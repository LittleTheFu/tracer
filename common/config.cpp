#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_CUBE;

int configResolutionScale = 2;
int configSamplersPerPixel = 10;
int configNeeTracerDepth = 3;
float configLightIntensityScale = 50.0f;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;