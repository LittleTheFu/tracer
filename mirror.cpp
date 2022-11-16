#include "mirror.h"

Mirror::Mirror()
{

}

Color Mirror::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    const Vector3 local_wo = -wo;
    wi = local_wo.reflect(LOCAL_NORMAL);

    pdf = 1;

    return Color::COLOR_WHITE;
}

bool Mirror::isMirror() const
{
    return true;
}