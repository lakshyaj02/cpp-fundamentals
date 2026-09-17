# Interview drills

Answer aloud before writing code. For each ownership question, draw solid owning arrows and dashed observing arrows.

## 1. Construction or assignment?

Name the operation selected on each marked line:

```cpp
Widget a;                 // A
Widget b = a;             // B
Widget c;
c = a;                    // C
Widget d = std::move(a);  // D
b = std::move(c);         // E
```

What must remain true about `a` and `c` after their moves?

## 2. Find the ownership bug

```cpp
class Buffer {
public:
    explicit Buffer(std::size_t size) : data_(new int[size]) {}
    ~Buffer() { delete[] data_; }

private:
    int* data_;
};

Buffer first{10};
Buffer second = first;
```

Explain the failure and give three valid design choices.

## 3. Exception safety

Why is "delete the old allocation, then allocate and copy the new one" a poor copy-assignment implementation? Explain how copy-and-swap changes the guarantee.

## 4. Move semantics

After moving a resource handle, why must the source usually be reset? Why should a move constructor often be `noexcept`? Does `std::move(value)` itself invoke a move constructor?

## 5. Rule selection

Choose Rule of 3, 5, or 0 and justify the choice:

1. A class containing only `std::string` and `std::vector<int>`.
2. A teaching class that directly owns an array allocated with `new[]` and must be copyable.
3. A production class with exclusive heap ownership that can store the object in `std::unique_ptr`.

## 6. API ownership

Choose a parameter type for each function: `T&`, `const T&`, `T*`, `unique_ptr<T>`, `shared_ptr<T>`, or a smart-pointer reference.

1. Read an object without extending its lifetime.
2. Mutate a required borrowed object.
3. Accept an optional borrowed object.
4. Permanently take exclusive ownership.
5. Store another shared owner.
6. Replace the caller's `unique_ptr`.

## 7. Reference counts

Predict each printed count:

```cpp
auto a = std::make_shared<int>(42);
std::weak_ptr<int> w = a;
std::cout << a.use_count() << '\n';       // A
{
    auto b = a;
    auto c = w.lock();
    std::cout << a.use_count() << '\n';   // B
}
std::cout << a.use_count() << '\n';       // C
a.reset();
std::cout << w.expired() << '\n';         // D
```

## 8. Shared ownership cycle

Two `Node` objects each store a `shared_ptr<Node>` to the other. Explain why neither destructor runs and repair the ownership graph.

## 9. Code review

What is wrong with this code?

```cpp
Widget* raw = new Widget;
std::shared_ptr<Widget> first{raw};
std::shared_ptr<Widget> second{raw};
```

How should `first` and `second` be created?

## 10. Design question

Design a movable, non-copyable RAII wrapper around an integer file descriptor. State its invariant, destructor behavior, move behavior, and borrowing API. What subtle bug must move assignment avoid?