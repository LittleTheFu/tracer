#ifndef _FISH_EYE_CAMERA_H_
#define _FISH_EYE_CAMERA_H_

#include "camera.h"

//bug, fix later
class FishEyeCamera : public Camera
{
public:
    FishEyeCamera();

private:
    Ray generateRay(float screenX, float screenY) const;
};

#endif