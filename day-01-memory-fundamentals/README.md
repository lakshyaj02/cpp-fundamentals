# Day 1: C++ memory fundamentals

Goal: given a short program, draw the objects, storage regions, addresses, ownership arrows, and exact points where lifetimes begin and end.

## Setup

Requirements: a C++20 compiler and CMake 3.20 or newer.

```sh
cmake -S . -B build
cmake --build build
```

Run an example with `./build/<name>`. Available names:

| Executable | Topics |
| --- | --- |
| `stack_heap` | automatic, static, and dynamic storage |
| `pointers_references` | pointers, references, nullability, aliases |
| `pointer_arithmetic` | pointer arithmetic, arrays, `span`, contiguous memory |
| `lifetime` | construction, destruction, scope, dangling observers |
| `allocation` | `new`/`delete`, `malloc`/`free`, placement construction, RAII |
| `copy_semantics` | shallow versus deep copy |
| `layout` | alignment, padding, offsets, `sizeof` |

Addresses differ across runs and platforms. Study relationships between addresses, not particular hexadecimal values.

## Study loop

1. Read one source file without running it.
2. Draw its memory state after each important line using the notation below.
3. Predict output, destruction order, and invalidation points.
4. Build and run the executable.
5. Explain any mismatch in one sentence.
6. Complete [the worksheet](exercises/memory-diagrams.md), then check [the answers](answers/memory-diagrams.md).

Suggested order: storage and aliases (45 min), arithmetic and contiguity (35 min), lifetime and allocation (60 min), copies (30 min), layout and `sizeof` (35 min), worksheet and review (45 min).

## Diagram notation

```text
STACK: main frame                 HEAP
+----------------------+         +----------------+
| value: int = 42      | <-----+ | allocation     |
| pointer: int* = 0x.. | ------+ | int = 99       |
+----------------------+         +----------------+
                                      owner: pointer
```

Use a solid arrow for ownership and a dashed arrow for a non-owning observer. A reference is an alias, not a second copy of the referred object. Cross out an object when its lifetime ends; any remaining arrow to it is dangling.

## Rules to retain

- "Stack" and "heap" are common implementation terms; the C++ language specifies storage duration and object lifetime.
- A pointer is an object that stores an address and may be null or reseated. A reference is an alias that must be initialized and cannot be reseated.
- Pointer arithmetic is defined only within one array object, including formation of its one-past-the-end pointer. Never dereference one-past-the-end.
- Storage can exist without a live object in it. Access through a pointer or reference requires a live object of an allowed type.
- A dangling pointer still stores an address, but the object it identified is no longer alive. Dereferencing it is undefined behavior.
- A leak is a live allocation that the program can no longer release. RAII makes cleanup follow object lifetime.
- Pair `new` with `delete`, `new[]` with `delete[]`, and `malloc` with `free`. Never mix families.
- `malloc` and `free` do not call constructors or destructors. Prefer standard containers and smart pointers in C++ application code.
- A shallow copy duplicates handles or addresses; a deep copy duplicates owned content. Raw owning pointers require carefully designed copy/move/destruction behavior.
- `sizeof(T)` includes padding and is implementation-dependent. `alignof(T)` states valid placement boundaries.
- Built-in arrays, `std::array`, and `std::vector` elements are contiguous. Linked containers are not.

## Sanitizer lab

The normal examples avoid undefined behavior. The optional unsafe executable exists only to let AddressSanitizer diagnose mistakes:

```sh
cmake -S . -B build-asan -DENABLE_UNSAFE_LABS=ON
cmake --build build-asan
./build-asan/unsafe_memory use-after-free
./build-asan/unsafe_memory out-of-bounds
ASAN_OPTIONS=detect_leaks=1 ./build-asan/unsafe_memory leak
```

Each unsafe run may terminate with a nonzero exit code. Read the first error, allocation site, and deallocation site. Do not imitate these cases in production code.

## References

Read these in order; cppreference is dense, so use the examples and summary sections first.

1. [C++ object model, size, and alignment](https://en.cppreference.com/w/cpp/language/object.html) - objects, storage, representation, padding, and alignment.
2. [Storage duration](https://en.cppreference.com/w/cpp/language/storage_duration.html) - automatic, static, thread, and dynamic storage duration.
3. [Object lifetime](https://en.cppreference.com/w/cpp/language/lifetime.html) - lifetime start/end, temporaries, storage reuse, and invalid access.
4. [Pointers](https://en.cppreference.com/w/cpp/language/pointer.html) and [references](https://en.cppreference.com/w/cpp/language/reference.html) - semantics and dangling cases.
5. [`new` expression](https://en.cppreference.com/w/cpp/language/new.html), [`delete` expression](https://en.cppreference.com/w/cpp/language/delete.html), [`std::malloc`](https://en.cppreference.com/w/cpp/memory/c/malloc.html), and [`std::free`](https://en.cppreference.com/w/cpp/memory/c/free.html).
6. [`sizeof`](https://en.cppreference.com/w/cpp/language/sizeof.html), [`alignof`](https://en.cppreference.com/w/cpp/language/alignof.html), and [`offsetof`](https://en.cppreference.com/w/cpp/types/offsetof.html).
7. [`std::vector` contiguous storage](https://en.cppreference.com/w/cpp/container/vector.html) and [`std::span`](https://en.cppreference.com/w/cpp/container/span.html).
8. [C++ Core Guidelines: resource management](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource) - RAII, ownership, smart pointers, and guidance on raw allocation.
9. [The rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three.html) - correct copy and move behavior for resource-owning classes.
10. [Clang AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) - detecting use-after-free, bounds errors, invalid frees, and leaks.

## Completion check

You are done when you can draw all six worksheet diagrams, identify every owner and observer, predict destruction order, explain every padding byte in the layout exercise, and make the sanitizer report each intentional defect.