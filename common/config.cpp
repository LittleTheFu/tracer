#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_VOLUME;

int configResolutionScale = 6;
int configSamplersPerPixel = 64;
int configNeeTracerDepth = 12;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;