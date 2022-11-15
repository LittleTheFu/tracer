#include "noiseTexture.h"

NoiseTexture::NoiseTexture(Color color)
{
    m_color = color;
}

Color NoiseTexture::getColor(float u, float v) const
{
    float n = m_noise.getValue(u, v);
    float f = (n + 1) / 2;

    return m_color * f;
}