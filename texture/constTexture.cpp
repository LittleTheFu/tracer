#include "constTexture.h"

ConstTexture::ConstTexture(const Color &color)
{
    m_color = color;
}

Color ConstTexture::getColor(float u, float v) const
{
    return m_color;
}