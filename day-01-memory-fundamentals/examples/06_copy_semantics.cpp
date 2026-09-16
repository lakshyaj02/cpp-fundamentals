#include <iostream>
#include <vector>

struct ShallowView {
    int* data;
};

struct DeepValue {
    std::vector<int> data;
};

int main() {
    int shared = 10;
    ShallowView first_view{&shared};
    ShallowView second_view = first_view;
    *second_view.data = 99;

    std::cout << "shallow copies point to same object: " << std::boolalpha
              << (first_view.data == second_view.data) << '\n';
    std::cout << "value through first view: " << *first_view.data << '\n';

    DeepValue first_value{{1, 2, 3}};
    DeepValue second_value = first_value;
    second_value.data[0] = 99;

    std::cout << "deep copy has separate storage: "
              << (first_value.data.data() != second_value.data.data()) << '\n';
    std::cout << "first element values: " << first_value.data[0] << ", "
              << second_value.data[0] << '\n';
}