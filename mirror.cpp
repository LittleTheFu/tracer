#include "mirror.h"

Mirror::Mirror()
{

}

Color Mirror::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    const Vector3 local_wo = -wo;
    wi = local_wo.reflect(LOCAL_NORMAL);

    // if(wi.z < 0)
    // {
    //     int a = 2;
    // }

    pdf = 1;

    return Color::COLOR_WHITE;
}

bool Mirror::isMirror() const
{
    return true;
}