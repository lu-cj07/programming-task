# Task 001 — 实现有界环形缓冲区（RingBuffer）

**课程阶段：** 现代 C++ 基础与工程规范  
**任务类型：** 工程实践 / 数据结构  
**建议投入：** 约 3–6 小时，可跨天；学习和调研时间包含在内  
**语言标准：** C++17  
**完成条件：** PR 在 Windows 与 Linux 的 CI 检查通过，并合并到 main。

## 1. 工程背景与学习目标

环形缓冲区常见于传感器数据采集、嵌入式通信、日志缓存及生产者—消费者系统。你需要实现固定容量、先进先出（FIFO）的泛型容器，正确维护读写位置与元素数量。

完成本任务后，应当能够：
- 解释循环队列的索引回绕与空/满判定；
- 编写具有明确不变量的 C++ 类模板；
- 理解 `std::vector<T>`、`std::optional<T>` 和 `const` 成员函数的用途；
- 使用 CMake、CTest、断言和差分测试验证实现；
- 使用 Git 分支、Pull Request 和 GitHub Actions 完成工程提交。

## 2. 前置学习：指定教材与资料

**必读（按主题阅读，不要求通读整章的无关内容）：**

1. **《C++ Primer》第 5 版**（Stanley B. Lippman、Josée Lajoie、Barbara E. Moo）：第 3 章 *Strings, Vectors, and Arrays* 中 `vector` 的使用；第 7 章 *Classes* 中构造函数、封装和 `const` 成员函数。重点是能看懂并正确使用，不要求提前掌握全书。
2. **《C++ Primer》第 5 版**：第 16 章 *Templates and Generic Programming* 的模板基础（特别是类模板）。这一部分可以结合本题代码边写边读。
3. **cppreference**：
   - [std::vector](https://en.cppreference.com/w/cpp/container/vector)
   - [std::optional](https://en.cppreference.com/w/cpp/utility/optional)
   - [std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)
   - [std::size_t](https://en.cppreference.com/w/cpp/types/size_t)

**选读（遇到问题再查）：**

- 《C++ Primer》第 5 版，第 5 章中异常处理相关内容；
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)：理解项目配置与构建；
- [CTest 文档](https://cmake.org/cmake/help/latest/manual/ctest.1.html)：理解测试发现与运行；
- [GitHub Actions 文档](https://docs.github.com/en/actions)：理解自动化 CI。

> 教材可使用中译本；以“第 5 版”的章节标题和主题为准。你不需要为了完成本题先系统学完 CS106L。

## 3. 自主调研（先尝试回答，再动手修正理解）

请独立查找资料，并在 `tasks/001-ring-buffer/notes.md` 中用自己的语言回答；每题至少附一个参考来源（教材名称与章节，或资料链接）。

1. 循环队列只保存 `head` 和 `tail` 时，为什么 `head == tail` 可能同时表示空和满？常见解决方法有哪些？
2. `std::vector<T>::size()` 与 `capacity()` 有何区别？`resize(n)` 和 `reserve(n)` 对元素访问有什么影响？
3. 类模板的实现为什么通常放在头文件中？与普通非模板类有什么区别？
4. `std::optional<T>` 如何表示“没有值”？相比使用 `-1` 等哨兵值，有什么优势？
5. 如果写入操作中的 `T` 复制或赋值抛出异常，哪些内部状态必须保持一致？如何避免错误地增加元素计数？

可以使用搜索引擎和 AI 辅助理解，但不要直接复制整段回答。允许暂时写下疑问，在完成代码后补充修正。

## 4. 设计任务

在 `include/ring_buffer.hpp` 中实现类模板：

```cpp
template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity);

    bool push(const T& value);
    std::optional<T> pop();

    bool empty() const;
    bool full() const;
    std::size_t size() const;
    std::size_t capacity() const;
};
```

**行为约束：**
- 容量必须大于 0；否则构造函数抛出 `std::invalid_argument`。
- `push`：成功返回 `true`；满时返回 `false`，不得覆盖现有元素。
- `pop`：按 FIFO 顺序返回元素；空时返回 `std::nullopt`。
- `size` 表示当前有效元素数量，`capacity` 表示最大元素数量。
- 正确处理索引回绕，特别是容量为 1 的情况。
- 本阶段使用 `std::vector<T>` 存储；允许限定 `T` 为可默认构造、可复制类型，不要求处理移动专属类型。
- 不允许用裸指针管理所有权；本题**不要求线程安全**。
- 需要在笔记中说明用于判断正确性的状态不变量。

**提示而非答案：** 思考使用读位置、写位置和当前数量分别表示什么，以及每次成功操作应如何更新它们。不要只用单次正常读写测试来证明正确性。

## 5. 测试与验收

现有 `tests/ring_buffer_test.cpp` 提供基础检查，至少包括：
1. 容量 0：构造时抛出异常；
2. 初始状态：空、非满、大小为 0；
3. 容量 1：写满、拒绝额外写入、读出、再次写入；
4. 容量 3：写入 1/2/3，取出 1/2，写入 4/5，再依序取出 3/4/5；
5. 空时读取不返回元素，满时写入不改变逻辑内容；
6. 固定随机种子下进行 10,000 次操作，与 `std::deque<int>` 参考模型对照；
7. GitHub Actions 在 Ubuntu 与 Windows 上构建、运行 CTest。

建议你自行添加至少一个测试用例，并解释它覆盖了什么边界情况。

**本地运行：**

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

注意：当前测试使用 `assert`，应使用 Debug 构建，以免发布模式禁用断言。初始代码中的 `TODO` 会导致测试失败，这是预期现象。

## 6. 可跨天的学习安排

- **阶段 A — 阅读与调研：** 了解 `vector`、`optional`、类模板、环形队列判空判满；记录问题的初步答案。
- **阶段 B — 设计与实现：** 先写下状态变量及不变量，再完成接口；优先验证容量 1 和索引回绕。
- **阶段 C — 测试与调试：** 运行 CMake / CTest，补充边界用例，分析失败原因。
- **阶段 D — 复盘与提交：** 完成笔记，提交任务分支并创建 PR，等待双平台 CI 通过后合并。

这四个阶段不必对应四天，也不要求每天必须完成一个阶段。

## 7. 提交规范

- 实现：`include/ring_buffer.hpp`
- 测试：`tests/ring_buffer_test.cpp`
- 调研、设计与复盘：`tasks/001-ring-buffer/notes.md`
- 分支：`task/001-ring-buffer`
- PR 标题：`task(001): bounded ring buffer`

**解锁标准：** PR 已合并且 Linux/Windows CI 全部通过。笔记和思考问题属于学习任务，但不设置额外的人工评分门槛；后续仍可能收到不阻塞进度的代码评审建议。

## 8. 复盘问题

- 哪个不变量最容易在修改代码时被破坏？
- 哪个测试最能证明你的环形回绕实现正确？
- `push` 和 `pop` 的时间复杂度是多少？为何？
- 如果未来要求多线程使用，当前实现还缺少哪些同步保证？

## 9. 可选拓展（不影响验收）

研究异常安全保证、支持不可默认构造的元素类型，以及为不同操作增加移动语义重载。暂时不要直接扩展成多线程或无锁队列。
