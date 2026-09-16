#include <array>
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

template <typename Range>
void print_addresses(const Range& values) {
    for (std::size_t index = 0; index < values.size(); ++index) {
        std::cout << index << ": " << &values[index] << " -> " << values[index] << '\n';
    }
}

int main() {
    std::array<int, 4> array{10, 20, 30, 40};
    int* first = array.data();
    int* one_past_end = first + array.size();

    print_addresses(array);
    std::cout << "byte stride: "
              << reinterpret_cast<const char*>(first + 1) - reinterpret_cast<const char*>(first)
              << '\n';
    std::cout << "element distance: " << one_past_end - first << '\n';

    std::vector<int> vector{50, 60, 70, 80};
    std::span<const int> view{vector};
    std::cout << "vector is contiguous: " << std::boolalpha
              << (&view[1] == view.data() + 1) << '\n';

    // one_past_end may be compared or subtracted, but never dereferenced.
}