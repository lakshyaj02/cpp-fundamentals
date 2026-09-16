#include <iostream>
#include <memory>
#include <string>

struct Tracer {
    std::string name;

    explicit Tracer(std::string value) : name{std::move(value)} {
        std::cout << "construct " << name << '\n';
    }

    ~Tracer() {
        std::cout << "destroy   " << name << '\n';
    }
};

int main() {
    Tracer outer{"outer"};
    {
        Tracer inner{"inner"};
        auto dynamic = std::make_unique<Tracer>("dynamic");
        std::cout << "leaving inner scope\n";
    }

    int* observer = nullptr;
    {
        int temporary = 42;
        observer = &temporary;
        std::cout << "observer is valid here: " << *observer << '\n';
    }
    observer = nullptr;
    std::cout << "observer reset after pointee lifetime ended: " << observer << '\n';
}