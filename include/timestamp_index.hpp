#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

// Task 002: implement a binary-search-based index for sorted timestamps.
// The input must be nondecreasing. Do not use std::lower_bound or
// std::upper_bound inside the three query methods.
class TimestampIndex {
public:
    explicit TimestampIndex(std::vector<std::int64_t> timestamps) {
        // TODO: store timestamps and reject unsorted input.
        (void)timestamps;
        throw std::logic_error("TODO: TimestampIndex constructor");
    }

    std::size_t lower_bound(std::int64_t target) const {
        (void)target;
        throw std::logic_error("TODO: lower_bound");
    }

    std::size_t upper_bound(std::int64_t target) const {
        (void)target;
        throw std::logic_error("TODO: upper_bound");
    }

    std::size_t count_range(std::int64_t begin, std::int64_t end) const {
        (void)begin;
        (void)end;
        throw std::logic_error("TODO: count_range");
    }

    std::size_t size() const noexcept {
        // TODO
        return 0;
    }

private:
    std::vector<std::int64_t> timestamps_;
};
