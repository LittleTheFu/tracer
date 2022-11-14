#include "LambertianMaterial.h"
#include "lambertian.h"
#include "common.h"

LambertianMaterial::LambertianMaterial(const Texture *pTexture, float scale)
{
    m_pLambertianBrdf = new Lambertian(Color::COLOR_BLACK, scale);
    m_pTexture = pTexture;
}

LambertianMaterial::LambertianMaterial(const Color &rho, float scale)
{
    m_pLambertianBrdf = new Lambertian(rho, scale);
    m_pTexture = nullptr;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    if (m_pTexture)
    {
        // f *= m_pTexture->getColor(u, v);
        // f += m_pTexture->getColor(u, v);
        // f /= 5;

        // WARNING: CAST
        Color textureColor = m_pTexture->getColor(u, v);
        m_pLambertianBrdf->setRho(textureColor);
        // ((Lambertian *)(m_pBrdf))->m_rho = m_pTexture->getColor(u, v) * Common::INV_PI;
    }

    Color f = m_pLambertianBrdf->sample_f(wo, wi, pdf);

    return f;
}
