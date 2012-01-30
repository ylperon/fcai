# pragma once

# ifdef WIN32
# include <windows.h>
# else
# include <ctime>
# endif //WIN32

# ifndef TEST_TIMER_H_
# define TEST_TIMER_H_

class Timer
{
public:
    void StartTiming();
    void StopTiming();
    double GetUserSeconds() const { return value; };
    long long GetUserTicks() const { return ticks; }

private:	
    double value;
    long long ticks;

# ifdef WIN32
    DWORD_PTR oldMask;
    LARGE_INTEGER timeStart;
# else
    time_t timeStart;
# endif //WIN32
};

# endif //TEST_TIMER_H_