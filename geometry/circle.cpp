#include "circle.h"
#include <cmath>
#include "common.h"

Circle::Circle(const Vector3 &center, const Vector3 &normal, float r)
{
    this->center = center;
    this->normal = normal;
    this->r = r;
}

// float Circle::getPhi(const Vector3 &p)
// {
//     float phi = std::atan2(p.y, p.x);
//     if (phi < 0)
//     {
//         phi += Common::PI * 2;
//     }

//     return phi;
// }

// float Circle::getTheta(const Vector3 &p)
// {
//     float a = p.z / r;
//     if (a < -1)
//         a = -1;
//     if (a > 1)
//         a = 1;

//     const float theta = std::acos(p.z / r);

//     return theta;
// }

// Vector3 Circle::dpdu(const Vector3 &p)
// {
//     const float phi = getPhi(p);
//     const float phi_max = Common::PI * 2;

//     const float x = -p.y * phi_max;
//     const float y = p.x * phi_max;
//     const float z = 0;

//     Vector3 v = Vector3(x, y, z);
//     v.normalize();

//     return v;
// }

// Vector3 Circle::dpdv(const Vector3 &p)
// {
//     const float phi = getPhi(p);
//     const float theta_range = Common::PI;

//     const float theta = getTheta(p);

//     const float x = p.z * std::cos(phi) * theta_range;
//     const float y = p.z * std::sin(phi) * theta_range;
//     const float z = -std::sin(theta) * theta_range;

//     Vector3 v = Vector3(x, y, z);
//     v.normalize();

//     return v;
// }
