#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_MATERIAL_BALLS;

bool configUseBVH = false;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::NEE;

int configCameraFactor = 3;
int configSamplersPerPixel = 3;
int configNeeTracerDepth = 3;

float configBnuuyScale = 700;
std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;

std::string configOutputImageName = "img";

bool configLogProgress = true;

float configLightRadius = 20;
Vector3 configLightPos(0, 40, 300);
float configLightIntensity = 100;

float configLambdaScale = 0.3f;