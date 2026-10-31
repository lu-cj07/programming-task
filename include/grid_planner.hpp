#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

// Task 004: weighted four-neighbor grid A* path planning.
// Read tasks/004-grid-planner/README.md before implementing.

struct GridPoint {
    int row;
    int col;
};

struct GridMap {
    // -1 = blocked; 1..1000 = cost of entering the cell.
    std::vector<std::vector<int>> cost;
};

struct PathResult {
    std::vector<GridPoint> path;
    std::int64_t total_cost;
    std::size_t expanded_nodes;
};

class GridPlanner {
public:
    static std::optional<PathResult> plan(const GridMap& map,
                                          GridPoint start,
                                          GridPoint goal) {
        // TODO: validate map and endpoints; implement A* and path reconstruction.
        (void)map;
        (void)start;
        (void)goal;
        return std::nullopt;
    }
};
