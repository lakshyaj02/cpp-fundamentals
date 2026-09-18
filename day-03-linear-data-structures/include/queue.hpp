#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue {
public:
    Queue() : data_(new T[initial_capacity_]) {}

    ~Queue() { delete[] data_; }

    Queue(const Queue& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (std::size_t index = 0; index < size_; ++index) {
            data_[index] = other.data_[(other.front_ + index) % other.capacity_];
        }
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            Queue copy(other);
            swap(copy);
        }
        return *this;
    }

    Queue(Queue&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          front_(std::exchange(other.front_, 0)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            front_ = std::exchange(other.front_, 0);
            size_ = std::exchange(other.size_, 0);
            capacity_ = std::exchange(other.capacity_, 0);
        }
        return *this;
    }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    T& front() { ensure_not_empty(); return data_[front_]; }
    const T& front() const { ensure_not_empty(); return data_[front_]; }
    T& back() { ensure_not_empty(); return data_[(front_ + size_ - 1) % capacity_]; }
    const T& back() const { ensure_not_empty(); return data_[(front_ + size_ - 1) % capacity_]; }

    void enqueue(const T& value) {
        ensure_capacity();
        data_[(front_ + size_) % capacity_] = value;
        ++size_;
    }

    T dequeue() {
        ensure_not_empty();
        T value = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        --size_;
        if (size_ == 0) {
            front_ = 0;
        }
        return value;
    }

    void swap(Queue& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(front_, other.front_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

private:
    void ensure_not_empty() const {
        if (empty()) {
            throw std::underflow_error("queue is empty");
        }
    }

    void ensure_capacity() {
        if (size_ < capacity_) {
            return;
        }
        const std::size_t new_capacity = capacity_ == 0 ? initial_capacity_ : capacity_ * 2;
        T* replacement = new T[new_capacity];
        for (std::size_t index = 0; index < size_; ++index) {
            replacement[index] = std::move(data_[(front_ + index) % capacity_]);
        }
        delete[] data_;
        data_ = replacement;
        front_ = 0;
        capacity_ = new_capacity;
    }

    static constexpr std::size_t initial_capacity_ = 4;
    T* data_;
    std::size_t front_ = 0;
    std::size_t size_ = 0;
    std::size_t capacity_ = initial_capacity_;
};