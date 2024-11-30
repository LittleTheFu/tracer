#include "common.h"
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <sstream> 
#include <iomanip>
#include "mathConstantDef.h"

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);

Vector3 Common::getNormal(const Vector3 &from, const Vector3 &to)
{
    Vector3 r = to - from;
    r.normalize();

    return r;
}

void Common::printCurrentTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_time_t);

    std::cout << "Current time: " << std::put_time(&local_tm, "%H:%M:%S") << std::endl;
}