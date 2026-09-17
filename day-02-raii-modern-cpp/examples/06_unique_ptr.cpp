#include <cstdio>
#include <iostream>
#include <memory>
#include <utility>

class Job {
public:
    explicit Job(int id) : id_(id) {
        std::cout << "create job " << id_ << '\n';
    }

    ~Job() {
        std::cout << "destroy job " << id_ << '\n';
    }

    void run() const {
        std::cout << "run job " << id_ << '\n';
    }

private:
    int id_;
};

std::unique_ptr<Job> make_job(int id) {
    return std::make_unique<Job>(id);
}

void consume(std::unique_ptr<Job> job) {
    job->run();
}

int main() {
    auto job = make_job(7);
    Job* observer = job.get();
    observer->run();

    auto new_owner = std::move(job);
    std::cout << "old owner empty: " << std::boolalpha << (job == nullptr) << '\n';
    consume(std::move(new_owner));

    using File = std::unique_ptr<std::FILE, decltype(&std::fclose)>;
    File file{std::tmpfile(), &std::fclose};
    if (file) {
        std::fputs("RAII closes this file\n", file.get());
    }
}