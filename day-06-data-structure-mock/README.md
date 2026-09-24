# Day 6: Data structure mock interview

Goal: design, implement, test, and explain an LRU cache from a blank C++ file under interview conditions.

This is a mock day, not a guided implementation. Do not look at earlier linked-list or hash-table code until the review phase.

## Rules

- Use C++20.
- You may use `std::unordered_map`, but not `std::list`.
- Write the doubly linked list and its node operations yourself.
- Keep `get` and `put` at average $O(1)$ time.
- Keep total storage at $O(capacity)$.
- Do not use global state.
- State your assumptions before coding.

## Mock schedule

| Time | Task |
| ---: | --- |
| 0-5 min | Restate the API, constraints, and edge cases |
| 5-12 min | Choose the data structures and draw their invariants |
| 12-42 min | Implement the cache from scratch |
| 42-52 min | Test normal and boundary cases |
| 52-60 min | Explain complexity, ownership, and follow-ups |

Use a timer. During the first attempt, compile only after you have written a complete first draft.

## Primary problem: LRU cache

Implement this interface:

```cpp
class LRUCache {
public:
    explicit LRUCache(std::size_t capacity);

    std::optional<int> get(int key);
    void put(int key, int value);
    std::size_t size() const noexcept;
};
```

The cache evicts the **least recently used** entry when inserting a new key would exceed its capacity.

- A successful `get` makes that key most recently used.
- An unsuccessful `get` does not change the cache.
- Updating an existing key changes its value and makes it most recently used.
- Inserting a new key makes it most recently used.
- A zero-capacity cache stores nothing.

Example:

```text
LRUCache cache(2)
put(1, 10)       order: [1]
put(2, 20)       order: [2, 1]
get(1) -> 10     order: [1, 2]
put(3, 30)       order: [3, 1], key 2 is evicted
get(2) -> empty  order: [3, 1]
```

In each order above, the most recently used key is on the left.

## Design checkpoint

Before writing code, answer these questions aloud:

1. Why is a hash table alone unable to identify the least recently used key in $O(1)$ time?
2. Why is a linked list alone unable to find an arbitrary key in $O(1)$ time?
3. What does the map store as its value?
4. Which end of the list represents the most recently used entry?
5. Which pointer updates are required when moving a middle node to the front?
6. Who owns each node, and when is it deleted?
7. How will the empty and one-element cases remain simple?

Recommended representation:

```text
unordered_map<key, Node*>             recency list

key 1 -----------------------------> [1:10]
key 2 -----------> [2:20] <--------> [1:10] <--------> [3:30]
key 3 -------------------------------------------------> [3:30]
                  most recent                         least recent
```

Sentinel head and tail nodes are optional. If you use them, explain what edge cases they remove and whether they store real entries.

## Invariants

Write these beside your implementation and check them after every mutation:

1. Every real list node has exactly one matching map entry.
2. Every map entry points to a node currently in the list.
3. The list contains exactly `size()` real nodes.
4. The most recently used node is at the chosen front end.
5. The least recently used node is at the chosen back end.
6. Forward and backward links agree.
7. The number of entries never exceeds capacity.

## Suggested implementation order

1. Define `Node` and the cache's data members.
2. Implement a helper that detaches an existing node.
3. Implement a helper that inserts an existing node at the most-recent end.
4. Implement a helper that marks an existing node as recently used.
5. Implement `get`.
6. Implement updating an existing key in `put`.
7. Implement inserting a new key in `put`.
8. Implement eviction.
9. Implement cleanup and decide whether copying is allowed.

Each list helper should do one job. Cache policy belongs in `get` and `put`; pointer rewiring belongs in the list helpers.

## Required tests

Use assertions to cover each case:

1. A missing key returns `std::nullopt`.
2. One insertion can be retrieved.
3. Updating a key changes its value without changing the size.
4. A successful `get` changes eviction order.
5. Inserting past capacity evicts exactly one least-recent key.
6. Repeated reads keep the correct entry most recent.
7. Capacity one handles repeated replacement.
8. Capacity zero always remains empty.
9. Negative keys and values work.
10. A long mixed sequence never exceeds capacity.

