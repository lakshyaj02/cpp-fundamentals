#pragma once

#include <cstddef>
#include <functional>
#include <list>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable {
public:
    explicit ChainedHashTable(std::size_t bucket_count = 8)
        : buckets_(bucket_count == 0 ? 1 : bucket_count) {}

    bool insert_or_assign(const Key& key, const Value& value) {
        auto& bucket = buckets_[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return false;
            }
        }
        bucket.emplace_back(key, value);
        ++size_;
        return true;
    }

    Value* find(const Key& key) {
        auto& bucket = buckets_[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        auto& bucket = buckets_[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        auto& bucket = buckets_[bucket_index(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool contains(const Key& key) const { return find(key) != nullptr; }
    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t bucket_count() const noexcept { return buckets_.size(); }

    [[nodiscard]] double load_factor() const noexcept {
        return static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

private:
    using Entry = std::pair<Key, Value>;

    [[nodiscard]] std::size_t bucket_index(const Key& key) const {
        return hash_(key) % buckets_.size();
    }

    void rehash(std::size_t new_bucket_count) {
        std::vector<std::list<Entry>> new_buckets(new_bucket_count == 0 ? 1 : new_bucket_count);
        for (auto& bucket : buckets_) {
            for (auto& entry : bucket) {
                new_buckets[hash_(entry.first) % new_buckets.size()].push_back(std::move(entry));
            }
        }
        buckets_ = std::move(new_buckets);
    }

    static constexpr double max_load_factor_ = 0.75;
    std::vector<std::list<Entry>> buckets_;
    std::size_t size_ = 0;
    Hash hash_;
};