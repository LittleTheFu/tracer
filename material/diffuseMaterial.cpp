#include "diffuseMaterial.h"
#include "diffuseBrdf.h"
#include "common.h"

DiffuseMaterial::DiffuseMaterial(std::shared_ptr<Texture> pTexture, float scale)
{
    m_pDiffuseBrdf = std::make_shared<DiffuseBrdf>(scale);
    m_pTexture = pTexture;
}

Color DiffuseMaterial::eval(float u,
                            float v,
                            const Vector3 &wo,
                            Vector3 &wi,
                            float &pdf,
                            bool &isDelta,
                            std::shared_ptr<Brdf> &brdf)
{
    isDelta = false;
    Color textureColor = m_pTexture->getColor(u, v);
    m_pDiffuseBrdf->setColor(textureColor);
    brdf = m_pDiffuseBrdf->clone();

    Color f = m_pDiffuseBrdf->sample_f(wo, wi, pdf);

    return f;
}