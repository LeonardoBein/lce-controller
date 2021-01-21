#ifndef TIME_H
#define TIME_H 1

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Time{
public:

    static void sleep_time (unsigned int seconds);
};

#endif // TIME_H