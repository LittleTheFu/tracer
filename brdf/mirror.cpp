#include "mirror.h"

Mirror::Mirror()
{

}

Color Mirror::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

Color Mirror::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    const Vector3 local_wo = -wo;
    
    Vector3 n = LOCAL_NORMAL;
    if(local_wo.isSameDir(n))
    {
        wi = Vector3::ZERO;
        pdf = 1;
        return Color::COLOR_BLACK;
        
        n = -n;
    }

    wi = local_wo.reflect(n);

    pdf = 1;

    return Color::COLOR_WHITE;
}

float Mirror::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}
