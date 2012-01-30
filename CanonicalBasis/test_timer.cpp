# include "test_timer.h"

void Timer::StartTiming()
{	
# ifdef WIN32
    oldMask = SetThreadAffinityMask(::GetCurrentThread(), 1);
# endif //WIN32

    /* 
    if processor support Intel Turbo Boost technology
    */
    volatile size_t warmingUp = 1;
    for (size_t i = 1; i < 100000; ++i)	
        warmingUp *= i;

# ifdef WIN32
    QueryPerformanceCounter(&timeStart);
# endif

# ifndef WIN32
    time(&timeStart);
# endif
}

void Timer::StopTiming()
{ 
# ifdef WIN32
    LARGE_INTEGER perfomanceFrequency;
    LARGE_INTEGER timeFinish;

    QueryPerformanceFrequency(&perfomanceFrequency);
    QueryPerformanceCounter(&timeFinish);
    SetThreadAffinityMask(::GetCurrentThread(), oldMask);
    value =	static_cast<double>(timeFinish.QuadPart - timeStart.QuadPart);
    value /= perfomanceFrequency.QuadPart;
    ticks = timeFinish.QuadPart - timeStart.QuadPart;
# else
    value = difftime(time(NULL), timeStart);
# endif //WIN33
}