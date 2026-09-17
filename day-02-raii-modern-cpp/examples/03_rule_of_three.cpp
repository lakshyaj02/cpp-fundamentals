#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>

class IntBuffer {
public:
    explicit IntBuffer(std::size_t size)
        : size_(size), data_(size == 0 ? nullptr : new int[size]{}) {}

    ~IntBuffer() {
        delete[] data_;
    }

    IntBuffer(const IntBuffer& other)
        : IntBuffer(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    IntBuffer& operator=(const IntBuffer& other) {
        IntBuffer copy{other};
        swap(copy);
        return *this;
    }

    void swap(IntBuffer& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    int& operator[](std::size_t index) {
        return data_[index];
    }

    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    const int* data() const {
        return data_;
    }

private:
    std::size_t size_{};
    int* data_{};
};

int main() {
    IntBuffer original{3};
    original[0] = 10;

    IntBuffer copied{original};
    copied[0] = 99;

    IntBuffer assigned{1};
    assigned = original;
    const IntBuffer& alias = assigned;
    assigned = alias;

    std::cout << "separate allocations: " << std::boolalpha
              << (original.data() != copied.data()) << '\n';
    std::cout << "values: " << original[0] << ", " << copied[0] << ", "
              << assigned[0] << '\n';
}