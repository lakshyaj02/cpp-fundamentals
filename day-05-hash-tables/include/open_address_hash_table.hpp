#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

enum class ProbeStrategy {
    linear,
    quadratic,
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressHashTable {
public:
    explicit OpenAddressHashTable(
        std::size_t capacity = 8,
        ProbeStrategy strategy = ProbeStrategy::linear)
        : slots_(capacity == 0 ? 8 : capacity), strategy_(strategy) {}

    bool insert_or_assign(const Key& key, const Value& value) {
        if (load_factor() > max_load_factor_) {
            rehash(slots_.size() * 2);
        }
        std::optional<std::size_t> first_tombstone;
        for (std::size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            std::size_t index = probe_index(key, attempt, slots_.size());
            auto& slot = slots_[index];
            if (slot.state == SlotState::tombstone) {
                if (!first_tombstone) {
                    first_tombstone = index;
                }
                continue;
            }
            if (slot.state == SlotState::empty) {
                auto& destination = first_tombstone ? slots_[*first_tombstone] : slot;
                destination.entry = std::make_pair(key, value);
                destination.state = SlotState::occupied;
                ++size_;
                if (first_tombstone) {
                    --tombstones_;
                }
                return true;
            }
            if (slot.entry->first == key) {
                slot.entry->second = value;
                return false;
            }
        }

        if (first_tombstone) {
            auto& destination = slots_[*first_tombstone];
            destination.entry = std::make_pair(key, value);
            destination.state = SlotState::occupied;
            ++size_;
            --tombstones_;
            return true;
        }
        return false;
    }

    Value* find(const Key& key) {
        for (std::size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            std::size_t index = probe_index(key, attempt, slots_.size());
            auto& slot = slots_[index];
            if (slot.state == SlotState::empty) {
                return nullptr;
            }
            if (slot.state == SlotState::occupied && slot.entry->first == key) {
                return &slot.entry->second;
            }
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        for (std::size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            std::size_t index = probe_index(key, attempt, slots_.size());
            auto& slot = slots_[index];
            if (slot.state == SlotState::empty) {
                return nullptr;
            }
            if (slot.state == SlotState::occupied && slot.entry->first == key) {
                return &slot.entry->second;
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        for (std::size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            std::size_t index = probe_index(key, attempt, slots_.size());
            auto& slot = slots_[index];
            if (slot.state == SlotState::empty) {
                return false;
            }
            if (slot.state == SlotState::occupied && slot.entry->first == key) {
                slot.state = SlotState::tombstone;
                --size_;
                ++tombstones_;
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool contains(const Key& key) const { return find(key) != nullptr; }
    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return slots_.size(); }

    [[nodiscard]] double load_factor() const noexcept {
        return static_cast<double>(size_) / static_cast<double>(slots_.size());
    }

private:
    enum class SlotState {
        empty,
        occupied,
        tombstone,
    };

    struct Slot {
        std::optional<std::pair<Key, Value>> entry;
        SlotState state = SlotState::empty;
    };

    [[nodiscard]] std::size_t probe_index(
        const Key& key,
        std::size_t attempt,
        std::size_t capacity) const {
        switch (strategy_) {
            case ProbeStrategy::linear:
                return (hash_(key) + attempt) % capacity;
            case ProbeStrategy::quadratic:
                return (hash_(key) + attempt * attempt) % capacity;
        }
        return 0; // Should never reach here.
    }

    void rehash(std::size_t new_capacity) {
        std::vector<Slot> new_slots(new_capacity == 0 ? 8 : new_capacity);
        for (auto& slot : slots_) {
            if (slot.state == SlotState::occupied) {
                const auto& [key, value] = *slot.entry;
                std::size_t attempt = 0;
                std::size_t index;
                do {
                    index = probe_index(key, attempt, new_slots.size());
                    ++attempt;
                } while (new_slots[index].state == SlotState::occupied);
                new_slots[index].entry = std::make_optional(std::make_pair(key, value));
                new_slots[index].state = SlotState::occupied;
            }
        }
        slots_ = std::move(new_slots);
    }

    static constexpr double max_load_factor_ = 0.6;
    std::vector<Slot> slots_;
    std::size_t size_ = 0;
    std::size_t tombstones_ = 0;
    ProbeStrategy strategy_;
    Hash hash_;
};