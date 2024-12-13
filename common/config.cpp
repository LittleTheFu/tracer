#include "config.h"

//don't use ROOM_VOLUME right now
ConfigScene configScene = ConfigScene::ROOM_TEAPOT;

bool configUseBVH = true;

//don't modify this because others are not done yet
TracerType configTracerType = TracerType::NEE;

int configCameraFactor = 1;
int configBounceTime = 8;//this one will be deleted soon
int configSamplersPerPixel = 3;
int configNeeTracerDepth = 10;

float configBnuuyScale = 700;
std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_MIRROR;

std::string configOutputImageName = "img";

//the three vars below are to be deleted soon
int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 16;
Vector3 configLightPos(0, 40, 250);
float configLightIntensity = 200;

float configLambdaScale = 0.3f;