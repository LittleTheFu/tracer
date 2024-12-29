#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

#include "sceneDef.h"
#include "tracerDef.h"

extern SceneType configScene;

extern int configResolutionScale;
extern int configSamplersPerPixel;
extern int configNeeTracerDepth;

extern std::string configOutputImageName;

extern bool configEnableLogProgress;
extern float configLambdaScale;

#endif