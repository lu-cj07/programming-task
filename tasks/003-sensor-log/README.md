# Task 003 — 传感器日志解析器

方向：C++17 工程实践，文件 I/O、异常、RAII 与轻量数学。预计 4–6 小时，可跨天。

## 背景
机器人底盘调参日志每行记录时间戳、左轮转速、右轮转速。实现严格的 CSV 风格解析器，将输入流转为结构化记录。

## API
在 include/sensor_log.hpp 中实现 SensorRecord（int64_t timestamp_ms; int left_rpm; int right_rpm）及 SensorLog::parse_line(const std::string&) 和 SensorLog::read(std::istream&)。

## 规则
- 每行恰好三列，逗号分隔，无表头；空输入返回空 vector。
- 字段必须是十进制有符号整数，允许前后空格、制表符，允许可选 + 或 -，但字段内部不得出现空白或其他字符。
- 空白行、空字段、额外列、尾随逗号均无效；timestamp_ms 必须在 int64_t 范围内，转速必须在 int 范围内。
- parse_line 发生格式或范围错误时抛 std::invalid_argument；read 使用 getline 逐行读取，遇到错误抛 std::invalid_argument，异常消息包含从 1 开始的行号。
- 支持 CRLF；允许负数、零、重复时间戳，不要求排序。
- 不使用正则表达式或第三方 CSV 库。总字符数 L 的时间复杂度目标 O(L)。

## 阅读
C++ Primer 第 8 章流与 getline、第 5 章异常、第 7 章类。
cppreference：getline、istringstream、stoll、invalid_argument。

## 自主调研
1. getline 与 operator>> 如何处理空白和换行？
2. stoll 为什么可能接受 12abc？如何确保消费整个字段？
3. int64_t 和 int 为什么需要分别检查范围？
4. istream& 为什么有利于单元测试？
5. RAII 在流对象上如何体现？

## 数学与正确性（约 15%）
描述字段解析的有限状态规则（可选符号、至少一位数字、末尾空白），解释每行成功解析后输出记录都对应合法输入，以及字符串语法与整数范围验证的区别。

## 验收
完成头文件 TODO，补充至少两个有意义的测试并记录在 notes.md。Ubuntu/Windows CI 通过、PR 合并 main 后解锁 Task 004。不要修改 Task 001/002 公共接口。

本地命令：

    git switch main
    git pull origin main
    git switch -c task/003-sensor-log
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build --config Debug
    ctest --test-dir build -C Debug --output-on-failure
