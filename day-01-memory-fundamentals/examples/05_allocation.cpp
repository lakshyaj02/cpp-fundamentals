#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>

struct Record {
    int id;

    explicit Record(int value) : id{value} {
        std::cout << "Record constructor\n";
    }

    ~Record() {
        std::cout << "Record destructor\n";
    }
};

int main() {
    Record* manual_cpp = new Record{1};
    delete manual_cpp;

    void* raw_storage = std::malloc(sizeof(Record));
    if (raw_storage == nullptr) {
        return 1;
    }
    Record* manual_c = new (raw_storage) Record{2};
    manual_c->~Record();
    std::free(raw_storage);

    auto preferred = std::make_unique<Record>(3);
    std::cout << "owned record id: " << preferred->id << '\n';
}