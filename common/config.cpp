#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_CUBE;

int configResolutionScale = 10;
int configSamplersPerPixel = 1024;
int configNeeTracerDepth = 10;
float configLightIntensityScale = 30.0f;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;