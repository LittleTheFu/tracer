#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_TEAPOT;

int configResolutionScale = 8;
int configSamplersPerPixel = 12;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;