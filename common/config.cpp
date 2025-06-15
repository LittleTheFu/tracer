#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_SIMPLE_BUNNY;

int configResolutionScale = 10;
int configSamplersPerPixel = 20;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;