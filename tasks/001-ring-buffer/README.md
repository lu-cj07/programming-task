# Task 001 — Implement a bounded ring buffer

**Track:** C++ engineering / data structures. **Estimated effort:** 2–4 hours, may span days.

## Why
Ring buffers are used in embedded data acquisition, logging and message queues. Implement a fixed-capacity FIFO container and understand indexing, invariants and object lifetime.

## Prerequisite reading
- cppreference: `std::vector`, `std::optional`, `std::size_t`, `std::move`, `std::invalid_argument`
- CS106L: containers, references and const correctness
- Review modular arithmetic and circular queue invariants.

## Required interface
Implement `include/ring_buffer.hpp` as a template `RingBuffer<T>` with:
- `explicit RingBuffer(std::size_t capacity)` (capacity must be > 0, otherwise throw `std::invalid_argument`)
- `bool push(const T& value)` (false when full; no overwrite)
- `std::optional<T> pop()` (empty optional when empty)
- `bool empty() const`, `bool full() const`, `std::size_t size() const`, `std::size_t capacity() const`

Use `std::vector<T>` as storage for this first version. You may restrict `T` to default-constructible, copyable types. No raw owning pointers. Preserve FIFO order across wraparound. No thread-safety requirement.

## Required verification
1. Constructor rejects capacity zero.
2. Initial state: size 0, empty true, full false.
3. Capacity 1: push, reject extra push, pop, reuse.
4. Capacity 3: push 1,2,3; pop 1,2; push 4,5; pop 3,4,5.
5. Pop empty returns no value; push full returns false without modifying contents.
6. Randomized differential test: compare 10,000 operations against `std::deque<int>` with fixed seed.
7. CI builds and tests on Linux and Windows.

## Submission
- Implement `include/ring_buffer.hpp`.
- Extend tests in `tests/ring_buffer_test.cpp`.
- Complete `tasks/001-ring-buffer/notes.md` with invariants and verification.
- Open PR titled `task(001): bounded ring buffer`.

## Optional extension
Analyze exception safety and support for non-default-constructible types.
