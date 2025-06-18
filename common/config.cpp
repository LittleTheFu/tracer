#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_TEAPOT_NORMAL_MAP;

int configResolutionScale = 1;
int configSamplersPerPixel = 1;
int configNeeTracerDepth = 8;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;