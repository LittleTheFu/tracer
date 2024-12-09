#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_SIMPLE;

bool configUseBVH = false;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::SIMPLE;

int configCameraFactor = 16;
int configBounceTime = 8;
int configSamplersPerPixel = 8;

float configBnuuyScale = 500;
std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 16;
Vector3 configLightPos(0, 40, 300);
float configLightIntensity = 30;

float configLambdaScale = 0.5f;