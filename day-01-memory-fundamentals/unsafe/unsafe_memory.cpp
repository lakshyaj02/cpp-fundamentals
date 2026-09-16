#include <cstdlib>
#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: unsafe_memory <leak|use-after-free|out-of-bounds>\n";
        return 1;
    }

    const std::string_view mode{argv[1]};
    if (mode == "leak") {
        [[maybe_unused]] int* lost = new int[100];
    } else if (mode == "use-after-free") {
        int* value = new int{42};
        delete value;
        std::cout << *value << '\n';
    } else if (mode == "out-of-bounds") {
        int values[3]{1, 2, 3};
        std::cout << values[3] << '\n';
    } else {
        std::cerr << "unknown mode\n";
        return 1;
    }
}