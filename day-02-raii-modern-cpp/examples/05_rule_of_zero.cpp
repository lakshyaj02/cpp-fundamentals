#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Record {
public:
    Record(std::string name, std::vector<int> samples)
        : name_(std::move(name)), samples_(std::move(samples)) {}

    void set_first_sample(int value) {
        samples_.front() = value;
    }

    int first_sample() const {
        return samples_.front();
    }

private:
    std::string name_;
    std::vector<int> samples_;
};

int main() {
    Record original{"sensor", {10, 20, 30}};
    Record copied = original;
    copied.set_first_sample(99);

    Record moved = std::move(copied);

    std::cout << "independent copy: " << original.first_sample() << '\n';
    std::cout << "moved value: " << moved.first_sample() << '\n';
    // Once moved cannot access the original object safely
    // std::cout << "copied value: " << copied.first_sample() << '\n';
}