# Task 004 — 二维栅格路径规划器（A*）

方向：**算法与数据结构 + 机器人业务建模 + 数学证明**。预计 6–10 小时，可跨天；PA / OS 另行安排。

## 任务背景
机器人在二维离散地图上从起点移动到终点。部分格子不可通行，其他格子具有进入代价。实现一个能寻找**总代价最小路径**的规划器，而不只是“看起来能到达”的路径。

这是离散全局路径规划，不要求麦克纳姆轮运动学、平滑轨迹或控制器。后续任务可基于它继续扩展。

## 你要交付的接口
在 `include/grid_planner.hpp` 中实现以下公开接口（可自行增加私有辅助函数）：

- `struct GridPoint { int row; int col; };`
- `struct GridMap { std::vector<std::vector<int>> cost; };`
- `struct PathResult { std::vector<GridPoint> path; std::int64_t total_cost; std::size_t expanded_nodes; };`
- `class GridPlanner { public: static std::optional<PathResult> plan(const GridMap& map, GridPoint start, GridPoint goal); };`

数据规则：
- 地图非空且为矩形；`cost[row][col] == -1` 表示障碍，`1..1000` 表示进入该格子的代价，其他值非法。
- 仅允许上下左右四邻接移动；不能斜向移动、不能穿过障碍。
- 每一步的代价等于**进入目标格子**的代价，起点本身不计费。
- 起点、终点必须在地图内且可通行；否则抛出 `std::invalid_argument`。
- 地图格式非法也抛出 `std::invalid_argument`。
- 有路返回 `PathResult`；无路返回 `std::nullopt`。
- 起点等于终点：返回只含起点的路径，总代价为 0。
- `path` 必须包含起点和终点，每一步合法，`total_cost` 与路径代价一致，并且在所有可行路径中最小。
- 若存在多条最优路径，返回任意一条即可。不得要求测试依赖固定的平局顺序。
- `expanded_nodes` 为真正从待处理集合取出并进行邻居扩展的**不同格子数量**；跳过过期条目，不重复扩展同一格子。起点等于终点时记为 0。
- 路径总代价使用 `std::int64_t`；需要考虑累加溢出的防护或给出有依据的上界论证。

## 算法要求
1. 核心使用 **A***（启发式搜索），不得调用现成路径规划库。
2. 自己选择适合的 STL 容器，解释原因与复杂度；建议调研 `std::priority_queue`、`std::vector`、`std::optional`。
3. 启发式建议从曼哈顿距离开始，但必须解释它为什么在本任务中**不会高估剩余代价**。
4. 需要维护最小已知代价和前驱关系，最终重建路径。
5. 分析在一致启发式、非负边权下，何时可以将格子视为最终确定；理解堆中可能存在过期条目。
6. 目标时间复杂度：令 `V=行数×列数`，四邻接下 `E=O(V)`，典型二叉堆实现为 `O((V+E)log V)`；空间 `O(V+E)`。如果你的实现不同，写出自己的分析。

## 编码前：先完成需求契约
在 `tasks/004-grid-planner/notes.md` 写出：
- 状态、可执行动作、转移规则、路径代价；
- 至少 5 个自拟测试（必须包含：不可达、起终点相同、障碍绕行、**步数较少但代价更高**、多条等价最优路径）；
- 你选择的数据结构及其理由。

## 阅读 / 自主调研
- 《算法导论》图搜索、最短路径相关章节（按手头版本目录定位）；或 Princeton Algorithms 图算法资料。
- cppreference: `std::priority_queue`、`std::optional`、`std::vector`。
- 自主回答：BFS、Dijkstra、A* 的区别；为什么带权地图不能简单用 BFS 保证最低代价；启发式的 admissible / consistent 是什么；为什么需要跳过过期堆条目。
- 可阅读伪代码和资料，但**不要让 Agent 直接完成核心 A* 实现**。

## 数学与正确性（约 15%–20%）
- 写出 `f(n)=g(n)+h(n)` 的含义。
- 证明曼哈顿距离乘以最小进入代价是本题的可采纳启发式，并讨论一致性。
- 说明 A* 找到目标时为何可获得最优路径（写清所依赖的条件）。
- 分析一个“最短步数不等于最低代价”的反例。

## 测试、调试与 AI 使用
- 先运行仓库提供的基础测试，再自行补充至少 **5 个**有意义的测试；不要仅仅追求 CTest 变绿。
- 失败时记录：输入、预期、实际、最小复现、根因和修复。
- L1：允许 AI 解释 API / 报错；L2：允许 AI 协助定位根因；L3：允许局部示范，但应自己完成核心算法并解释关键不变量。
- Agent 可协助构建配置、测试建议和代码审查，禁止直接代写核心算法。
- 不要修改 Task 001–003 的公开接口。

## 验收
1. `include/grid_planner.hpp` 实现通过基础测试与自增测试。
2. `notes.md` 包含需求契约、阅读调研、数学推理、测试和调试复盘。
3. Ubuntu/Windows CI 均通过，PR 合并到 `main` 后才解锁 Task 005。
4. 任务可跨天，没有截止日期。

## 本地工作流
```bash
git switch main
git pull origin main
git switch -c task/004-grid-planner
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```
