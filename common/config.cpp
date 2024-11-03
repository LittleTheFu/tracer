#include "config.h"

//alpha scene is a bunny in the room
bool configUseBunnyScene = true;
bool configUseBVH = true;

bool configUseSimpleTracer = true;

int configCameraFactor = 6;
int configBounceTime = 6;

std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;