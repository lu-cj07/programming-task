# Task 002 — 有序时间戳索引：二分查找与循环不变量

**方向：** 算法 / C++17 / 数学融合  
**预计时间：** 3–5 小时，可跨天  
**状态：** Task 001 已验收；本任务待实现

## 工程背景

机器人传感器、日志系统和时序数据存储经常需要从已按时间戳升序排列的数据中快速查找一个时间区间。线性扫描需要 O(n)；本任务尝试使用二分查找把定位边界的时间降为 O(log n)。

## 学习目标

- 使用 `std::vector<std::int64_t>` 保存时间戳；
- 区分 lower bound（首个 >= target）和 upper bound（首个 > target）；
- 正确处理空数组、重复时间戳、负数、极值和不存在的目标；
- 写出并解释二分查找的循环不变量与终止条件；
- 通过 C++17 的 `std::lower_bound` / `std::upper_bound` 做差分测试；
- 理解对数时间复杂度以及区间查询的半开区间语义。

## 前置阅读

**必读：**
1. 结城浩《程序员的数学》第 1 卷：第 4 章「数学归纳法」的证明思想、第 7 章「指数爆炸」中指数/对数与问题规模的关系；按主题选读，不必读完整章。
2. 《C++ Primer》第 5 版：第 3 章 `vector`、下标和迭代器相关部分；第 10 章泛型算法中 `find` / 二分查找相关内容（用于对照，不直接作为实现）。
3. cppreference: [lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound), [upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound), [int64_t](https://en.cppreference.com/w/cpp/types/integer)。

**选读：** 《算法导论》第 3 版第 2 章中循环不变量与算法正确性的讨论。

## 数学推导（约占任务时间的 15%–20%）

在 notes.md 中完成：
1. 为 lower_bound 写出一个在每次循环开始时成立的**区间不变量**，解释初始化、保持与终止。
2. 若每轮把候选区间长度最多缩小为约一半，说明经过 k 轮后的规模上界，并推导为何迭代次数是 O(log n)。
3. 解释为什么使用半开区间 [lo, hi) 更容易处理空数组与“目标不存在”的情况。
4. 说明测试能发现实现错误，但为什么有限测试不能替代正确性证明。

## 自主调研问题

1. `lower_bound` 和 `upper_bound` 对重复元素的返回值有什么区别？
2. `std::size_t` 是什么类型？为什么 `(lo + hi) / 2` 存在潜在溢出问题？
3. 为什么区间 [begin, end) 通常比闭区间方便？
4. 如何使用标准库算法作为自己实现的“参考模型”，而不是直接提交标准库调用？
5. 如果时间戳序列没有排序，二分查找还能保证正确吗？应该如何设计输入约束？

在 `notes.md` 记录自己的回答和参考来源。

## 接口与行为

实现 `include/timestamp_index.hpp` 中的 `TimestampIndex`：

```cpp
class TimestampIndex {
public:
    explicit TimestampIndex(std::vector<std::int64_t> timestamps);
    std::size_t lower_bound(std::int64_t target) const;
    std::size_t upper_bound(std::int64_t target) const;
    std::size_t count_range(std::int64_t begin, std::int64_t end) const;
    std::size_t size() const noexcept;
};
```

**约束：**
- 构造函数接受**非降序**时间戳（允许重复）；输入不满足时抛出 `std::invalid_argument`。
- `lower_bound(target)` 返回首个 >= target 的下标，不存在则返回 `size()`。
- `upper_bound(target)` 返回首个 > target 的下标，不存在则返回 `size()`。
- `count_range(begin,end)` 返回半开区间 [begin,end) 内的元素个数；当 begin >= end 时返回 0。
- 不得在这三个查询方法中调用标准库的二分查找算法；标准库仅用于测试对照。
- 构造允许 O(n) 校验，查询须 O(log n)，计数方法不允许线性遍历。
- 不要求线程安全或增量插入；不要改动 Task 001 的公共接口。

## 必须通过的测试

- 空数组；单元素；重复值；全部相同；
- 目标比最小值小、比最大值大、恰好等于边界；
- 负数、`INT64_MIN`、`INT64_MAX`；
- [a,b) 的边界排除、begin == end、begin > end；
- 构造时拒绝无序输入；
- 固定随机种子下与标准库 `lower_bound`、`upper_bound` 对照；
- Windows / Ubuntu GitHub Actions CI 通过。

你应自行再添加至少两个有意义的测试用例。

## 工作流程

**A 阅读与设计：** 完成必要阅读，写出二分查找不变量，画出区间变化。  
**B 编码：** 实现两个边界查找与区间计数，处理边界。  
**C 验证：** 编译、运行测试、增加自测、分析失败。  
**D 复盘：** 完成 notes.md，推送任务分支、创建 PR。

本地命令：

```bash
git pull origin main
git switch -c task/002-timestamp-index
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

PR 标题建议：`task(002): timestamp binary search index`。

**验收：** PR 合并至 main，且 Windows/Ubuntu CI 通过；笔记与代码质量另作反馈，不增加人工阻塞条件。

## 选做拓展

用随机数据测量线性扫描与二分查找在不同 n 下的查询耗时，解释为什么实际时间不一定严格符合渐近复杂度。
