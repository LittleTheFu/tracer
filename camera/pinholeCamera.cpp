#include "pinholeCamera.h"

PinholeCamera::PinholeCamera() : Camera()
{
}

Ray PinholeCamera::generateRay(float screenX, float screenY) const
{
    const float half_width = m_Width / 2.0f;
    const float half_height = m_Height / 2.0f;

    const Vector3 origin(0, 0, 0);
    const Vector3 dir((screenX - half_width) / half_width, (screenY - half_height) / half_height, 2);

    return Ray(origin, dir);
}
