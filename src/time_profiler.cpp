#include "test_time_profiler.h"

#include <stdexcept>

void TimeProfiler::StartTiming(const std::string& point) {
    if (table.find(point) == table.end()) {
        table.insert(std::make_pair(point, Timer()));
    }
    table[point].StartTiming();
}

void TimeProfiler::StopTiming(const std::string& point) {
    if (table.find(point) == table.end()) {
        throw std::runtime_error("can not find point");
    }
    table[point].StopTiming();
}

double TimeProfiler::GetUserSeconds(const std::string& point) const {
    if (table.find(point) == table.end()) {
        throw std::runtime_error("can not find point");
    }
    return table[point].GetUserSeconds();
}

long long TimeProfiler::GetUserTicks(const std::string& point) const {
    if (table.find(point) == table.end()) {
        throw std::runtime_error("can not find point");
    }
    return table[point].GetUserTicks();
}

void TimeProfiler::DeletePoint(const std::string& point) {
    table.erase(point);
}

void TimeProfiler::Clear() {
    table.clear();
}
