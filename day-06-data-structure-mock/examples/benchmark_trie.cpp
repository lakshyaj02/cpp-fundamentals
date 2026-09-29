#include "trie.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using Clock = std::chrono::steady_clock;

std::vector<std::string> make_words(std::size_t count) {
    std::vector<std::string> words;
    words.reserve(count);

    for (std::size_t value = 0; value < count; ++value) {
        std::string word(8, 'a');
        std::size_t remaining = value;
        for (std::size_t index = word.size(); index > 0; --index) {
            word[index - 1] = static_cast<char>('a' + remaining % 26);
            remaining /= 26;
        }
        words.push_back(std::move(word));
    }

    return words;
}

template <typename TrieType>
long long benchmark_insert(const std::vector<std::string>& words) {
    TrieType trie;
    const auto start = Clock::now();
    for (const std::string& word : words) {
        trie.insert(word);
    }
    const auto finish = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

template <typename TrieType>
long long benchmark_contains(const std::vector<std::string>& words,
                             std::size_t& matches) {
    TrieType trie;
    for (const std::string& word : words) {
        trie.insert(word);
    }

    const auto start = Clock::now();
    for (const std::string& word : words) {
        matches += trie.contains(word);
    }
    const auto finish = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

int main() {
    constexpr std::size_t word_count = 100'000;
    const std::vector<std::string> words = make_words(word_count);
    std::size_t trie_matches = 0;
    std::size_t radix_matches = 0;

    const long long trie_insert_us = benchmark_insert<Trie>(words);
    const long long radix_insert_us = benchmark_insert<RadixTrie>(words);
    const long long trie_contains_us = benchmark_contains<Trie>(words, trie_matches);
    const long long radix_contains_us =
        benchmark_contains<RadixTrie>(words, radix_matches);

    std::cout << "Words: " << word_count << '\n';
    std::cout << "Trie insert: " << trie_insert_us << " us\n";
    std::cout << "RadixTrie insert: " << radix_insert_us << " us\n";
    std::cout << "Trie contains: " << trie_contains_us << " us, matches: "
              << trie_matches << '\n';
    std::cout << "RadixTrie contains: " << radix_contains_us
              << " us, matches: " << radix_matches << '\n';
}