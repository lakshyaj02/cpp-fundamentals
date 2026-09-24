#pragma once

#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <optional>
#include <utility>

template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity)
        : capacity_(capacity), buffer_(capacity == 0 ? nullptr : std::make_unique<T[]>(capacity)) {}

    BoundedQueue(const BoundedQueue&) = delete;
    BoundedQueue& operator=(const BoundedQueue&) = delete;
    BoundedQueue(BoundedQueue&&) = delete;
    BoundedQueue& operator=(BoundedQueue&&) = delete;

    bool push(T value) {
        if (capacity_ == 0) {
            return false;
        }

        std::unique_lock lock(mutex_);
        not_full_.wait(lock, [this] {
            return size_ < capacity_ || closed_;
        });

        if (closed_) {
            return false;
        }

        push_unlocked(std::move(value));
        lock.unlock();
        not_empty_.notify_one();
        return true;
    }

    std::optional<T> pop() {
        std::unique_lock lock(mutex_);
        not_empty_.wait(lock, [this] {
            return size_ > 0 || closed_;
        });

        if (size_ == 0) {
            return std::nullopt;
        }

        T output = pop_unlocked();
        lock.unlock();
        not_full_.notify_one();
        return output;
    }

    bool try_push(T value) {
        std::lock_guard lock(mutex_);
        if (size_ == capacity_ || closed_) {
            return false;
        }

        push_unlocked(std::move(value));
        not_empty_.notify_one();
        return true;
    }

    bool try_pop(T& output) {
        std::lock_guard lock(mutex_);
        if (size_ == 0) {
            return false;
        }

        output = pop_unlocked();
        not_full_.notify_one();
        return true;
    }

    void close() {
        {
            std::lock_guard lock(mutex_);
            closed_ = true;
        }
        not_full_.notify_all();
        not_empty_.notify_all();
    }

    [[nodiscard]] bool empty() const {
        std::lock_guard lock(mutex_);
        return size_ == 0;
    }

    [[nodiscard]] bool full() const {
        std::lock_guard lock(mutex_);
        return size_ == capacity_;
    }

    [[nodiscard]] bool closed() const {
        std::lock_guard lock(mutex_);
        return closed_;
    }

    [[nodiscard]] std::size_t size() const {
        std::lock_guard lock(mutex_);
        return size_;
    }
    [[nodiscard]] std::size_t capacity() const {
        std::lock_guard lock(mutex_);
        return capacity_;
    }
    void push_unlocked(T value) {
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    T pop_unlocked() {
        T output = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return output;
    }

    std::lock_guard lock(mutex_);
    std::size_t size_ = 0;
    bool closed_ = false;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::unique_ptr<T[]> buffer_;
    mutable std::mutex mutex_;
};