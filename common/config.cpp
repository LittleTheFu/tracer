#include "config.h"

//alpha scene is a bunny in the room
bool configUseBunnyScene = false;
bool configUseBVH = false;

bool configUseSimpleTracer = true;

int configCameraFactor = 6;
int configBounceTime = 8;

std::string configBunnyRes = ResourceDef::SIMPLE_BUNNY;
MATERIAL_TYPE configBunnyMaterial = MATERIAL_TYPE::M_GLASS;