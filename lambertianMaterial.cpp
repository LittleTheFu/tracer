#include "LambertianMaterial.h"
#include "lambertian.h"

LambertianMaterial::LambertianMaterial(const Color &rho, const Texture *pTexture)
{
    m_pBrdf = new Lambertian(rho);
    m_pTexture = pTexture;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    Color f = m_pBrdf->sample_f(wo, wi, pdf);

    if (m_pTexture)
    {
        f *= m_pTexture->getColor(u, v);
    }

    return f;
}
