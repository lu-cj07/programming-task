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
        (void)line;
        throw std::logic_error("TODO: SensorLog::parse_line");
    }

    static std::vector<SensorRecord> read(std::istream& input) {
        (void)input;
        throw std::logic_error("TODO: SensorLog::read");
    }
};
