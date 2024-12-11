#include "mirror.h"

Mirror::Mirror()
{

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
