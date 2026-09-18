#include "singly_linked_list.hpp"

#include <cassert>
#include <stdexcept>
#include <utility>

int main() {
    SinglyLinkedList<int> values;
    assert(values.empty());

    values.push_back(20);
    values.push_front(10);
    values.push_back(30);
    assert(values.size() == 3);
    assert(values.front() == 10);
    assert(values.back() == 30);
    assert(values.at(1) == 20);

    SinglyLinkedList<int> copied = values;
    copied.at(1) = 99;
    assert(values.at(1) == 20);
    assert(copied.at(1) == 99);

    SinglyLinkedList<int> moved = std::move(copied);
    assert(copied.empty());
    assert(moved.pop_front() == 10);
    assert(moved.pop_front() == 99);
    assert(moved.pop_front() == 30);
    assert(moved.empty());

    bool threw = false;
    try {
        moved.pop_front();
    } catch (const std::underflow_error&) {
        threw = true;
    }
    assert(threw);
}