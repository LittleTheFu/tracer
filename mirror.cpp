#include "mirror.h"

float Mirror::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    const Vector3 local_wo = -wo;
    wi = local_wo.reflect(LOCAL_NORMAL);

    pdf = 1;

    return 1;
}