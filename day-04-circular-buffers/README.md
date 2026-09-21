# Day 4: Circular buffers and queues

Goal: implement a fixed-capacity FIFO queue backed by a circular array and explain every index transition.

## Setup

```sh
cmake -S . -B build
cmake --build build
./build/circular_buffer_practice
```

Start in `include/circular_buffer.hpp`. Implement one method at a time and uncomment the matching assertions in `examples/circular_buffer_practice.cpp`.

Use the [exercise sheet](exercises/circular-buffer-drills.md) for invariants, edge cases, and DSA-style follow-up problems.

## Completion check

You are done when you can draw the physical array after each operation, distinguish `head_` from `tail_`, explain why equal indices can represent both empty and full states, and preserve FIFO order across repeated wraparound.