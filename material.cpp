#include "material.h"

Material::Material()
{
    // m_pBrdf = nullptr;
    // m_pTexture = nullptr;
}

Color Material::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    // if (m_pBrdf)
    // {
    //     return m_pBrdf->sample_f(wo, wi, pdf);
    // }

    return Color::COLOR_BLACK;
}

bool Material::isMirror() const
{
    // if(m_pBrdf)
    // {
    //     return m_pBrdf->isMirror();
    // }

    return false;
}

// void Material::setBrdf(const Brdf *pBrdf)
// {
//     m_pBrdf = pBrdf;
// }

// const Brdf *Material::getBrdf() const
// {
//     return m_pBrdf;
// }

// void Material::setTexture(const Texture *pTexture)
// {
//     m_pTexture = pTexture;
// }

// const Texture *Material::getTexture() const
// {
//     return m_pTexture;
// }