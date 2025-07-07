#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_CUBE;

int configResolutionScale = 1;
int configSamplersPerPixel = 3;
int configNeeTracerDepth = 6;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;