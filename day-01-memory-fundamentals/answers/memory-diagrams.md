# Memory diagram answer key

## 1. Pointer and reference aliases

There is one `int` object. `value` names it, `reference` is another name for it, and `pointer` is a separate pointer object whose stored value is the `int` object's address. The final `int` value is `9`.

## 2. Dynamic array

Before deletion, `data` points at element 0 and `middle` points at element 1 of one three-element allocation. `delete[]` ends all three element lifetimes and releases the allocation, so both pointers dangle immediately. Resetting `data` does not modify `middle`.

## 3. Scope and lifetime

`observer` exists in the outer scope. `local` exists only in the inner scope. At the closing brace, `local`'s lifetime ends and `observer` becomes dangling; the pointer object itself remains alive.

## 4. Shallow copy

Both pointer members contain the same address. Updating through `second` changes the shared allocation, so `first.data[0]` observes `8`. The allocation has only one lifetime; a second `delete[]` would attempt to release dead storage.

## 5. Layout prediction

Typical layout: `a` at offset 0, three padding bytes, `b` at offset 4, `c` at offset 8, and three bytes of tail padding. The resulting size is 12 and alignment is 4. These values are implementation-dependent, so verify rather than hard-code them.

## 6. Contiguous memory

The addresses are `A`, `A + 1`, `A + 2`, and `A + 3`; pointer arithmetic scales by `sizeof(int)`. `end == A + 4` is the valid one-past pointer and must not be dereferenced. A vector reallocation, such as a capacity-growing `push_back`, invalidates both pointers.