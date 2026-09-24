#pragma once

#include <cstddef>
#include <memory>
#include <unordered_map>

class LRUCache {
public:
    explicit LRUCache(std::size_t capacity)
        : capacity_(capacity) {}

    ~LRUCache() {
        clear();
    }

    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;

    void put(int key, int value) {
        if (capacity_ == 0) {
            return;
        }

        auto existing = entries_.find(key);
        if (existing != entries_.end()) {
            existing->second->value = value;
            mark_most_recent(existing->second);
            return;
        }

        auto node = std::make_unique<Node>(Node{key, value, nullptr, nullptr});
        entries_.emplace(key, node.get());
        push_front(node.release());

        if (entries_.size() > capacity_) {
            evict_least_recent();
        }
    }

    int get(int key) {
        auto found = entries_.find(key);
        if (found == entries_.end()) {
            return -1;
        }

        mark_most_recent(found->second);
        return found->second->value;
    }

    std::size_t size() const noexcept {
        return entries_.size();
    }

private:
    struct Node {
        int key;
        int value;
        Node* previous;
        Node* next;
    };

    void detach(Node* node) noexcept {
        if (node->previous != nullptr) {
            node->previous->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next != nullptr) {
            node->next->previous = node->previous;
        } else {
            tail_ = node->previous;
        }
    }

    void push_front(Node* node) noexcept {
        node->previous = nullptr;
        node->next = head_;

        if (head_ != nullptr) {
            head_->previous = node;
        } else {
            tail_ = node;
        }

        head_ = node;
    }

    void mark_most_recent(Node* node) noexcept {
        if (node == head_) {
            return;
        }

        detach(node);
        push_front(node);
    }

    void evict_least_recent() {
        Node* node = tail_;
        detach(node);
        entries_.erase(node->key);
        delete node;
    }

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }

        tail_ = nullptr;
        entries_.clear();
    }

    std::size_t capacity_;
    std::unordered_map<int, Node*> entries_;
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
};
