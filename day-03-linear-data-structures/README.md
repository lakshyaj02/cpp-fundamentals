# Day 3: Arrays, linked lists, stacks, and queues

Goal: implement the core linear data structures without STL containers, preserve their invariants across edge cases, and state the time and space cost of every operation.

The implementations use raw dynamic arrays or linked nodes. Standard utilities, exceptions, and I/O are used, but `std::vector`, `std::list`, `std::stack`, and `std::queue` are not.

## Setup

Requirements: a C++20 compiler and CMake 3.20 or newer.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/linear_structures
```

## Implementations

| Type | Storage | Key invariant |
| --- | --- | --- |
| `SinglyLinkedList<T>` | individually allocated nodes | `tail_->next == nullptr`; head and tail are both null when empty |
| `DoublyLinkedList<T>` | nodes with next and previous links | head has no predecessor; tail has no successor |
| `Stack<T>` | resizing dynamic array | the top is at index `size - 1` |
| `Queue<T>` | resizing circular array | logical index `i` is physical index `(front + i) % capacity` |

Headers are in `include/`. These educational array implementations require `T` to be default-constructible and copy-assignable. Production generic containers normally use allocator primitives to construct only occupied elements.

## Array fundamentals

An array stores equal-sized elements contiguously. Given a base address, index access computes:

$$
\text{address}(i) = \text{base} + i \times \operatorname{sizeof}(T)
$$

That arithmetic makes random access $O(1)$. Inserting or erasing near the front requires shifting later elements, so it is $O(n)$. A dynamic array doubles its capacity when full: one growth costs $O(n)$, but a sequence of pushes costs $O(1)$ amortized per push.

## Singly linked list complexity

The implementation stores both head and tail pointers.

| Operation | Time | Auxiliary space |
| --- | ---: | ---: |
| `front`, `back`, `size`, `empty` | $O(1)$ | $O(1)$ |
| `push_front`, `push_back`, `pop_front` | $O(1)$ | $O(1)$ per insertion |
| `at(i)` | $O(i)$, worst $O(n)$ | $O(1)$ |
| `insert(i)`, `erase(i)` | $O(i)$, worst $O(n)$ | $O(1)$ per insertion |
| `pop_back` | $O(n)$ | $O(1)$ |
| copy | $O(n)$ | $O(n)$ |
| clear/destruction | $O(n)$ | $O(1)$ |

The whole structure uses $O(n)$ space: one value and one next pointer per node. A tail pointer makes append constant-time, but cannot make `pop_back` constant-time because finding the predecessor still requires traversal.

## Doubly linked list complexity

| Operation | Time | Auxiliary space |
| --- | ---: | ---: |
| `front`, `back`, `size`, `empty` | $O(1)$ | $O(1)$ |
| push or pop at either end | $O(1)$ | $O(1)$ per insertion |
| `at(i)` | $O(\min(i, n-i))$, worst $O(n)$ | $O(1)$ |
| `insert(i)`, `erase(i)` by index | $O(n)$ | $O(1)$ per insertion |
| insert/erase with an existing node pointer | $O(1)$ | $O(1)$ |
| copy | $O(n)$ | $O(n)$ |
| clear/destruction | $O(n)$ | $O(1)$ |

The whole structure uses $O(n)$ space with two links per node. The extra previous pointer buys constant-time removal from the back and bidirectional traversal.

## Stack complexity

A stack is last-in, first-out (LIFO). This implementation places the top at the dynamic array's end.

| Operation | Time | Auxiliary space |
| --- | ---: | ---: |
| `top`, `pop`, `size`, `empty` | $O(1)$ | $O(1)$ |
| `push` without growth | $O(1)$ | $O(1)$ |
| `push` that grows | $O(n)$ | $O(n)$ temporary allocation |
| `push` amortized | $O(1)$ | $O(1)$ amortized |
| copy | $O(n)$ | $O(n)$ |

Total storage is $O(n)$, though capacity may exceed size after geometric growth.

## Queue complexity

A queue is first-in, first-out (FIFO). A circular array reuses slots at the beginning instead of shifting elements after every dequeue.

| Operation | Time | Auxiliary space |
| --- | ---: | ---: |
| `front`, `back`, `dequeue`, `size`, `empty` | $O(1)$ | $O(1)$ |
| `enqueue` without growth | $O(1)$ | $O(1)$ |
| `enqueue` that grows | $O(n)$ | $O(n)$ temporary allocation |
| `enqueue` amortized | $O(1)$ | $O(1)$ amortized |
| copy | $O(n)$ | $O(n)$ |

Total storage is $O(n)$. A naive array queue that shifts after each removal would make dequeue $O(n)$; the circular index keeps it $O(1)$.

## Study loop

1. Draw the empty and one-element state for each structure.
2. Implement each operation before reading the supplied header.
3. Test transitions among empty, one-element, and many-element states.
4. Force stack growth and queue wraparound followed by growth.
5. Explain both worst-case and amortized cost.
6. Complete [the drills](exercises/complexity-drills.md), then check [the answers](answers/complexity-drills.md).

## Completion check

You are done when you can write all four structures from an empty file, explain every pointer or index update, implement deep copy and cleanup, identify the invariants that each operation preserves, and derive every complexity in the tables above.