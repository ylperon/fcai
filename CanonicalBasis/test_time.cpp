# include "test_time.h"

# include <iomanip>
# include <cmath>

Time::Time(clock_t time)
{	
    hours = time / HOUR;
    time %= HOUR;
    minutes = time / MINUTE;
    time %= MINUTE;
    seconds = (double)time / (double)SECOND;
}

Time::Time(double time)
{
    hours = static_cast<size_t>(floor(time / static_cast<double>(60 * 60)));
    time -= hours * static_cast<double>(60 * 60);
    minutes = static_cast<size_t>(floor(time / static_cast<double>(60)));
    time -= minutes * static_cast<double>(60);
    seconds = time;
}

std::ostream &operator <<(std::ostream &output, const Time &time)
{	
    output << std::setfill('0') << std::setw(2) << time.hours;
    output << ':';
    output << std::setfill('0') << std::setw(2) << time.minutes;
    output << ':';
    output << std::setprecision(7) << time.seconds;

    return output;
}