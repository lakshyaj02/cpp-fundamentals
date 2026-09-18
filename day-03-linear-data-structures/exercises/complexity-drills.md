# Complexity drills

Answer each question with time complexity, auxiliary space complexity, and the invariant involved.

1. Why does storing a tail pointer make singly linked-list append $O(1)$ but not make `pop_back` $O(1)$?
2. A pointer to a doubly linked-list node is already available. What is the cost of removing that node? How does removing by numeric index differ?
3. Trace head and tail while removing the only node in a singly linked list. Which assignments are required?
4. A dynamic-array stack has size 8 and capacity 8. What work happens on the next push if capacity doubles?
5. Why is stack push $O(1)$ amortized even though an individual push can be $O(n)$?
6. In a queue of capacity 8, `front == 6` and `size == 4`. At which physical indices are its elements stored?
7. Why must a circular queue copy elements in logical order during growth rather than copying the physical array unchanged?
8. Compare the total memory overhead of singly and doubly linked lists for $n$ nodes.
9. Which structure would you choose for undo history? Which for tasks handled in arrival order?
10. List the edge cases that should be tested for every implementation here.