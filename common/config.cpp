#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_TEAPOT;

int configResolutionScale = 4;
int configSamplersPerPixel = 1;
int configNeeTracerDepth = 3;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;