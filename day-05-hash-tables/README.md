# Day 5: Hash tables

Goal: trace a key from its hash value to a bucket or probe sequence, resolve collisions correctly, and explain how load factor drives resizing and rehashing.

## Setup

```sh
cmake -S . -B build
cmake --build build
./build/hash_table_practice
```

Start with `include/chained_hash_table.hpp`. Once all chaining assertions pass, move to `include/open_address_hash_table.hpp` and implement linear probing before quadratic probing.

The [exercise sheet](exercises/hash-table-drills.md) contains the implementation order, invariants, edge cases, and DSA-style follow-up problems.

## Complexity targets

| Operation | Average | Worst case |
| --- | ---: | ---: |
| insert, find, erase | $O(1)$ | $O(n)$ |
| resize and rehash | $O(n)$ | $O(n)$ |

Resizing is occasional, so insertion remains $O(1)$ amortized under a suitable hash function and load-factor policy.

## Completion check

You are done when you can draw collision chains and probe sequences, explain why tombstones preserve lookup, distinguish capacity from size, and rehash every live entry after resizing.

## Notes
With chaining, high load factor creates longer linked lists and slower searches. With open addressing, it causes longer probe sequences and clustering; performance deteriorates sharply as the table approaches full capacity.

Quadratic probing may fail to visit every slot. Common designs use a prime capacity and restrict load factor, often below 0.5, to guarantee finding an available slot. The exact requirements depend on the probing formula.