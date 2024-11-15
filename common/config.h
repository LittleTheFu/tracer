#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "resourceDef.h"
#include "materialDef.h"
#include "vector.h"

enum class ConfigScene {
    ROOM_BUNNY,
    ROOM_SIMPLE,
    ROOM_VOLUME,
};

extern ConfigScene configScene;
extern bool configUseBVH;

extern bool configUseSimpleTracer;
extern bool configShowLightInSimperTracer;

extern int configCameraFactor;
extern int configBounceTime;

extern float configBnuuyScale;
extern std::string configBunnyRes;
extern MATERIAL_TYPE configBunnyMaterial;

extern std::string configOutputImageName;

extern int configBatchStartBounce;
extern int configBatchEndBounces;
extern bool configUseBatchRun;

extern bool configLogProgress;

extern float configLightRadius;
extern Vector3 configLightPos;
extern float configLightIntensity;

extern float configLambdaScale;


#endif