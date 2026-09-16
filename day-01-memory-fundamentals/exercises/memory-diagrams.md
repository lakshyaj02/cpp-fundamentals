# Memory diagram worksheet

For every snippet, draw separate boxes for stack frames, static storage, and heap allocations. Inside each box write the object name, type, value, and lifetime. Draw arrows for pointers and references, and cross out objects when their lifetime ends.

## 1. Pointer and reference aliases

```cpp
int value = 7;
int* pointer = &value;
int& reference = value;
reference = 9;
```

Draw the state after every line. How many `int` objects exist? Which names or values identify the same object?

## 2. Dynamic array

```cpp
int* data = new int[3]{10, 20, 30};
int* middle = data + 1;
delete[] data;
data = nullptr;
```

Draw the state before and after `delete[]`. Is `middle` changed by assigning `nullptr` to `data`? When does each pointer dangle?

## 3. Scope and lifetime

```cpp
int* observer = nullptr;
{
    int local = 42;
    observer = &local;
}
```

Mark the exact point where `observer` becomes dangling. Does the pointer object still exist?

## 4. Shallow copy

```cpp
struct Buffer { int* data; };
Buffer first{new int[2]{1, 2}};
Buffer second = first;
second.data[0] = 8;
```

Draw both `Buffer` objects and the allocation. What value does `first.data[0]` observe? Why would deleting through both objects be invalid?

## 5. Layout prediction

Assume `sizeof(char) == 1`, `sizeof(int) == 4`, and `alignof(int) == 4`.

```cpp
struct Layout {
    char a;
    int b;
    char c;
};
```

Predict each member offset, internal padding, tail padding, `sizeof(Layout)`, and `alignof(Layout)`. Then compare with the `layout` executable.

## 6. Contiguous memory

```cpp
std::vector<int> values{2, 4, 6, 8};
int* begin = values.data();
int* end = begin + values.size();
```

Draw all element addresses symbolically using `A = values.data()`. Which pointer may be formed but not dereferenced? What operation could invalidate both pointers?