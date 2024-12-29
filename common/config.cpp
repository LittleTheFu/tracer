#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_SIMPLE;

bool configUseBVH = false;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::NEE;

int configCameraFactor = 10;
int configSamplersPerPixel = 1;
int configNeeTracerDepth = 10;

std::string configOutputImageName = "img";

bool configEnableLogProgress = true;

float configLightIntensity = 100.0f;

float configLambdaScale = 0.6f;