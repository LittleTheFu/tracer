#include "LambertianMaterial.h"
#include "lambertian.h"
#include "common.h"

LambertianMaterial::LambertianMaterial(const Color &rho, const Texture *pTexture)
{
    m_pBrdf = new Lambertian(rho);
    m_pTexture = pTexture;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    if (m_pTexture)
    {
        // f *= m_pTexture->getColor(u, v);
        // f += m_pTexture->getColor(u, v);
        // f /= 5;

        // WARNING: CAST
        ((Lambertian *)(m_pBrdf))->m_rho = m_pTexture->getColor(u, v) * Common::INV_PI;
    }

    Color f = m_pBrdf->sample_f(wo, wi, pdf);

    return f;
}
