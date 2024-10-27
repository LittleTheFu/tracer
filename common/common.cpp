#include "common.h"
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <sstream> 
#include <iomanip>
#include "mathConstantDef.h"

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);
const Color Common::LIGHT_COLOR = Color::COLOR_WHITE;

const float Common::SAMPLE_LIGHTR_CORRECT_FACTOR = 0.96f;

const float Common::SIGMA_T = 0.1f;
const float Common::SIGMA_S = 0.2f;

const void Common::printCurrentTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_time_t);

    std::cout << "Current time: " << std::put_time(&local_tm, "%H:%M:%S") << std::endl;
}