#include "config.h"

//don't use ROOM_VOLUME right now
SceneType configScene = SceneType::ROOM_MATERIAL_BALLS;

int configResolutionScale = 2;
int configSamplersPerPixel = 4;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;
float configLambdaScale = 0.6f;