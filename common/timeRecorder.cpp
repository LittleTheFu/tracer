#include <iomanip>
#include <iostream>

#include "timeRecorder.h"

void TimeRecorder::start()
{
    start_time = std::chrono::system_clock::now();
}

void TimeRecorder::end()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration d = now - start_time;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(d).count();

    auto hours = seconds / 3600;
    auto minutes = (seconds % 3600) / 60;
    auto secs = seconds % 60;

    std::cout << "total time : "
              << std::setw(6) << std::setfill('0') << hours << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"
              << std::setw(2) << std::setfill('0') << secs
              << std::endl;
}
