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
        // 检查是否有序？
        if(timestamps.cbegin() != timestamps.cend())
            for(auto i = timestamps.cbegin(); i != timestamps.cend() - 1; i++){
                if(*i > *(i + 1)){
                    throw std::invalid_argument("sequences are unordered");
                }
            }
        // 有序时进行赋值
        timestamps_ = timestamps;
    }

    // 首个大于等于target的下标
    std::size_t lower_bound(std::int64_t target) const {
        if(timestamps_.size() == 0)
            return 0;
        decltype(size()) begin = 0;
        decltype(begin) mid;
        auto end = size() - 1;
        while (begin < end)
        {
            mid = (end - begin)/2 + begin;
            if(timestamps_[mid] >= target)
                end = mid;
            else
                begin = mid + 1;
        }

        return timestamps_[begin] >= target ? begin : size();
    }

    std::size_t upper_bound(std::int64_t target) const {
        if(timestamps_.size() == 0)
            return 0;
        decltype(size()) begin = 0;
        decltype(begin) mid;
        auto end = size() - 1;
        while (begin < end)
        {
            mid = (end - begin)/2 + begin;
            if(timestamps_[mid] <= target)
                begin = mid + 1;
            else if(timestamps_[mid] > target)
                end = mid;
        }

        return timestamps_[begin] > target ? begin : size();
    }

    std::size_t count_range(std::int64_t begin, std::int64_t end) const {
        if(begin > end)
            return 0;
        return lower_bound(end) - lower_bound(begin);
    }

    std::size_t size() const noexcept {
        return timestamps_.size();
    }

private:
    std::vector<std::int64_t> timestamps_;
};
