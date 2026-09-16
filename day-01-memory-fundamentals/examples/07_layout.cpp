#include <cstddef>
#include <iostream>

struct Mixed {
    char tag;
    int count;
    char state;
};

struct Reordered {
    int count;
    char tag;
    char state;
};

int main() {
    std::cout << "sizeof(char):      " << sizeof(char) << '\n';
    std::cout << "sizeof(int):       " << sizeof(int) << '\n';
    std::cout << "sizeof(int*):      " << sizeof(int*) << '\n';
    std::cout << "sizeof(Mixed):     " << sizeof(Mixed) << '\n';
    std::cout << "alignof(Mixed):    " << alignof(Mixed) << '\n';
    std::cout << "Mixed offsets:     " << offsetof(Mixed, tag) << ", "
              << offsetof(Mixed, count) << ", " << offsetof(Mixed, state) << '\n';
    std::cout << "sizeof(Reordered): " << sizeof(Reordered) << '\n';
    std::cout << "Reordered offsets: " << offsetof(Reordered, count) << ", "
              << offsetof(Reordered, tag) << ", " << offsetof(Reordered, state) << '\n';

    int values[5]{};
    int* pointer = values;
    std::cout << "array bytes:       " << sizeof(values) << '\n';
    std::cout << "pointer bytes:     " << sizeof(pointer) << '\n';
    std::cout << "array elements:    " << sizeof(values) / sizeof(values[0]) << '\n';
}