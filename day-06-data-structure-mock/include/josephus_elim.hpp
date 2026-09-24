#pragma once

// Josephus problem description:
// n people numbered from 1 to n stand in a circle. Starting with person 1, count k people clockwise. The person counted as k is eliminated.

// Continue counting from the person immediately after the eliminated person until only one survivor remains.

struct Node {
    int value;
    Node* next = nullptr;
};

int josephus_elimination(int n, int k) {
    if(n <= 0 || k <= 0) {
        return -1;
    }

    // Create the circular linked list
    Node* head = new Node{1, nullptr};
    Node* tail = head;
    for(int i=2; i<=n; ++i) {
        tail->next = new Node{i, nullptr};
        tail = tail->next;
    }
    tail->next = head; // Complete the circle

    // Start the elimination process
    Node* curr = head;
    Node* prev = tail;

    while(curr->next != curr){
        for(int i=1; i<k; ++i) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }
    int survivor = curr->value;
    delete curr; // Delete the last remaining node
    return survivor;
}
