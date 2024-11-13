#include "config.h"

//alpha scene is a bunny in the room
bool configUseBunnyScene = false;
bool configUseBVH = false;

bool configUseSimpleTracer = false;//don't change it to false right now
bool configShowLightInSimperTracer = false;

int configCameraFactor = 3;
int configBounceTime = 8;

std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 30;
Vector3 configLightPos(0, -60, 300);

float configLambdaScale = 0.8f;