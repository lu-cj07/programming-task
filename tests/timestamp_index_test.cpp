#include "timestamp_index.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <random>
#include <stdexcept>
#include <vector>

int main() {
    using i64 = std::int64_t;
    {
        TimestampIndex empty({});
        assert(empty.size() == 0);
        assert(empty.lower_bound(0) == 0);
        assert(empty.upper_bound(0) == 0);
        assert(empty.count_range(-10, 10) == 0);
    }
    {
        TimestampIndex index({-5, -5, 0, 3, 3, 3, 10});
        assert(index.size() == 7);
        assert(index.lower_bound(-6) == 0);
        assert(index.lower_bound(-5) == 0);
        assert(index.upper_bound(-5) == 2);
        assert(index.lower_bound(3) == 3);
        assert(index.upper_bound(3) == 6);
        assert(index.lower_bound(11) == 7);
        assert(index.upper_bound(11) == 7);
        assert(index.count_range(-5, 3) == 3);
        assert(index.count_range(3, 10) == 3);
        assert(index.count_range(3, 3) == 0);
        assert(index.count_range(10, 3) == 0);
    }
    {
        TimestampIndex single({42});
        assert(single.lower_bound(42) == 0);
        assert(single.upper_bound(42) == 1);
        assert(single.lower_bound(43) == 1);
        assert(single.count_range(42, 43) == 1);
    }
    {
        TimestampIndex same({7, 7, 7});
        assert(same.lower_bound(7) == 0);
        assert(same.upper_bound(7) == 3);
        assert(same.count_range(7, 8) == 3);
    }
    {
        const i64 low = std::numeric_limits<i64>::min();
        const i64 high = std::numeric_limits<i64>::max();
        TimestampIndex edges({low, 0, high});
        assert(edges.lower_bound(low) == 0);
        assert(edges.upper_bound(low) == 1);
        assert(edges.lower_bound(high) == 2);
        assert(edges.upper_bound(high) == 3);
        assert(edges.count_range(low, high) == 2);
    }
    {
        bool rejected = false;
        try { TimestampIndex invalid({1, 3, 2}); }
        catch (const std::invalid_argument&) { rejected = true; }
        assert(rejected);
    }

    std::mt19937_64 rng(20261023);
    for (int round = 0; round < 80; ++round) {
        std::vector<i64> values;
        const int n = static_cast<int>(rng() % 180);
        for (int i = 0; i < n; ++i)
            values.push_back(static_cast<i64>(rng() % 81) - 40);
        std::sort(values.begin(), values.end());
        TimestampIndex index(values);
        assert(index.size() == values.size());
        for (i64 target = -45; target <= 45; ++target) {
            const auto expected_lower = static_cast<std::size_t>(
                std::lower_bound(values.begin(), values.end(), target) - values.begin());
            const auto expected_upper = static_cast<std::size_t>(
                std::upper_bound(values.begin(), values.end(), target) - values.begin());
            assert(index.lower_bound(target) == expected_lower);
            assert(index.upper_bound(target) == expected_upper);
        }
        for (int k = 0; k < 80; ++k) {
            const i64 begin = static_cast<i64>(rng() % 100) - 50;
            const i64 end = static_cast<i64>(rng() % 100) - 50;
            const auto expected = begin >= end ? std::size_t{0} :
                static_cast<std::size_t>(std::lower_bound(values.begin(), values.end(), end)
                    - std::lower_bound(values.begin(), values.end(), begin));
            assert(index.count_range(begin, end) == expected);
        }
    }
}
