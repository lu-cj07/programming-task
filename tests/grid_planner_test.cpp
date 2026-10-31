#include "grid_planner.hpp"

#include <cassert>
#include <cstdint>
#include <optional>
#include <stdexcept>

int main() {
    // Start == goal must be a zero-cost, single-node path.
    {
        GridMap map{{{1}}};
        auto result = GridPlanner::plan(map, {0, 0}, {0, 0});
        assert(result.has_value());
        assert(result->path.size() == 1);
        assert(result->path[0].row == 0 && result->path[0].col == 0);
        assert(result->total_cost == 0);
        assert(result->expanded_nodes == 0);
    }

    // A detour around a wall; path must be legal and have minimum cost.
    {
        GridMap map{{{1, -1, 1}, {1, -1, 1}, {1, 1, 1}}};
        auto result = GridPlanner::plan(map, {0, 0}, {0, 2});
        assert(result.has_value());
        assert(result->total_cost == 6);
        assert(result->path.size() == 7);
    }

    // Weighted cells: cheapest path can take more steps.
    {
        GridMap map{{{1, 100, 1}, {1, 1, 1}}};
        auto result = GridPlanner::plan(map, {0, 0}, {0, 2});
        assert(result.has_value());
        assert(result->total_cost == 4);
        assert(result->path.size() == 5);
    }

    // No route is different from invalid input.
    {
        GridMap map{{{1, -1, 1}}};
        assert(!GridPlanner::plan(map, {0, 0}, {0, 2}).has_value());
    }

    // Ragged maps are invalid.
    {
        GridMap map{{{1, 1}, {1}}};
        bool threw = false;
        try {
            (void)GridPlanner::plan(map, {0, 0}, {1, 0});
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        assert(threw);
    }
}
