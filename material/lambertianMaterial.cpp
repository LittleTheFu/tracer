#include "lambertianMaterial.h"
#include "lambertian.h"
#include "common.h"

LambertianMaterial::LambertianMaterial(std::shared_ptr<const Texture> pTexture, float scale)
{
    m_pLambertianBrdf = std::make_shared<Lambertian>(scale);
    m_pTexture = pTexture;
}

Color LambertianMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    Color f = m_pLambertianBrdf->get_f(wo, wi);

    return f;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const
{
    isDelta = false;
    Color textureColor = m_pTexture->getColor(u, v);
    m_pLambertianBrdf->setColor(textureColor);

    Color f = m_pLambertianBrdf->sample_f(wo, wi, pdf);

    return f;
}