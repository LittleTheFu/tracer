#include "glass.h"
#include "color.h"
#include <cassert>
#include <algorithm>

Glass::Glass(float etaOutsie, float etaInside)
{
    assert(etaInside != 0);
    assert(etaOutsie != 0);

    m_etaInside = etaInside;
    m_etaOutside = etaOutsie;
}

Color Glass::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    Vector3 normal = LOCAL_NORMAL;
    float dot = wo * normal;
    if (dot < 0)
    {
        normal = -normal;
        std::swap(m_etaInside, m_etaOutside);
    }

    // Vector3 inputVector = Vector3(wo.x, wo.y, -wo.z);
    Vector3 inputVector = -wo;
    wi = inputVector.refract(normal, m_etaOutside, m_etaInside);

    pdf = 1;

    return Color::COLOR_WHITE;
}

bool Glass::isGlass() const
{
    return true;
}

bool Glass::isMirror() const
{
    return true;
}