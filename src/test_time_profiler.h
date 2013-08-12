# pragma once

# ifndef TEST_TIME_PROFILER_H_
# define TEST_TIME_PROFILER_H_

# include <map>
# include <string>

# include "test_timer.h"

class TimeProfiler
{
public:
    void StartTiming(const char* point);
    void StartTiming(const std::string& point);

    void StopTiming(const char* point);
    void StopTiming(const std::string& point);

    double GetUserSeconds(const char* point) const;
    double GetUserSeconds(const std::string& point) const;

    long long GetUserTicks(const char* point) const;
    long long GetUserTicks(const std::string& point) const;

    void DeletePoint(const char* point);
    void DeletePoint(const std::string& point);

    void Clear();

private:
    std::map<std::string, Timer> table;
};

# endif //TEST_TIME_PROFILER_H_