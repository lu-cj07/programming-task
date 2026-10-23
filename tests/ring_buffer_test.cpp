#include "ring_buffer.hpp"
#include <cassert>
#include <deque>
#include <random>
#include <stdexcept>
#include <iostream>

int main() {
    bool threw = false;
    try { RingBuffer<int> bad(0); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    RingBuffer<int> q(3);
    assert(q.capacity() == 3 && q.size() == 0 && q.empty() && !q.full());
    assert(!q.pop().has_value());
    assert(q.push(1) && q.push(2) && q.push(3));
    std::cout<<q.full()<<" "<<q.push(99)<<std::endl;
    assert(q.full() && !q.push(99));
    assert(q.pop() == 1 && q.pop() == 2);
    assert(q.push(4) && q.push(5));
    assert(q.pop() == 3 && q.pop() == 4 && q.pop() == 5);
    assert(q.empty());

    RingBuffer<int> single(1);
    assert(single.push(7) && !single.push(8));
    assert(single.pop() == 7 && single.push(9) && single.pop() == 9);

    RingBuffer<int> test(7);
    std::deque<int> reference;
    std::mt19937 rng(20261022);
    for (int i = 0; i < 10000; ++i) {
        if (rng() % 2 == 0) {
            int value = static_cast<int>(rng() % 10000);
            bool expected = reference.size() < 7;
            assert(test.push(value) == expected);
            if (expected) reference.push_back(value);
        } else {
            auto actual = test.pop();
            if (reference.empty()) assert(!actual.has_value());
            else { assert(actual == reference.front()); reference.pop_front(); }
        }
        assert(test.size() == reference.size());
        assert(test.empty() == reference.empty());
        assert(test.full() == (reference.size() == 7));
    }
}
