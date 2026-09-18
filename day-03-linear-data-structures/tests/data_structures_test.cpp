#include "doubly_linked_list.hpp"
#include "queue.hpp"
#include "singly_linked_list.hpp"
#include "stack.hpp"

#include <cassert>

int main() {
    SinglyLinkedList<int> singly;
    singly.push_back(1);
    singly.push_back(3);
    singly.insert(1, 2);
    assert(singly.erase(1) == 2);
    assert(singly.pop_back() == 3);
    assert(singly.front() == 1 && singly.back() == 1);

    DoublyLinkedList<int> doubly;
    doubly.push_front(2);
    doubly.push_front(1);
    doubly.push_back(4);
    doubly.insert(2, 3);
    assert(doubly.at(2) == 3);
    assert(doubly.erase(1) == 2);
    assert(doubly.pop_front() == 1);
    assert(doubly.pop_back() == 4);
    assert(doubly.front() == 3 && doubly.back() == 3);

    DoublyLinkedList<int> copied = doubly;
    copied.front() = 99;
    assert(doubly.front() == 3);

    Stack<int> stack;
    for (int value = 0; value < 10; ++value) {
        stack.push(value);
    }
    for (int value = 9; value >= 0; --value) {
        assert(stack.pop() == value);
    }
    assert(stack.empty());

    Queue<int> queue;
    for (int value = 0; value < 4; ++value) {
        queue.enqueue(value);
    }
    assert(queue.dequeue() == 0);
    assert(queue.dequeue() == 1);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    for (int value = 2; value <= 6; ++value) {
        assert(queue.dequeue() == value);
    }
    assert(queue.empty());
}