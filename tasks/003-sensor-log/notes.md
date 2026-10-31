# Task 003 学习笔记

## 阅读与参考资料
    1. c++primer
    2. google

## 自主调研
1. getline 与 operator>>：
   - getline可读取一行的数据。
   - operator>> 遇到空格则停止。
2. stoll 完整消费：
  使用 pos 检查完整消费
    ```c++
    std::string s = "123abc";
    std::size_t pos = 0;
    long long value = std::stoll(s, &pos, 10);
    if (pos != s.size()) {
        throw std::invalid_argument("Invalid integer");
    }
    ```
    其中：
    - s：待转换的字符串。
    - &pos：接收解析停止的位置（已经消费的字符数）。
    - 10：使用十进制解析。
    - pos == s.size()：表示所有字符都被消费。
3. int64_t 和 int 范围：
   - int为4字节，32位 -2 ** 31 - 2 ** 31 - 1
   - int64_t为8字节 64位 -2 ** 63 - 2 ** 63 - 1
4. istream& 可测试性：
   - 使用 std::istream& 可以将解析逻辑与输入来源解耦，提高代码复用性与可测试性
5. RAII 与流：
   - 文件资源自动释放，降低资源泄漏风险

## 设计
- 解析步骤：
    1. `std::vector<SensorRecord> read(std::istream& input)`读取行字符串数据并记录行号，当解析抛出异常之后返回出错的行号
    2. `SensorRecord parse_line(const std::string& line)一行解析数据，去除首尾空格，检测脏数据，并且进行数值越界检测，最终解析出字段
- 异常与行号：见上
- 复杂度：O(1)

## 数学与正确性
- 字段状态规则：中途不抛异常就说明是合理的字符串
- 每行处理后的不变量：`std::getline(input, line)== true`
- 语法与范围检查：见代码

## 测试
- 自增测试一：
- 自增测试二：
- Ubuntu CI：
- Windows CI：

## 复盘
1. 审题要结合测试用例
2. 写代码之前查清楚api的细节
3. 防御性编程，学会抛异常