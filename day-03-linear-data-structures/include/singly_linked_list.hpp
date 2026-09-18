#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next;

        explicit Node(const T& value, Node* next = nullptr)
            : value(value), next(next) {}
    };

public:
    SinglyLinkedList() = default;

    ~SinglyLinkedList() {
        clear();
    }

    SinglyLinkedList(const SinglyLinkedList& other) {
        SinglyLinkedList copy;
        for (Node* current = other.head_; current != nullptr; current = current->next) {
            copy.push_back(current->value);
        }
        swap(copy);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            SinglyLinkedList copy(other);
            swap(copy);
        }
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : head_(std::exchange(other.head_, nullptr)),
          tail_(std::exchange(other.tail_, nullptr)),
          size_(std::exchange(other.size_, 0)) {}

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = std::exchange(other.head_, nullptr);
            tail_ = std::exchange(other.tail_, nullptr);
            size_ = std::exchange(other.size_, 0);
        }
        return *this;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    T& front() {
        ensure_not_empty();
        return head_->value;
    }

    const T& front() const {
        ensure_not_empty();
        return head_->value;
    }

    T& back() {
        ensure_not_empty();
        return tail_->value;
    }

    const T& back() const {
        ensure_not_empty();
        return tail_->value;
    }

    T& at(std::size_t index) {
        return node_at(index)->value;
    }

    const T& at(std::size_t index) const {
        return node_at(index)->value;
    }

    void push_front(const T& value) {
        Node* node = new Node(value, head_);
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = node;
        }
        ++size_;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    T pop_front() {
        ensure_not_empty();
        Node* old_head = head_;
        T value = std::move(old_head->value);
        head_ = head_->next;
        delete old_head;
        --size_;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        return value;
    }

    T pop_back() {
        ensure_not_empty();
        if (size_ == 1) {
            return pop_front();
        }
        Node* new_tail = node_at(size_ - 2);
        T value = std::move(tail_->value);
        delete tail_;
        tail_ = new_tail;
        tail_->next = nullptr;
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
            Node* previous = node_at(index - 1);
            previous->next = new Node(value, previous->next);
            ++size_;
        }
    }

    T erase(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("list index out of range");
        }
        if (index == 0) {
            return pop_front();
        }
        Node* previous = node_at(index - 1);
        Node* removed = previous->next;
        T value = std::move(removed->value);
        previous->next = removed->next;
        if (removed == tail_) {
            tail_ = previous;
        }
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

    void swap(SinglyLinkedList& other) noexcept {
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
        Node* current = head_;
        for (std::size_t position = 0; position < index; ++position) {
            current = current->next;
        }
        return current;
    }

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};