#include "circular_buffer.hpp"

#include <cassert>

int main() {
    CircularBuffer<int> buffer(3);

    // Uncomment these checks as you implement each operation.
    assert(buffer.empty());
    assert(buffer.push(10));
    assert(buffer.push(20));
    assert(buffer.push(30));
    assert(buffer.full());
    assert(!buffer.push(40));

    int value = -1;
    assert(buffer.pop(value) && value == 10);
    assert(buffer.push(40));
    assert(buffer.pop(value) && value == 20);
    assert(buffer.pop(value) && value == 30);
    assert(buffer.pop(value) && value == 40);
    assert(buffer.empty());
    assert(!buffer.pop(value));

    (void)value;
}