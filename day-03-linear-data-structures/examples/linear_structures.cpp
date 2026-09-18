#include "doubly_linked_list.hpp"
#include "queue.hpp"
#include "singly_linked_list.hpp"
#include "stack.hpp"

#include <iostream>

int main() {
    SinglyLinkedList<int> singly;
    singly.push_back(10);
    singly.push_back(30);
    singly.insert(1, 20);
    std::cout << "singly: ";
    while (!singly.empty()) {
        std::cout << singly.pop_front() << ' ';
    }

    DoublyLinkedList<int> doubly;
    doubly.push_front(20);
    doubly.push_front(10);
    doubly.push_back(30);
    std::cout << "\ndoubly backward: ";
    while (!doubly.empty()) {
        std::cout << doubly.pop_back() << ' ';
    }

    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "\nstack (LIFO): ";
    while (!stack.empty()) {
        std::cout << stack.pop() << ' ';
    }

    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "\nqueue (FIFO): ";
    while (!queue.empty()) {
        std::cout << queue.dequeue() << ' ';
    }
    std::cout << '\n';
}