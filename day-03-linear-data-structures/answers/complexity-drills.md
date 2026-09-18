# Complexity drill answers

1. The tail gives direct access to the last node, so linking a new node is $O(1)$. A singly linked node has no previous pointer, so finding the new tail before deletion requires a traversal: $O(n)$ time and $O(1)$ auxiliary space.

2. With the node pointer, reconnecting its two neighbors is $O(1)$. Removing by index first traverses to the node, making the complete operation $O(n)$ in the worst case. Both use $O(1)$ auxiliary space.

3. Save the old head, advance head to its null next pointer, delete the old node, decrement size, and set tail to null. The invariant is that head and tail must either both be null or both identify nodes in the same chain.

4. Allocate capacity 16, move or copy 8 elements, release the old array, then place the new value. That push is $O(n)$ time and temporarily needs $O(n)$ extra space.

5. Capacities grow geometrically: over $n$ pushes, elements are copied roughly $1 + 2 + 4 + \cdots + n < 2n$ times. Total growth work is $O(n)$, so average growth work per push is $O(1)$.

6. The physical indices are 6, 7, 0, and 1 because each logical index maps to `(front + i) % capacity`.

7. The physical storage may wrap around. Copying logical element 0 first restores a contiguous order with the new front at 0 and preserves FIFO order.

8. Both use $O(n)$ total space. Ignoring allocator overhead and padding, a singly linked node stores one pointer beyond its value; a doubly linked node stores two.

9. Use a stack for undo because the most recent action is undone first. Use a queue for arrival-order processing because the earliest task leaves first.

10. Test empty-operation errors, the first insertion, removal of the only element, front and back operations, growth boundaries, queue wraparound, indexed boundaries, deep-copy independence, self-assignment, move behavior, and destruction of non-empty structures.