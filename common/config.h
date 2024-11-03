#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "resourceDef.h"
#include "materialDef.h"

extern bool configUseBunnyScene;
extern bool configUseBVH;

extern bool configUseSimpleTracer;

extern int configCameraFactor;
extern int configBounceTime;

extern std::string configBunnyRes;
extern MATERIAL_TYPE configBunnyMaterial;

#endif