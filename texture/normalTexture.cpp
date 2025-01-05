#include <cassert>

#include "normalTexture.h"

NormalTexture::NormalTexture(const std::string fileName)
{
    m_ImageTexture = std::make_shared<ImageTexture>(fileName);
    assert(m_ImageTexture);
}

Color NormalTexture::getColor(float u, float v) const
{
    return m_ImageTexture->getColor(u, v);
}

Vector3 NormalTexture::getNormal(float u, float v) const
{
    Color color = m_ImageTexture->getColor(u, v);

    //maybe a converter is needed,later...
    Vector3 normal(color.r, color.g, color.b);
    normal = normal * 2.0f - Vector3::ONE;
    // normal.normalize();

    return normal;
}
