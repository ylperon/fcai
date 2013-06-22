# include "test_time_profiler.h"

# include <stdexcept>

void TimeProfiler::StartTiming(const std::string& point)
{
    std::map<std::string, Timer>::iterator it = table.find(point);
    if (table.end() == it)
    {
        it->second = Timer();
    }

    it->second.StartTiming();
}

void TimeProfiler::StartTiming(const char* point)
{
    StartTiming(std::string(point));
}

void TimeProfiler::StopTiming(const std::string& point)
{
    std::map<std::string, Timer>::iterator it = table.find(point);
    if (table.end() == it)
    {
        throw std::runtime_error("in TimeProfiler::StopTiming(const std::string&) "
                                 "can not find point");
    }

    it->second.StopTiming();
}

void TimeProfiler::StopTiming(const char* point)
{
    StopTiming(std::string(point));
}

double TimeProfiler::GetUserSeconds(const std::string& point) const
{
    std::map<std::string, Timer>::const_iterator it = table.find(point);
    if (table.end() == it)
    {
        throw std::runtime_error("in TimeProfiler::GetUserSeconds(const std::string&) "
                                 "can not find point");
    }

    return it->second.GetUserSeconds();
}

double TimeProfiler::GetUserSeconds(const char* point) const
{
    return GetUserSeconds(std::string(point));
}

long long TimeProfiler::GetUserTicks(const std::string& point) const
{
    std::map<std::string, Timer>::const_iterator it = table.find(point);
    if (table.end() == it)
    {
        throw std::runtime_error("in TimeProfiler::GetUserSeconds(const std::string&) "
                                 "can not find point");
    }

    return it->second.GetUserTicks();
}

long long TimeProfiler::GetUserTicks(const char* point) const
{
    return GetUserTicks(std::string(point));
}

void TimeProfiler::DeletePoint(const std::string& point)
{
    table.erase(point);
}

void TimeProfiler::DeletePoint(const char* point)
{
    table.erase(std::string(point));
}

void TimeProfiler::Clear()
{
    table.clear();
}