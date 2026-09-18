#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
public:
    Stack() : data_(new T[initial_capacity_]) {}

    ~Stack() { delete[] data_; }

    Stack(const Stack& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (std::size_t index = 0; index < size_; ++index) {
            data_[index] = other.data_[index];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            Stack copy(other);
            swap(copy);
        }
        return *this;
    }

    Stack(Stack&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            size_ = std::exchange(other.size_, 0);
            capacity_ = std::exchange(other.capacity_, 0);
        }
        return *this;
    }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    T& top() { ensure_not_empty(); return data_[size_ - 1]; }
    const T& top() const { ensure_not_empty(); return data_[size_ - 1]; }

    void push(const T& value) {
        ensure_capacity();
        data_[size_++] = value;
    }

    T pop() {
        ensure_not_empty();
        return std::move(data_[--size_]);
    }

    void swap(Stack& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

private:
    void ensure_not_empty() const {
        if (empty()) {
            throw std::underflow_error("stack is empty");
        }
    }

    void ensure_capacity() {
        if (size_ < capacity_) {
            return;
        }
        const std::size_t new_capacity = capacity_ == 0 ? initial_capacity_ : capacity_ * 2;
        T* replacement = new T[new_capacity];
        for (std::size_t index = 0; index < size_; ++index) {
            replacement[index] = std::move(data_[index]);
        }
        delete[] data_;
        data_ = replacement;
        capacity_ = new_capacity;
    }

    static constexpr std::size_t initial_capacity_ = 4;
    T* data_;
    std::size_t size_ = 0;
    std::size_t capacity_ = initial_capacity_;
};