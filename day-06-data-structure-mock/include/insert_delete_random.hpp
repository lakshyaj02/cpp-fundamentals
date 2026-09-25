#pragma once

#include <vector>
#include <unordered_map>
// Insert/Delete/GetRandom problem description:
// Design a data structure that stores unique integers and supports all of the
// following operations in average O(1) time:
//
// - bool insert(int value): Add value if it is not already present. Return true
//   when the value was inserted; otherwise return false.
// - bool remove(int value): Remove value if it is present. Return true when the
//   value was removed; otherwise return false.
// - int get_random(): Return one of the stored values such that every stored
//   value has an equal probability of being chosen.
//
// Assumptions and constraints:
// - Values are unique.
// - get_random() is called only when the data structure is non-empty.
// - Do not use a linear scan during insert, remove, or get_random.
// - Removing an element may change the internal order of the remaining values.
//
// Example:
// InsertDeleteRandom collection;
// collection.insert(10);       // true, values: [10]
// collection.insert(20);       // true, values: [10, 20]
// collection.insert(10);       // false, values: [10, 20]
// collection.remove(10);       // true, values may be [20]
// collection.get_random();     // 20

class InsertDeleteRandom {
public:
    bool insert(int value){
        if(value_to_index.find(value) != value_to_index.end()) {
            return false;
        }
        values.push_back(value);
        value_to_index[value] = values.size() - 1;
        return true;
    }
    bool remove(int value){
        auto it = value_to_index.find(value);
        if(it == value_to_index.end()) {
            return false;
        }
        int index = it->second;
        int last_value = values.back();
        values[index] = last_value;
        value_to_index[last_value] = index;
        values.pop_back();
        value_to_index.erase(it);
        return true;
    }
    int get_random(){
        if(values.empty()) {
            throw std::runtime_error("get_random() called on empty collection");
        }
        int random_index = rand() % values.size();
        return values[random_index];
    }
private:
    std::vector<int> values;
    std::unordered_map<int, int> value_to_index;
};