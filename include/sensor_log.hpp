#pragma once
#include <cstdint>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

struct SensorRecord {
    std::int64_t timestamp_ms;
    int left_rpm;
    int right_rpm;
};

class SensorLog {
public:
    static SensorRecord parse_line(const std::string& line) {
        std::vector<std::string> temps;
        auto end = line.size();
        if (end > 0 && line[end - 1] == '\r') {
            --end;
        }
        decltype(line.size()) start = 0;
        for (decltype(line.size()) i = 0; i <= end; ++i) {
            if (i == end || line[i] == ',') {
                temps.push_back(line.substr(start, i - start));
                start = i + 1;
            }
        }
        if (temps.size() != 3) {
            throw std::invalid_argument("Incorrect number of fields");
        }
        for (auto& field : temps) {
            field = validate_integer(field);
        }
        try {
            const auto timestamp = std::stoll(temps[0], nullptr, 10);
            if (timestamp < INT64_MIN || timestamp > INT64_MAX) {
                throw std::invalid_argument("Timestamp out of range");
            }
            // stoi 直接检查 int 范围，避免 long long 转 int 时丢失数值。
            return {static_cast<std::int64_t>(timestamp),
                    std::stoi(temps[1], nullptr, 10),
                    std::stoi(temps[2], nullptr, 10)};
        } catch (const std::out_of_range&) {
            throw std::invalid_argument("Integer out of range");
        }
    }

    static std::vector<SensorRecord> read(std::istream& input) {
        std::string line;
        std::vector<SensorRecord> records;
        decltype(records.size()) line_number = 0;
        while (std::getline(input, line)) {
            ++line_number;
            try {
                records.push_back(parse_line(line));
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Line " + std::to_string(line_number)
                                            + ": " + e.what());
            }
        }
        return records;
    }
private:
    static std::string validate_integer(const std::string& field) {
        const auto first = field.find_first_not_of(" \t");
        if (first == std::string::npos) {
            throw std::invalid_argument("Empty field");
        }
        const auto last = field.find_last_not_of(" \t");
        const auto number = field.substr(first, last - first + 1);
        decltype(number.size()) i =
            (number[0] == '+' || number[0] == '-') ? 1 : 0;
        if (i == number.size()) {
            throw std::invalid_argument("Missing digits");
        }
        for (; i < number.size(); ++i) {
            if (number[i] < '0' || number[i] > '9') {
                throw std::invalid_argument("Invalid integer");
            }
        }
        return number;
    }
};