Run the finished program with warnings and sanitizers:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  lru_cache.cpp -o lru_cache
./lru_cache
```

## Complexity review

Fill this table without looking at notes:

| Operation | Average time | Why |
| --- | ---: | --- |
| successful `get` | ? | ? |
| unsuccessful `get` | ? | ? |
| update with `put` | ? | ? |
| insert below capacity | ? | ? |
| insert with eviction | ? | ? |
| destruction | ? | ? |

Then explain why the guarantees are average-case rather than worst-case and what role the hash function plays.

## Debugging drill

If a test fails, draw the map and both links of every node after each operation. Check these failure patterns first:

- The map still points to an evicted node.
- A detached node remains connected on one side.
- Moving the front node corrupts the list.
- Updating a key allocates a duplicate node.
- Eviction occurs before checking whether the key already exists.
- Zero capacity attempts to remove from an empty list.
- Raw-pointer ownership causes a leak, double delete, or accidental shallow copy.

## Follow-up rounds

Attempt these only after the core cache passes all tests.

### Round 1: Generic cache

Convert the cache to `template <typename Key, typename Value>`. Decide how hashing and equality should be supplied and whether `get` should return a copy, pointer, reference, or optional reference wrapper.

### Round 2: Standard-library implementation

Replace the custom linked list with `std::list`. Store list iterators in the hash table and use `splice` to move an entry without allocating. Compare code size, safety, and iterator invalidation rules with the from-scratch version.

### Round 3: LFU cache

Design an LFU cache with average $O(1)$ `get` and `put`. Track frequency and recency so that ties among equally frequent entries evict the least recently used one. Explain why one LRU list is no longer sufficient.

### Round 4: Production concerns

Discuss, without necessarily implementing:

- thread safety and lock granularity;
- exception safety during insertion;
- memory overhead per entry;
- custom hash functions and collision attacks;
- time-based expiration;
- persistence and distributed caches;
- metrics such as hit rate and eviction count.

## Problem bank

Complete these in order within each group. Problems marked **Core mock** are the best full 45-60 minute interview simulations. For every problem, state the invariant, complexity target, and edge cases before coding.

### Arrays and strings

- [ ] Two Sum
- [ ] Best Time to Buy and Sell Stock
- [ ] Product of Array Except Self
- [ ] Maximum Subarray
- [ ] Merge Intervals
- [ ] Insert Interval
- [ ] Rotate Array
- [ ] Set Matrix Zeroes
- [ ] Spiral Matrix
- [ ] Longest Substring Without Repeating Characters
- [ ] Minimum Window Substring

### Linked lists

- [ ] Reverse a Linked List
- [ ] Find the Middle Node
- [ ] Detect a Cycle and Find Its Start
- [ ] Merge Two Sorted Lists
- [ ] Remove Nth Node From End
- [ ] Reorder List
- [ ] Add Two Numbers
- [ ] Copy List With Random Pointer
- [ ] Merge K Sorted Lists
- [ ] **Core mock: LRU Cache**

### Stacks, queues, and deques

- [ ] Valid Parentheses
- [ ] **Core mock: Min Stack**
- [ ] Implement Queue Using Stacks
- [ ] Implement Stack Using Queues
- [ ] Evaluate Reverse Polish Notation
- [ ] Daily Temperatures
- [ ] Largest Rectangle in Histogram
- [ ] Sliding Window Maximum
- [ ] Design a Circular Queue
- [ ] **Core mock: Hit Counter**

### Hash tables and sets

- [ ] Contains Duplicate
- [ ] Valid Anagram
- [ ] Group Anagrams
- [ ] Longest Consecutive Sequence
- [ ] Subarray Sum Equals K
- [ ] Top K Frequent Elements
- [ ] Design HashMap From Scratch
- [ ] **Core mock: Insert/Delete/GetRandom in average $O(1)$**
- [ ] **Core mock: Time-Based Key-Value Store**
- [ ] **Core mock: LFU Cache**

### Heaps and priority queues

- [ ] Kth Largest Element in an Array
- [ ] K Closest Points to Origin
- [ ] Merge K Sorted Lists Using a Heap
- [ ] Task Scheduler
- [ ] Meeting Rooms II
- [ ] **Core mock: Median From Data Stream**
- [ ] **Core mock: Top-K Stream Tracker**

### Trees and binary search trees

- [ ] Maximum Depth of a Binary Tree
- [ ] Invert a Binary Tree
- [ ] Same Tree and Subtree of Another Tree
- [ ] Level-Order Traversal
- [ ] Validate a Binary Search Tree
- [ ] Kth Smallest Element in a BST
- [ ] Lowest Common Ancestor
- [ ] Diameter of a Binary Tree
- [ ] Serialize and Deserialize a Binary Tree
- [ ] **Core mock: BST With Insert, Find, and Erase**

### Tries

- [ ] **Core mock: Implement Trie**
- [ ] Add and Search Words With Wildcards
- [ ] Replace Words by Prefix
- [ ] Word Search II
- [ ] **Core mock: Autocomplete With Ranked Suggestions**

### Graphs

- [ ] Breadth-First and Depth-First Traversal
- [ ] Number of Islands
- [ ] Clone Graph
- [ ] Course Schedule
- [ ] Detect a Cycle in Directed and Undirected Graphs
- [ ] Connected Components
- [ ] Shortest Path in an Unweighted Graph
- [ ] Dijkstra's Shortest Path
- [ ] Minimum Spanning Tree
- [ ] **Core mock: Design and Implement a Graph Class**

### Disjoint sets

- [ ] Implement Union-Find With Path Compression and Union by Rank
- [ ] Number of Connected Components
- [ ] Redundant Connection
- [ ] Accounts Merge
- [ ] Kruskal's Minimum Spanning Tree

### Data-structure design mocks

- [ ] **Core mock: Browser History** using two stacks or a doubly linked list
- [ ] **Core mock: Undo/Redo Editor** using two stacks
- [ ] **Core mock: File-System Paths** using a trie or tree
- [ ] **Core mock: In-Memory Key-Value Store** with expiration
- [ ] **Core mock: Rate Limiter** using a queue, deque, or token bucket
- [ ] **Core mock: Leaderboard** using a hash table plus ordered structure
- [ ] **Core mock: All-O(1) Key Counter** using buckets plus hash tables
- [ ] **Core mock: Consistent Hash Ring** for assigning keys to servers
- [ ] **Core mock: Scheduler** using a heap plus cancellation lookup
- [ ] **Core mock: In-Memory Pub/Sub Queue** with subscriber cursors

## Recommended practice passes

1. **Recognition:** name the primary structure and target complexity in under two minutes.
2. **Implementation:** solve without notes and test boundary transitions.
3. **Explanation:** narrate invariants and tradeoffs while coding.
4. **Variation:** change one requirement, such as bounded memory, concurrency, expiration, or generic types.
5. **Mock:** choose a **Core mock**, use the 60-minute schedule, and do not restart after mistakes.

For combination problems, identify the operation that one data structure cannot make efficient and the second structure that supplies the missing capability.

## Completion check

You are done when you can implement the LRU cache from an empty file in 30-40 minutes, pass the edge cases without memory errors, derive each complexity, and explain every ownership and pointer update without relying on memorized code.