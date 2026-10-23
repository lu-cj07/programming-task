# Task 001 — 学习、调研与复盘记录

> 请用自己的语言填写。允许先写初步认识，再在编码与测试后修正。资料来源可写教材名称、版本、章节，或可访问的文档链接。

## A. 前置阅读记录

- 阅读的教材/课程及具体章节：
  - 《c++ primer》第三章、第七章、第十六章
- 查阅的标准库或工具文档：
    - cppreference
    - 菜鸟教程
- 仍不理解的概念：
    - 什么叫写入时发生异常，会发生哪些异常，若真的发生异常则捕获并停止写入操作？
    - 有点不想去看异常处理的文档和cmake和git操作了，累了。

## B. 自主调研

### Q1. 环形队列的空/满歧义
- 我的回答：
  - head == tail时，可能为空，可能为满，当是由于pop操作导致的时为空，push操作导致时为满。
  - 解决方案：
    - 1. 当环形队列容量为n时，牺牲一个存储区域，当（tail + 1）% n = head时为满， tail == head时为空。
    - 2. 维护一个count变量用于记录存储区域中的元素数量，当count == capacity时为满， count == 0时为空。
    - 3. 使用tag标记push和pop操作，例如tag == 1时表示刚刚进行了push操作， 则若此时 tail == head时为满， tag == 0 && tail == head时为空。
- 资料来源：
  - 技术文档

### Q2. vector 的 size、capacity、resize 与 reserve
- 我的回答：
  - size: 返回vector中的元素个数，类型为vector定义的size_type类型。
  - capacity: 返回当前已分配的内存容量，capacity通常大于等于size
  -  reserve: 预分配内存空间
  -  resize: 调整存储的元素数量
- 资料来源：
  - https://en.cppreference.com/cpp/container/vector
  - 《c++ primer》第三章
  - https://www.runoob.com/cplusplus/cpp-vector.html

### Q3. 为什么类模板的实现通常在头文件中？
- 我的回答：
  - 若将模版的声明/定义放在.h文件中，实现放在.cpp文件中，编译器只能找到模版的声明但是找不到实现导致在链接时无法找到模版的实现。但是似乎如果实现了的.cpp也include，也能够使得编译器找到模版的实现，但是这样做就不如直接定义和实现在.h文件中了。
- 资料来源：
  - https://blog.csdn.net/xin_hen/article/details/108782175

### Q4. optional 相比哨兵值的优势
- 我的回答：
  - 可以很好地处理构造成本高的对象，并且具有很好的可读性。
- 资料来源：
  - https://vra.github.io/2023/06/30/cpp-optional-tutorial/

### Q5. 写入时发生异常如何维护内部状态？
- 我的回答：
- 资料来源：

## C. 设计与不变量

- `head` 的含义及取值范围：0 到 n - 1，表示循环队列的头指针，指向下一个pop的元素。
- `tail` 的含义及取值范围：0 到 n - 1，表示循环队列的尾指针，指向下一个push的位置。
- 当前元素数量的含义及范围：0 到 n，队列中插入的元素数量
- 空与满如何区分：count == capacity满， count == 0空。
- 每次成功 `push` / `pop` 后哪些条件必须成立：见代码
- 为什么容量为 1 时仍然正确：有边界保护啊。

## D. 测试与调试

- 本地操作系统、编译器及版本：ubuntu22.04
- CMake 配置与测试命令：你给的
- 自己补充的边界测试：无
- 遇到的失败及原因：
  - 忘记更新count了导致0 1
      ring_buffer_test: /home/lu/programming-task/tests/ring_buffer_test.cpp:19: int main(): Assertion `q.full() && !q.push(99)' failed.
- Linux CI 结果：通过
- Windows CI 结果：无

## E. 复盘

- `push`、`pop` 的时间与空间复杂度：O(1)、O(1)
- 最有价值的测试及理由：没发现
- 如果支持并发访问，需要考虑哪些问题：多线程同时写入(互斥锁)，生产者消费者问题(c++条件变量)
- 本任务学到的 C++ 知识：模版类的基础概念、vector容器的基础、const成员函数的意义和应用
- 仍然存在的问题：
