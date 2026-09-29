#include "trie.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename TrieType>
void test_insert_and_lookup() {
    TrieType trie;

    assert(trie.insert("apple"));
    assert(trie.insert("app"));
    assert(trie.insert("apt"));
    assert(trie.insert("bat"));
    assert(!trie.insert("apple"));

    assert(trie.contains("apple"));
    assert(trie.contains("app"));
    assert(trie.contains("apt"));
    assert(trie.contains("bat"));
    assert(!trie.contains("ap"));
    assert(!trie.contains("apply"));
    assert(!trie.contains("bad"));
}

template <typename TrieType>
void test_prefix_lookup() {
    TrieType trie;
    trie.insert("application");
    trie.insert("apply");

    assert(trie.starts_with(""));
    assert(trie.starts_with("app"));
    assert(trie.starts_with("appl"));
    assert(trie.starts_with("application"));
    assert(!trie.starts_with("apple"));
    assert(!trie.starts_with("banana"));
}

template <typename TrieType>
void test_empty_word() {
    TrieType trie;

    assert(trie.insert(""));
    assert(!trie.insert(""));
    assert(trie.contains(""));
    assert(trie.starts_with(""));
}

template <typename TrieType>
void test_invalid_input() {
    TrieType trie;

    try {
        trie.insert("Apple");
        assert(false);
    } catch (const std::invalid_argument&) {
    }

    try {
        trie.contains("two words");
        assert(false);
    } catch (const std::invalid_argument&) {
    }
}

template <typename TrieType>
void run_tests() {
    test_insert_and_lookup<TrieType>();
    test_prefix_lookup<TrieType>();
    test_empty_word<TrieType>();
    test_invalid_input<TrieType>();
}

int main() {
    run_tests<Trie>();
    run_tests<RadixTrie>();

    std::cout << "All trie tests passed.\n";
}