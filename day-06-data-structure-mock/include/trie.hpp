#pragma once

#include <cstddef>
#include <stdexcept>
#include <string_view>

struct TrieNode {
    TrieNode* children[26];
    bool terminal;

    TrieNode() : children{}, terminal(false) {}
};

class Trie {
public:
    Trie() : root_(new TrieNode{}) {}

    ~Trie() {
        destroy(root_);
    }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    Trie(Trie&&) = delete;
    Trie& operator=(Trie&&) = delete;

    // Returns true only when word was not already stored.
    bool insert(std::string_view word) {
        TrieNode* current = root_;

        for (char character : word) {
            const std::size_t index = child_index(character);
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode{};
            }
            current = current->children[index];
        }

        const bool inserted = !current->terminal;
        current->terminal = true;
        return inserted;
    }

    bool contains(std::string_view word) const {
        const TrieNode* node = find_node(word);
        return node != nullptr && node->terminal;
    }

    bool starts_with(std::string_view prefix) const {
        return find_node(prefix) != nullptr;
    }

private:
    static std::size_t child_index(char character) {
        if (character < 'a' || character > 'z') {
            throw std::invalid_argument("Trie accepts only lowercase English letters");
        }
        return static_cast<std::size_t>(character - 'a');
    }

    const TrieNode* find_node(std::string_view text) const {
        const TrieNode* current = root_;

        for (char character : text) {
            current = current->children[child_index(character)];
            if (current == nullptr) {
                return nullptr;
            }
        }

        return current;
    }

    static void destroy(TrieNode* node) noexcept {
        if (node == nullptr) {
            return;
        }

        for (TrieNode* child : node->children) {
            destroy(child);
        }
        delete node;
    }

    TrieNode* root_;
};