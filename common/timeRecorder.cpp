#include "timeRecorder.h"
#include <iostream>

void TimeRecorder::start()
{
    start_time = std::chrono::system_clock::now();
}

void TimeRecorder::end()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration d = now - start_time;

    // char timeStr[128];
    // int error = ctime_s(timeStr, 128, &d);

    std::cout << "total time : " << d.count() <<std::endl;
}
