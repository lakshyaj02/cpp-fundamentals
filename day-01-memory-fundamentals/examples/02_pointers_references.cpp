#include <iostream>

void increment_by_pointer(int* value) {
    if (value != nullptr) {
        ++*value;
    }
}

void increment_by_reference(int& value) {
    ++value;
}

int main() {
    int value = 40;
    int* pointer = &value;
    int& reference = value;

    std::cout << "object address:    " << &value << '\n';
    std::cout << "pointer value:     " << pointer << '\n';
    std::cout << "pointer's address: " << &pointer << '\n';
    std::cout << "reference address: " << &reference << '\n';

    increment_by_pointer(pointer);
    increment_by_reference(reference);
    increment_by_pointer(nullptr);
    std::cout << "final value: " << value << '\n';
}