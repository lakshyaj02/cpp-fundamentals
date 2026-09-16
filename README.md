# C++ Fundamentals

A practical, example-driven study repository for building a strong mental model of modern C++. Each topic combines small runnable programs, prediction exercises, diagrams, and references to authoritative documentation.

## Learning approach

For each example:

1. Read the source before running it.
2. Predict the output and relevant program state.
3. Draw objects, addresses, ownership, and lifetimes when memory is involved.
4. Build and run the example.
5. Explain any difference between the prediction and observed behavior.

The examples use low-level language features to make their behavior visible, then connect them to safer modern C++ practices such as RAII, standard containers, and smart pointers.

## Curriculum

| Module | Topics | Status |
| --- | --- | --- |
| [Day 1: Memory fundamentals](day-01-memory-fundamentals/) | Stack and heap, pointers, references, lifetime, allocation, copying, alignment, and contiguous memory | Complete |

## Quick start

Requirements:

- A C++20-compatible compiler
- CMake 3.20 or newer

Build the Day 1 examples:

```sh
cd day-01-memory-fundamentals
cmake -S . -B build
cmake --build build
```

Run an individual example:

```sh
./build/stack_heap
./build/pointers_references
./build/layout
```

See the [Day 1 study guide](day-01-memory-fundamentals/README.md) for the complete executable list, memory-diagram worksheet, sanitizer lab, and reading references.

## Repository structure

```text
cpp-fundamentals/
├── README.md
└── day-01-memory-fundamentals/
    ├── examples/       # Runnable, defined-behavior demonstrations
    ├── exercises/      # Memory-diagram prompts
    ├── answers/        # Exercise explanations
    ├── unsafe/         # Optional sanitizer-only defect examples
    ├── CMakeLists.txt
    └── README.md       # Detailed lesson and reference guide
```

## Safety note

Programs under `unsafe/` intentionally demonstrate undefined behavior and are excluded from normal builds. Run them only with the sanitizer configuration documented in the relevant module.

## References

The study guides prioritize:

- [cppreference](https://en.cppreference.com/) for language and standard-library details
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) for modern design and resource-management practices
- [Clang AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) for diagnosing memory defects