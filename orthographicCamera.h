#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

#include "camera.h"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera();

private:
    Ray generateRay(float screenX, float screenY) const;
};

#endif