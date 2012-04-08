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
# else 
# ifdef __unix__
    rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    timeStart = usage.ru_utime;
# else 
    time(&timeStart);
# endif //__unix__
# endif // WIN32
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
# ifdef __unix__
    rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    value = (double)(usage.ru_utime.tv_sec - timeStart.tv_sec) +
            (double)(usage.ru_utime.tv_usec - timeStart.tv_usec)/1e6;
# else
    value = difftime(time(NULL), timeStart);
# endif //__unix__
# endif //WIN32
}
