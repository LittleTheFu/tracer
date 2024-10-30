#ifndef _CONFIG_H_
#define _CONFIG_H_

extern bool configUseAlphaScene;

extern bool configUseBVH;

extern int configCameraFactor;
extern int configBounceTime;

enum class BUNNY_TYPE
{
    LOW_LOW = 0,
    LOW,
    SIMPLE,
    ORIGIN,
};

extern BUNNY_TYPE bunnyType;

#endif