# Interview drill answers

## 1. Construction or assignment?

A is default construction. B is copy construction. C is copy assignment. D is move construction. E is move assignment. Moved-from `a` and `c` must still be valid and destructible; unless `Widget` documents a stronger promise, their values are unspecified.

## 2. Find the ownership bug

The generated copy constructor copies the pointer, so both objects believe they own one allocation and both destructors call `delete[]` on it. Valid designs include implementing deep-copy Rule of 3, adding moves for Rule of 5, replacing the pointer with `std::vector<int>` for Rule of 0, or deleting copying if the resource must be exclusive.

## 3. Exception safety

After deleting the old allocation, allocation or element copying can throw and leave the target damaged. Copy-and-swap first constructs a complete temporary copy. If that fails, the target is unchanged. Swapping non-throwing handles commits the new state, and the temporary destroys the old state, providing the strong exception guarantee.

## 4. Move semantics

Resetting the source prevents both objects from releasing the same resource. A truthful `noexcept` lets containers move elements during reallocation while preserving their exception guarantees. `std::move` is a cast to an xvalue; overload resolution may then select a move operation, but the cast itself transfers nothing.

## 5. Rule selection

1. Rule of 0: the standard members already manage their resources.
2. Rule of 3 at minimum; Rule of 5 avoids expensive copies from rvalues.
3. Rule of 0 is usually best. A `unique_ptr` member automatically destroys and moves ownership. Copying is naturally disabled unless explicit deep-copy value semantics are required.

## 6. API ownership

1. `const T&`.
2. `T&`.
3. `T*`, with null meaning absent.
4. `std::unique_ptr<T>` by value.
5. `std::shared_ptr<T>` by value.
6. `std::unique_ptr<T>&`.

Use `shared_ptr<T>&` similarly only when a function must reseat a caller's shared pointer. Ordinary object access should not pay for or obscure ownership semantics.

## 7. Reference counts

A is 1. B is 3 because `a`, `b`, and the result of `lock()` own the object; `w` does not. C is 1. D is `true` (printed as `1` without `boolalpha`) because the final strong owner was reset.

## 8. Shared ownership cycle

Each node's outgoing strong edge keeps the other node's strong count above zero, even after external owners disappear. Model the back-edge or otherwise non-owning relationship as `weak_ptr<Node>`. Lock it temporarily when access is needed.

## 9. Code review

The two constructors create independent control blocks for one raw pointer. Each control block eventually deletes the same object. Create the first owner with `auto first = std::make_shared<Widget>();` and copy it with `auto second = first;` so both share one control block.

## 10. Design question

Use `-1` as the no-resource invariant. The destructor calls `close(fd)` only when the descriptor is valid. Delete copy operations. Move construction takes the descriptor with `std::exchange(other.fd_, -1)`. Move assignment must close its currently owned descriptor before taking the source descriptor, while also handling self-move safely. Expose `int get() const noexcept` for borrowing and optionally `release()` and `reset()` for explicit ownership operations. Never let move assignment overwrite a live descriptor without closing it, or it leaks.