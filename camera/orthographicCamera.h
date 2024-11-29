#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

#include "camera.h"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(std::shared_ptr<Tracer> tracer);

private:
    Ray generateRay(float screenX, float screenY) const;
};

#endif