#include "fishEyeCamera.h"
#include "ball.h"

FishEyeCamera::FishEyeCamera() : Camera()
{
}

Ray FishEyeCamera::generateRay(float screenX, float screenY) const
{
    const float half_width = m_Width / 2.0f;
    const float half_height = m_Height / 2.0f;

    float u = (screenX - half_width) / half_width;
    u = (u + 1) / 2;
    // u -= 0.5;
    // if (u < 0)
    //     u += 1;

    float v = (screenY - half_height) / half_height;
    v = (v + 1) / 2;
    // v -= 0.5;
    // if (v < 0)
    //     v += 1;

    Ball ball;
    const Vector3 dir = ball.getLocalDirection(u, v);

    return Ray(Vector3::ZERO, dir);
}