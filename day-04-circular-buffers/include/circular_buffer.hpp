#pragma once

#include <cstddef>
#include <memory>

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(std::size_t capacity)
        : data_(capacity == 0 ? nullptr : std::make_unique<T[]>(capacity)),
          capacity_(capacity) {}

    bool push(const T& value) {
        if (full()) {
            return false;
        }
        data_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
        return true;
    }

    bool pop(T& value) {
        if (empty()) {
            return false;
        }
        value = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return true;
    }

    [[nodiscard]] bool empty() const noexcept {
        // Express this using the buffer's current state.
        return size_ == 0;
    }

    [[nodiscard]] bool full() const noexcept {
        // Express this using the buffer's current state.
        return size_ == capacity_;
    }

    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }

private:
    std::unique_ptr<T[]> data_;
    std::size_t capacity_ = 0;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};