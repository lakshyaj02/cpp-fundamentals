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
        std::cout << "deep copy\n";
    }

    IntBuffer& operator=(const IntBuffer& other) {
        IntBuffer copy{other};
        swap(copy);
        return *this;
    }

    IntBuffer(IntBuffer&& other) noexcept
        : size_(std::exchange(other.size_, 0)),
          data_(std::exchange(other.data_, nullptr)) {
        std::cout << "move ownership\n";
    }

    IntBuffer& operator=(IntBuffer&& other) noexcept {
        IntBuffer moved{std::move(other)};
        swap(moved);
        return *this;
    }

    void swap(IntBuffer& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    std::size_t size() const {
        return size_;
    }

    const int* data() const {
        return data_;
    }

private:
    std::size_t size_{};
    int* data_{};
};

int main() {
    IntBuffer source{1'000};
    const int* original_allocation = source.data();

    IntBuffer destination{std::move(source)};
    std::cout << "allocation transferred: " << std::boolalpha
              << (destination.data() == original_allocation) << '\n';
    std::cout << "moved-from size: " << source.size() << '\n';

    IntBuffer target{5};
    target = std::move(destination);
    std::cout << "move-assigned size: " << target.size() << '\n';
    std::cout << "move-from size: " << destination.size() << '\n';
}