#include "sensor_log.hpp"
#include <cassert>
#include <cstdint>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

static bool invalid_line(const std::string& s) {
    try { (void)SensorLog::parse_line(s); }
    catch (const std::invalid_argument&) { return true; }
    return false;
}

int main() {
    {
        auto r = SensorLog::parse_line("  -123 , +20 , -30  ");
        assert(r.timestamp_ms == -123 && r.left_rpm == 20 && r.right_rpm == -30);
    }
    {
        auto r = SensorLog::parse_line("0,0,0\r");
        assert(r.timestamp_ms == 0 && r.left_rpm == 0 && r.right_rpm == 0);
    }
    {
        auto r = SensorLog::parse_line("-9223372036854775808,0,0");
        assert(r.timestamp_ms == std::numeric_limits<std::int64_t>::min());
    }
    for (const auto& bad : std::vector<std::string>{
        "", "   ", "1,2", "1,2,3,4", "1,2,3,", ",2,3", "1,,3",
        "1,2,", "1,2,3x", "1,2.0,3", "1,+ 2,3", "1,2 3,4",
        "9223372036854775808,1,2", "1,0x10,2"
    }) assert(invalid_line(bad));
    if (std::numeric_limits<int>::max() == 2147483647) {
        assert(invalid_line("1,2147483648,2"));
        assert(invalid_line("1,2,-2147483649"));
    }
    {
        std::istringstream input("");
        assert(SensorLog::read(input).empty());
    }
    {
        std::istringstream input("1,2,3\r\n2,-4,+5\r\n2,0,0\r\n");
        auto v = SensorLog::read(input);
        assert(v.size() == 3);
        assert(v[0].timestamp_ms == 1 && v[0].left_rpm == 2 && v[0].right_rpm == 3);
        assert(v[1].timestamp_ms == 2 && v[1].left_rpm == -4 && v[1].right_rpm == 5);
        assert(v[2].timestamp_ms == 2 && v[2].left_rpm == 0);
    }
    {
        std::istringstream input("1,2,3\n2,3,4\ninvalid\n4,5,6\n");
        bool caught = false;
        try { (void)SensorLog::read(input); }
        catch (const std::invalid_argument& e) {
            caught = std::string(e.what()).find("3") != std::string::npos;
        }
        assert(caught);
    }
    {
        std::istringstream input("1,2,3\n\n");
        bool caught = false;
        try { (void)SensorLog::read(input); }
        catch (const std::invalid_argument& e) {
            caught = std::string(e.what()).find("2") != std::string::npos;
        }
        assert(caught);
    }
}
