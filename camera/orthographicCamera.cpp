#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(std::shared_ptr<Tracer> tracer) : Camera(tracer)
{
}

Ray OrthographicCamera::generateRay(float screenX, float screenY) const
{
    const int PIXEL_SIZE_FACTOR = 100;

    const float half_width = m_Width / 2.0f;
    const float half_height = m_Height / 2.0f;

    const Vector3 origin(100 * (screenX - half_width) / half_width, 100 * (screenY - half_height) / half_height, 0);
    const Vector3 dir(0, 0, 1);

    return Ray(origin, dir);
}