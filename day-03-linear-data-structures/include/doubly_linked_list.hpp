#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T value;
        Node* previous;
        Node* next;

        Node(const T& value, Node* previous = nullptr, Node* next = nullptr)
            : value(value), previous(previous), next(next) {}
    };

public:
    DoublyLinkedList() = default;

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        DoublyLinkedList copy;
        for (Node* current = other.head_; current != nullptr; current = current->next) {
            copy.push_back(current->value);
        }
        swap(copy);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            DoublyLinkedList copy(other);
            swap(copy);
        }
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head_(std::exchange(other.head_, nullptr)),
          tail_(std::exchange(other.tail_, nullptr)),
          size_(std::exchange(other.size_, 0)) {}

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = std::exchange(other.head_, nullptr);
            tail_ = std::exchange(other.tail_, nullptr);
            size_ = std::exchange(other.size_, 0);
        }
        return *this;
    }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    T& front() { ensure_not_empty(); return head_->value; }
    const T& front() const { ensure_not_empty(); return head_->value; }
    T& back() { ensure_not_empty(); return tail_->value; }
    const T& back() const { ensure_not_empty(); return tail_->value; }
    T& at(std::size_t index) { return node_at(index)->value; }
    const T& at(std::size_t index) const { return node_at(index)->value; }

    void push_front(const T& value) {
        Node* node = new Node(value, nullptr, head_);
        if (head_ == nullptr) {
            tail_ = node;
        } else {
            head_->previous = node;
        }
        head_ = node;
        ++size_;
    }

    void push_back(const T& value) {
        Node* node = new Node(value, tail_);
        if (tail_ == nullptr) {
            head_ = node;
        } else {
            tail_->next = node;
        }
        tail_ = node;
        ++size_;
    }

    T pop_front() {
        ensure_not_empty();
        Node* removed = head_;
        T value = std::move(removed->value);
        head_ = removed->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->previous = nullptr;
        }
        delete removed;
        --size_;
        return value;
    }

    T pop_back() {
        ensure_not_empty();
        Node* removed = tail_;
        T value = std::move(removed->value);
        tail_ = removed->previous;
        if (tail_ == nullptr) {
            head_ = nullptr;
        } else {
            tail_->next = nullptr;
        }
        delete removed;
        --size_;
        return value;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("list index out of range");
        }
        if (index == 0) {
            push_front(value);
        } else if (index == size_) {
            push_back(value);
        } else {
            Node* next = node_at(index);
            Node* node = new Node(value, next->previous, next);
            next->previous->next = node;
            next->previous = node;
            ++size_;
        }
    }

    T erase(std::size_t index) {
        Node* removed = node_at(index);
        if (removed == head_) {
            return pop_front();
        }
        if (removed == tail_) {
            return pop_back();
        }
        T value = std::move(removed->value);
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        delete removed;
        --size_;
        return value;
    }

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void swap(DoublyLinkedList& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

private:
    void ensure_not_empty() const {
        if (empty()) {
            throw std::underflow_error("list is empty");
        }
    }

    Node* node_at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("list index out of range");
        }
        if (index < size_ / 2) {
            Node* current = head_;
            for (std::size_t position = 0; position < index; ++position) {
                current = current->next;
            }
            return current;
        }
        Node* current = tail_;
        for (std::size_t position = size_ - 1; position > index; --position) {
            current = current->previous;
        }
        return current;
    }

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};