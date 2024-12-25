#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_VOLUME;

bool configUseBVH = false;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::NEE_VOLUME;

int configCameraFactor = 3;
int configSamplersPerPixel = 3;
int configNeeTracerDepth = 10;

float configBnuuyScale = 300;
// float configBnuuyScale = 40;
std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_MIRROR;

std::string configOutputImageName = "img";

bool configLogProgress = true;

float configLightRadius = 20;
Vector3 configLightPos(0, 80, 200);
float configLightIntensity = 180;

float configLambdaScale = 0.6f;