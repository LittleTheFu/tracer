#include <math.h>

#include "noiseTexture.h"

NoiseTexture::NoiseTexture(Color color)
{
    m_color = color;
}

Color NoiseTexture::getColor(float u, float v) const
{
    float f = 0;
    for (int i = 0; i < 5; i++)
    {
        float k = static_cast<float>(std::pow(2, i));
        f += m_noise.getValue(u * k, v * k) / k;
    }

    //remap to [0,1]
    f = (f + 2) / 4;

    return m_color * f;
}