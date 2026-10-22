#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>

// Task 001: implement the interface described in tasks/001-ring-buffer/README.md.
// This is deliberately incomplete. CI should fail until you implement it.
template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity) {
        (void)capacity;
        throw std::logic_error("TODO: implement RingBuffer");
    }
    bool push(const T& value) {
        (void)value;
        throw std::logic_error("TODO: implement push");
    }
    std::optional<T> pop() {
        throw std::logic_error("TODO: implement pop");
    }
    bool empty() const {
        throw std::logic_error("TODO: implement empty");
    }
    bool full() const {
        throw std::logic_error("TODO: implement full");
    }
    std::size_t size() const {
        throw std::logic_error("TODO: implement size");
    }
    std::size_t capacity() const {
        throw std::logic_error("TODO: implement capacity");
    }
};
