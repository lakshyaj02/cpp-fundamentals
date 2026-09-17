# Day 2: RAII and modern C++

Goal: given a resource-owning type, explain exactly who owns the resource, which special member functions run, and whether copying, moving, or destruction is correct.

## Setup

Requirements: a C++20 compiler and CMake 3.20 or newer.

```sh
cmake -S . -B build
cmake --build build
```

Run an example with `./build/<name>`:

| Executable | Topics |
| --- | --- |
| `special_members` | constructor, destructor, copy and move operations |
| `raii` | deterministic cleanup during normal flow and exceptions |
| `rule_of_three` | deep copy for a raw resource owner |
| `rule_of_five` | efficient ownership transfer with moves |
| `rule_of_zero` | composing standard RAII types |
| `unique_ownership` | `unique_ptr`, transfer, factories, custom deleters |
| `shared_ownership` | `shared_ptr`, control blocks, `weak_ptr`, cycles |

## Study loop

1. Read one source file without running it.
2. Mark every construction, assignment, ownership transfer, and destruction.
3. Predict the output and the state of moved-from objects.
4. Build and run it.
5. Explain which object owns each resource at every step.
6. Complete [the interview drills](exercises/interview-drills.md), then check [the answers](answers/interview-drills.md).

Suggested order: special members and RAII (50 min), Rule of 3/5/0 (75 min), smart pointers (70 min), interview drills (45 min).

## The six operations

```cpp
class Widget {
public:
    Widget();                              // constructor
    ~Widget();                             // destructor
    Widget(const Widget& other);           // copy constructor
    Widget& operator=(const Widget& other);// copy assignment
    Widget(Widget&& other) noexcept;       // move constructor
    Widget& operator=(Widget&& other) noexcept; // move assignment
};
```

- Construction starts a new object's lifetime; assignment changes an already-live object.
- Copying preserves the source and creates independent value state.
- Moving transfers reusable resources from a non-const source. The source remains valid but its value is generally unspecified.
- Destruction releases resources owned by the object. Destructors should not throw.
- Self-assignment must remain correct. Prefer implementations that are naturally safe rather than scattered address checks.
- Mark resource-transfer moves `noexcept` when they truly cannot throw. Standard containers can then prefer moving during reallocation.
- `std::move` does not move anything itself; it enables overload resolution to select move operations.

## Rule of 3, 5, and 0

**Rule of 3:** if a class directly owns a raw resource and needs a custom destructor, it probably needs a copy constructor and copy assignment operator. Otherwise, generated copying may duplicate the handle and cause double release.

**Rule of 5:** once such a class manages copying, consider move construction and move assignment too. A move should transfer ownership and leave the source destructible and assignable.

**Rule of 0:** the preferred design. Put ownership in RAII members such as `std::vector`, `std::string`, or smart pointers, and declare none of the five special members. Compiler-generated operations compose the correct member behavior.

These are design guidelines, not language rules. A polymorphic base class or a non-copyable resource wrapper may intentionally declare a different set of operations.

## RAII

Resource Acquisition Is Initialization binds a resource's lifetime to an object's lifetime:

1. Acquire the resource during construction.
2. Establish the class invariant only after acquisition succeeds.
3. Release the resource in the destructor.
4. Let scope exit perform cleanup on every path, including exceptions and early returns.

RAII applies to memory, files, sockets, mutex locks, database transactions, and any paired acquire/release API. `std::vector`, `std::string`, streams, `std::lock_guard`, and smart pointers are RAII types.

## Ownership vocabulary

| Type | Meaning | Copyable? | Typical use |
| --- | --- | --- | --- |
| `std::unique_ptr<T>` | exactly one owner | No | default heap ownership and transfer |
| `std::shared_ptr<T>` | shared lifetime through a control block | Yes | genuinely shared, dynamic lifetime |
| `std::weak_ptr<T>` | non-owning observer of a `shared_ptr` object | Yes | cycle breaking and optional observation |
| `T*`, `T&` | normally non-owning access | Yes | borrowing when lifetime is guaranteed elsewhere |

Prefer `std::make_unique` and `std::make_shared`. Pass smart pointers only when the function participates in ownership: by value to take/share ownership, or by reference when it may reseat the pointer. Pass `T&` or `T*` for ordinary borrowing.

`shared_ptr` does not make the pointed-to object thread-safe. Separate `shared_ptr` instances may safely adjust the shared control block concurrently, but access to the object still needs its own synchronization.

## Interview traps

- A user-declared destructor suppresses implicit move generation. The type may still appear move-constructible because its copy constructor accepts rvalues.
- Copying two `shared_ptr` objects increments a reference count; constructing two independent `shared_ptr` objects from the same raw pointer creates two control blocks and can double-delete.
- A `weak_ptr` must be converted with `lock()`. The result is either an owning `shared_ptr` or empty if the object expired.
- A cycle of owning `shared_ptr` edges never reaches a strong count of zero. Make at least one back-edge non-owning with `weak_ptr`.
- `unique_ptr<T>` needs a complete `T` where its destructor runs. For the pImpl pattern, define the owning class's destructor in a source file where `T` is complete.
- Returning a local object by value usually uses guaranteed or optional copy elision. Do not add `std::move` to a local return merely to force movement; it can inhibit elision.

## References

1. [Special member functions](https://en.cppreference.com/w/cpp/language/member_functions.html#Special_member_functions).
2. [Copy constructors](https://en.cppreference.com/w/cpp/language/copy_constructor.html), [copy assignment](https://en.cppreference.com/w/cpp/language/copy_assignment.html), [move constructors](https://en.cppreference.com/w/cpp/language/move_constructor.html), and [move assignment](https://en.cppreference.com/w/cpp/language/move_assignment.html).
3. [Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three.html).
4. [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr.html), [`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr.html), and [`std::weak_ptr`](https://en.cppreference.com/w/cpp/memory/weak_ptr.html).
5. [C++ Core Guidelines: resource management](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource).

## Completion check

You are done when you can implement a small resource owner correctly, explain why Rule of 0 is preferable, choose the right smart pointer for an ownership graph, identify a `shared_ptr` cycle, and predict every special-member call in the examples.