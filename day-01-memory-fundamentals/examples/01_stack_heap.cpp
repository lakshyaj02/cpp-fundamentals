#include <iostream>
#include <memory>

int global_value = 10;

int main() {
    int stack_value = 20;
    auto heap_value = std::make_unique<int>(30);

    std::cout << "global/static storage: " << &global_value << " -> " << global_value << '\n';
    std::cout << "stack object:          " << &stack_value << " -> " << stack_value << '\n';
    std::cout << "pointer object:        " << &heap_value << '\n';
    std::cout << "heap object:           " << heap_value.get() << " -> " << *heap_value << '\n';

    // Addresses vary between runs. Their relationships and ownership matter.
}