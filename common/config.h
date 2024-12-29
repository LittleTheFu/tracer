#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

#include "tracerDef.h"

enum class ConfigScene {
    ROOM_SIMPLE = 0,
    ROOM_BUNNY,
    ROOM_TEAPOT,
    ROOM_MATERIAL_BALLS,
    // ROOM_VOLUME,
};

extern ConfigScene configScene;
extern bool configUseBVH;

extern TracerType configTracerType;

extern int configCameraFactor;
extern int configSamplersPerPixel;
extern int configNeeTracerDepth;


extern std::string configOutputImageName;

extern bool configEnableLogProgress;
extern float configLightIntensity;
extern float configLambdaScale;

#endif