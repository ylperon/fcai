# pragma once

# ifndef TEST_TIME_H_
# define TEST_TIME_H_

# include <ctime>
# include <cstdlib>
# include <ostream>

struct Time
{
    static const clock_t SECOND = CLOCKS_PER_SEC;
    static const clock_t MINUTE = SECOND * 60;
    static const clock_t HOUR = MINUTE * 60;	
    
    unsigned int hours;
    unsigned int minutes;
    double seconds;

    explicit Time(clock_t time = 0);
    //time must be in seconds
    explicit Time(double time);

    friend std::ostream &operator <<(std::ostream &output, const Time &time);
};

# endif //TEST_TIME_H_