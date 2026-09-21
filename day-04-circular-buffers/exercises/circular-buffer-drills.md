# Circular buffer drills

Complete `include/circular_buffer.hpp` without using an STL container.

## Contract

- `push` inserts at the tail and returns `true`, or returns `false` without changing the buffer when full.
- `pop` writes the oldest value to its output argument and returns `true`, or returns `false` without changing the output when empty.
- The capacity is fixed after construction.
- A zero-capacity buffer is both empty and full, and rejects every push and pop.
- Every public operation should run in $O(1)$ time.

## State to understand

- `head_`: index of the next element to remove.
- `tail_`: index where the next element will be inserted.
- `capacity_`: number of physical slots in the array.
- `size_`: number of currently occupied slots.
- Wraparound: advancing past the final slot returns an index to zero.

Keep these invariants true after every operation:

```text
0 <= size_ <= capacity_
head_ < capacity_ and tail_ < capacity_  (when capacity_ > 0)
empty() exactly when size_ == 0
full() exactly when size_ == capacity_
```

## Implementation steps

1. Implement `empty()` and `full()`.
2. Implement the failure paths of `push()` and `pop()`.
3. Implement index advancement using modulo.
4. Trace a capacity-3 buffer through: push 10, 20, 30; pop; push 40; pop three times.
5. Verify that a failed pop does not modify its output argument.
6. Verify capacity 1 and capacity 0 separately.

## Tests to write

1. A new positive-capacity buffer is empty but not full.
2. Values leave in FIFO order.
3. Pushing to capacity makes the buffer full.
4. Pushing while full fails without overwriting data.
5. Popping while empty fails without changing the output.
6. Head and tail wrap around more than once.
7. Interleaved pushes and pops preserve order.
8. Capacity 1 transitions correctly among empty, full, and empty.
9. Capacity 0 safely rejects all operations.

## DSA-style problems that naturally use a circular queue

### 1. Design Circular Queue

Implement `MyCircularQueue(k)` with `enQueue`, `deQueue`, `Front`, `Rear`, `isEmpty`, and `isFull`. All operations must be $O(1)$.

### 2. Moving average from a data stream

Given a stream of integers and a window size `k`, return the average of the most recent `k` values after each insertion. Avoid shifting elements.

### 3. First negative number in every window

For every contiguous window of size `k`, report its first negative number, or zero if none exists. Store candidate indices in a queue.

### 4. Sliding-window maximum

Return the maximum in every window of size `k` in $O(n)$ time. Use a monotonic deque implemented over circular storage.

### 5. Recent request counter

Implement `ping(t)` to return how many requests occurred in the inclusive interval `[t - 3000, t]`. Timestamps arrive in increasing order.

### 6. Bounded producer-consumer queue

Design a fixed-capacity queue shared by producers and consumers. First implement the ring-buffer state transitions; then describe where synchronization and waiting would be required.

### 7. Round-robin CPU scheduler

Given jobs and a time quantum, repeatedly run the job at the front. Remove completed jobs and requeue unfinished jobs at the tail. Return completion times.

### 8. Network packet buffer

Packets arrive with processing durations into a bounded router buffer. Drop arrivals when full and report when each accepted packet begins processing.

### 9. Josephus elimination

Place `n` people in a queue and repeatedly rotate `k - 1` people from front to back before removing the next person. Return the survivor.

### 10. Hot-potato simulation

Players stand in a circle. After a changing number of passes, remove the current holder and continue from the next player until one remains.

For each problem, state whether you need a fixed-capacity circular queue, a dynamically growing queue, or a deque, and justify the choice.