#include "chained_hash_table.hpp"
#include "open_address_hash_table.hpp"

#include <cassert>
#include <string>

int main() {
    ChainedHashTable<std::string, int> chained(4);
    assert(chained.empty());
    assert(chained.size() == 0);
    assert(chained.bucket_count() == 4);

    // Uncomment as you implement separate chaining.
    assert(chained.insert_or_assign("Ada", 10));
    assert(chained.insert_or_assign("Grace", 20));
    assert(chained.contains("Ada"));
    assert(*chained.find("Grace") == 20);
    assert(!chained.insert_or_assign("Ada", 30));
    assert(*chained.find("Ada") == 30);
    assert(chained.erase("Ada"));
    assert(!chained.contains("Ada"));

    OpenAddressHashTable<int, std::string> open(8, ProbeStrategy::linear);
    assert(open.empty());
    assert(open.size() == 0);
    assert(open.capacity() == 8);

    // Uncomment as you implement open addressing.
    assert(open.insert_or_assign(1, "one"));
    assert(open.insert_or_assign(9, "nine")); // Collides with 1 at capacity 8.
    assert(*open.find(9) == "nine");
    assert(open.erase(1));
    assert(open.contains(9)); // Lookup must continue past the tombstone.
    assert(open.insert_or_assign(17, "seventeen"));
}