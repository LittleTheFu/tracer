#include "lambertianMaterial.h"
#include "diffuseBrdf.h"
#include "common.h"

LambertianMaterial::LambertianMaterial(std::shared_ptr<const Texture> pTexture, float scale)
{
    m_pDiffuseBrdf = std::make_shared<DiffuseBrdf>(scale);
    m_pTexture = pTexture;
}

Color LambertianMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    Color f = m_pDiffuseBrdf->get_f(wo, wi);

    return f;
}

Color LambertianMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const
{
    isDelta = false;
    Color textureColor = m_pTexture->getColor(u, v);
    m_pDiffuseBrdf->setColor(textureColor);

    Color f = m_pDiffuseBrdf->sample_f(wo, wi, pdf);

    return f;
}