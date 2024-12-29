#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_SIMPLE;

int configResolutionScale = 4;
int configSamplersPerPixel = 4;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLightIntensity = 100.0f;
float configLambdaScale = 0.6f;