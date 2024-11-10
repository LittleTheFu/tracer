#include "config.h"

//alpha scene is a bunny in the room
bool configUseBunnyScene = false;
bool configUseBVH = false;

bool configUseSimpleTracer = true;
bool configShowLightInSimperTracer = false;

int configCameraFactor = 3;
int configBounceTime = 6;

std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;

std::string configOutputImageName = "img";

int configBatchStartBounce = 3;
int configBatchEndBounces = 200;
bool configUseBatchRun = false;

bool configLogProgress = true;

float configLightRadius = 80;
extern Vector3 configLightPos(0, 0, 400);