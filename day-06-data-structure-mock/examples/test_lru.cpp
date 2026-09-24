#include "lru.hpp"

#include <cassert>
#include <iostream>

void test_missing_key() {
	LRUCache cache(2);

	assert(cache.get(42) == -1);
}

void test_insert_and_get() {
	LRUCache cache(2);

	cache.put(1, 10);

	assert(cache.get(1) == 10);
}

void test_update_existing_key() {
	LRUCache cache(2);

	cache.put(1, 10);
	cache.put(1, 99);

	assert(cache.get(1) == 99);
}

void test_evicts_least_recently_used_key() {
	LRUCache cache(2);

	cache.put(1, 10);
	cache.put(2, 20);
	cache.put(3, 30);

	assert(cache.get(1) == -1);
	assert(cache.get(2) == 20);
	assert(cache.get(3) == 30);
}

void test_get_changes_eviction_order() {
	LRUCache cache(2);

	cache.put(1, 10);
	cache.put(2, 20);
	assert(cache.get(1) == 10);
	cache.put(3, 30);

	assert(cache.get(1) == 10);
	assert(cache.get(2) == -1);
	assert(cache.get(3) == 30);
}

void test_update_changes_eviction_order() {
	LRUCache cache(2);

	cache.put(1, 10);
	cache.put(2, 20);
	cache.put(1, 11);
	cache.put(3, 30);

	assert(cache.get(1) == 11);
	assert(cache.get(2) == -1);
	assert(cache.get(3) == 30);
}

void test_capacity_one() {
	LRUCache cache(1);

	cache.put(1, 10);
	assert(cache.get(1) == 10);

	cache.put(2, 20);
	assert(cache.get(1) == -1);
	assert(cache.get(2) == 20);
}

void test_negative_keys_and_values() {
	LRUCache cache(2);

	cache.put(-1, -10);
	cache.put(-2, -20);

	assert(cache.get(-1) == -10);
	assert(cache.get(-2) == -20);
}

void test_zero_capacity() {
	LRUCache cache(0);

	cache.put(1, 10);

	assert(cache.get(1) == -1);
}

int main() {
	test_missing_key();
	test_insert_and_get();
	test_update_existing_key();
	test_evicts_least_recently_used_key();
	test_get_changes_eviction_order();
	test_update_changes_eviction_order();
	test_capacity_one();
	test_negative_keys_and_values();
	test_zero_capacity();

	std::cout << "All LRU cache tests passed.\n";
}
