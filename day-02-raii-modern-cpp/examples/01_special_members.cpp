#include <iostream>
#include <string>
#include <utility>

class Trace {
public:
    explicit Trace(std::string name) : name_(std::move(name)) {
        std::cout << "construct " << name_ << '\n';
    }

    ~Trace() {
        std::cout << "destroy " << name_ << '\n';
    }

    Trace(const Trace& other) : name_(other.name_ + "-copy") {
        std::cout << "copy-construct " << name_ << " from " << other.name_ << '\n';
    }

    Trace& operator=(const Trace& other) {
        std::cout << "copy-assign " << name_ << " from " << other.name_ << '\n';
        name_ = other.name_ + "-copy-assigned";
        return *this;
    }

    Trace(Trace&& other) noexcept : name_(std::move(other.name_)) {
        std::cout << "move-construct " << name_ << '\n';
    }

    Trace& operator=(Trace&& other) noexcept {
        std::cout << "move-assign " << name_ << " from " << other.name_ << '\n';
        name_ = std::move(other.name_);
        return *this;
    }

private:
    std::string name_;
};

int main() {
    Trace original{"original"};
    Trace copied{original};

    Trace copy_target{"copy-target"};
    copy_target = original;

    Trace moved{std::move(copied)};

    Trace move_target{"move-target"};
    move_target = std::move(moved);

    std::cout << "leaving scope\n";
}