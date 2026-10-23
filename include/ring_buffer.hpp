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
        if(capacity <= 0){
            throw std::invalid_argument("capacity can not be zero");
        }
        buffer = std::vector<T>(capacity);
        head = tail = count = 0;
    }
    bool push(const T& value) {
        if(count >= buffer.capacity()){
            return false;
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity();
        count++;
        return true;
    }
    std::optional<T> pop() {
        if(count <= 0){
            return std::nullopt;
        }
        T val = buffer[head];
        head = (head + 1) % capacity();
        count--;
        return val;
    }
    bool empty() const {
        return count == 0;
    }
    bool full() const {
        return count == buffer.capacity();
    }
    std::size_t size() const {
        return count;
    }
    std::size_t capacity() const {
        return buffer.capacity();
    }
private:
    std::vector<T> buffer;
    std::size_t head;
    std::size_t tail;
    std::size_t count;
};
