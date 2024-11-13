#include "config.h"

ConfigScene configScene = ConfigScene::ROOM_VOLUME;

bool configUseBVH = false;
bool configUseSimpleTracer = true;

int configCameraFactor = 3;
int configBounceTime = 8;

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