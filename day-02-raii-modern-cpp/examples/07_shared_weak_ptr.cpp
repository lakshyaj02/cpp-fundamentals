#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Service {
public:
    explicit Service(std::string name) : name_(std::move(name)) {
        std::cout << "start " << name_ << '\n';
    }

    ~Service() {
        std::cout << "stop " << name_ << '\n';
    }

    void ping() const {
        std::cout << "ping " << name_ << '\n';
    }

private:
    std::string name_;
};

int main() {
    std::weak_ptr<Service> observer;

    {
        auto first_owner = std::make_shared<Service>("cache");
        observer = first_owner;
        std::cout << "owners: " << first_owner.use_count() << '\n';

        {
            auto second_owner = first_owner;
            std::cout << "owners after copy: " << first_owner.use_count() << '\n';

            if (auto service = observer.lock()) {
                service->ping();
                std::cout << "owners while locked: " << service.use_count() << '\n';
            }
        }

        std::cout << "owners after inner scope: " << first_owner.use_count() << '\n';
    }

    std::cout << "observer expired: " << std::boolalpha << observer.expired() << '\n';
    std::cout << "lock after destruction is empty: " << (observer.lock() == nullptr) << '\n';
}