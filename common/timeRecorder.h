#include <chrono>
#ifndef _TIME_RECORDER_H_
#define _TIME_RECORDER_H_

class TimeRecorder
{
public:
    void start();
    void end();

private:
    std::chrono::system_clock::time_point start_time;

};

#endif