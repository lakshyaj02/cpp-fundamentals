#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Connection {
public:
    explicit Connection(std::string endpoint) : endpoint_(std::move(endpoint)) {
        std::cout << "open " << endpoint_ << '\n';
    }

    ~Connection() {
        std::cout << "close " << endpoint_ << '\n';
    }

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    void send() const {
        std::cout << "send to " << endpoint_ << '\n';
    }

private:
    std::string endpoint_;
};

void perform_request(bool fail) {
    Connection connection{"service:443"};
    connection.send();

    if (fail) {
        throw std::runtime_error{"request failed"};
    }
}

int main() {
    try {
        perform_request(true);
    } catch (const std::exception& error) {
        std::cout << "caught: " << error.what() << '\n';
    }
}