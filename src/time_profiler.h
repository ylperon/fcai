#pragma once

#include <map>
#include <string>

#include "test_timer.h"

class TimeProfiler {
public:
    void StartTiming(const std::string& point);
    void StopTiming(const std::string& point);
    double GetUserSeconds(const std::string& point) const;
    long long GetUserTicks(const std::string& point) const;
    void DeletePoint(const std::string& point);

    void Clear();
private:
    std::map<std::string, Timer> table;
};
