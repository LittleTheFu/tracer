#ifndef _PIN_HOLE_CAMERA_H_
#define _PIN_HOLE_CAMERA_H_

#include "camera.h"

class PinholeCamera : public Camera
{
public:
    PinholeCamera();

private:
    Ray generateRay(float screenX, float screenY) const;
};

#endif