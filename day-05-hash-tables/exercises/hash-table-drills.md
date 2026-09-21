# Hash table drills

Implement both headers in `include/`. Begin with separate chaining, then implement open addressing with linear probing before adding quadratic probing.

## Mental model

```text
hash(key) -> bucket or starting slot -> collision resolution
```

A hash function does not directly identify an entry. It produces a number that must be reduced to the table's current range. Different keys can map to the same index, so correctness depends on collision resolution and equality checks.

## Separate chaining

Each bucket owns a linked list of entries:

```text
buckets_[index] -> [key, value] -> [key, value] -> null
```

Implement in this order:

1. `bucket_index`
2. mutable and const `find`
3. `insert_or_assign`
4. `erase`
5. `load_factor`
6. `rehash`

`insert_or_assign` should return `true` for a newly inserted key and `false` when it updates an existing key.

## Open addressing

Every entry lives directly in the slot array:

```text
[occupied][empty][tombstone][occupied][empty]
```

Implement in this order:

1. linear `probe_index`
2. mutable and const `find`
3. `insert_or_assign`
4. `erase` using tombstones
5. `load_factor`
6. `rehash`
7. quadratic `probe_index`

For a starting index $h$ and attempt number $i$:

$$
\text{linear}(i) = (h + i) \bmod m
$$

$$
\text{quadratic}(i) = (h + i^2) \bmod m
$$

## Questions to answer before coding

1. Why must lookup compare keys even after finding the correct bucket?
2. Why does erasing an open-addressed entry require a tombstone?
3. When may lookup stop at an empty slot, and why may it not stop at a tombstone?
4. Should inserting into a tombstone continue probing for an existing copy of the key?
5. Why must resizing rehash entries instead of copying them to identical indices?
6. What is the difference between `size_`, capacity, and the number of tombstones?
7. How does a high load factor affect chaining and open addressing differently?
8. What table-size restrictions can quadratic probing require?

## Tests to add

1. Insert, find, update, and erase one key.
2. Force several distinct keys to collide with a custom hash function.
3. Erase the first key in a collision chain and still find later keys.
4. Reuse a tombstone while preserving access to keys later in the probe sequence.
5. Update an existing key without increasing `size_`.
6. Trigger multiple resizes and verify every key-value pair.
7. Compare linear and quadratic probe positions by hand.
8. Verify const lookup.

## DSA-style problems

1. **Two Sum:** map each visited value to its index and search for the complement.
2. **Contains Duplicate:** track values already encountered.
3. **First Unique Character:** count character frequencies, then scan in original order.
4. **Group Anagrams:** hash a canonical representation of each word to a group.
5. **Longest Consecutive Sequence:** store all values and begin counting only at sequence starts.
6. **Subarray Sum Equals K:** map prefix sums to their occurrence counts.
7. **LRU Cache:** combine a hash table with a doubly linked list for $O(1)$ access and eviction.
8. **Design HashMap:** implement integer keys without using the standard hash-table containers.
9. **Design Underground System:** map active journeys and route pairs to aggregate statistics.
10. **Insert Delete GetRandom O(1):** combine a value-to-index hash table with a dynamic array.

For each problem, identify what becomes the key, what becomes the value, and how collisions remain invisible to the caller.