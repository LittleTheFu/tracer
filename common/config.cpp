#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_VOLUME;

int configResolutionScale = 4;
int configSamplersPerPixel = 256;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;