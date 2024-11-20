#include "config.h"

ConfigScene configScene = ConfigScene::ROOM_SIMPLE;

bool configUseBVH = false;
bool configUseSimpleTracer = true;

int configCameraFactor = 10;
int configBounceTime = 10;

float configBnuuyScale = 40;
std::string configBunnyRes = ResourceDef::BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 25;
Vector3 configLightPos(0, 40, 300);
float configLightIntensity = 50;

float configLambdaScale = 0.5f;