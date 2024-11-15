#include "config.h"

ConfigScene configScene = ConfigScene::ROOM_BUNNY;

bool configUseBVH = true;
bool configUseSimpleTracer = true;

int configCameraFactor = 4;
int configBounceTime = 6;

float configBnuuyScale = 500;
std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_RED;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 25;
Vector3 configLightPos(0, 40, 300);
float configLightIntensity = 16;

float configLambdaScale = 0.5f;