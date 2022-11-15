#include "LambertianMaterial.h"
#include "lambertian.h"
#include "common/common.h"

LambertianMaterial::LambertianMaterial(const Texture *pTexture, float scale)
{
    m_pLambertianBrdf = new Lambertian(scale);
    m_pTexture = pTexture;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    Color textureColor = m_pTexture->getColor(u, v);
    m_pLambertianBrdf->setColor(textureColor);

    Color f = m_pLambertianBrdf->sample_f(wo, wi, pdf);

    return f;
}