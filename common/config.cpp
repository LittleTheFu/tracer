#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_BUNNY;

bool configUseBVH = true;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::NEE;

int configCameraFactor = 10;
int configBounceTime = 8;//this one will be deleted soon
int configSamplersPerPixel = 100;
int configNeeTracerDepth = 30;

float configBnuuyScale = 50;
std::string configBunnyRes = ResourceDef::BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_MIX;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 16;
Vector3 configLightPos(30, 40, 300);
float configLightIntensity = 160;

float configLambdaScale = 0.3f;