#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
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
        validate(word);
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
        validate(word);
        const TrieNode* node = find_node(word);
        return node != nullptr && node->terminal;
    }

    bool starts_with(std::string_view prefix) const {
        validate(prefix);
        return find_node(prefix) != nullptr;
    }

private:
    static void validate(std::string_view text) {
        for (char character : text) {
            if (character < 'a' || character > 'z') {
                throw std::invalid_argument(
                    "Trie accepts only lowercase English letters");
            }
        }
    }

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

struct RadixTrieNode {
    std::string label;
    RadixTrieNode* children[26];
    bool terminal;

    explicit RadixTrieNode(std::string_view node_label = {})
        : label(node_label), children{}, terminal(false) {}
};

// A compressed trie: each node stores the full label of its incoming edge.
class RadixTrie {
public:
    RadixTrie() : root_(new RadixTrieNode{}) {}

    ~RadixTrie() {
        destroy(root_);
    }

    RadixTrie(const RadixTrie&) = delete;
    RadixTrie& operator=(const RadixTrie&) = delete;
    RadixTrie(RadixTrie&&) = delete;
    RadixTrie& operator=(RadixTrie&&) = delete;

    bool insert(std::string_view word) {
        validate(word);

        RadixTrieNode* current = root_;
        std::size_t offset = 0;

        while (offset < word.size()) {
            const std::size_t index = child_index(word[offset]);
            RadixTrieNode*& child = current->children[index];

            if (child == nullptr) {
                child = new RadixTrieNode(word.substr(offset));
                child->terminal = true;
                return true;
            }

            const std::size_t common = common_prefix_length(
                word.substr(offset), child->label);

            if (common == child->label.size()) {
                current = child;
                offset += common;
                continue;
            }

            RadixTrieNode* split = new RadixTrieNode(child->label.substr(0, common));
            child->label.erase(0, common);
            split->children[child_index(child->label.front())] = child;
            child = split;
            offset += common;

            if (offset == word.size()) {
                split->terminal = true;
            } else {
                RadixTrieNode* suffix = new RadixTrieNode(word.substr(offset));
                suffix->terminal = true;
                split->children[child_index(suffix->label.front())] = suffix;
            }
            return true;
        }

        const bool inserted = !current->terminal;
        current->terminal = true;
        return inserted;
    }

    bool contains(std::string_view word) const {
        validate(word);
        const RadixTrieNode* node = find_node(word, true);
        return node != nullptr && node->terminal;
    }

    bool starts_with(std::string_view prefix) const {
        validate(prefix);
        return find_node(prefix, false) != nullptr;
    }

private:
    static std::size_t child_index(char character) {
        return static_cast<std::size_t>(character - 'a');
    }

    static void validate(std::string_view text) {
        for (char character : text) {
            if (character < 'a' || character > 'z') {
                throw std::invalid_argument(
                    "RadixTrie accepts only lowercase English letters");
            }
        }
    }

    static std::size_t common_prefix_length(std::string_view first,
                                            std::string_view second) noexcept {
        std::size_t length = 0;
        while (length < first.size() && length < second.size() &&
               first[length] == second[length]) {
            ++length;
        }
        return length;
    }

    const RadixTrieNode* find_node(std::string_view text,
                                   bool require_complete_label) const {
        const RadixTrieNode* current = root_;
        std::size_t offset = 0;

        while (offset < text.size()) {
            const RadixTrieNode* child = current->children[child_index(text[offset])];
            if (child == nullptr) {
                return nullptr;
            }

            const std::size_t common = common_prefix_length(
                text.substr(offset), child->label);
            if (common == text.size() - offset) {
                return require_complete_label && common != child->label.size()
                    ? nullptr
                    : child;
            }
            if (common != child->label.size()) {
                return nullptr;
            }

            current = child;
            offset += common;
        }

        return current;
    }

    static void destroy(RadixTrieNode* node) noexcept {
        if (node == nullptr) {
            return;
        }

        for (RadixTrieNode* child : node->children) {
            destroy(child);
        }
        delete node;
    }

    RadixTrieNode* root_;
};