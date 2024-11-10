#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "resourceDef.h"
#include "materialDef.h"
#include "vector.h"

extern bool configUseBunnyScene;
extern bool configUseBVH;

extern bool configUseSimpleTracer;
extern bool configShowLightInSimperTracer;

extern int configCameraFactor;
extern int configBounceTime;

extern std::string configBunnyRes;
extern MATERIAL_TYPE configBunnyMaterial;

extern std::string configOutputImageName;

extern int configBatchStartBounce;
extern int configBatchEndBounces;
extern bool configUseBatchRun;

extern bool configLogProgress;

extern float configLightRadius;
extern Vector3 configLightPos;

#endif