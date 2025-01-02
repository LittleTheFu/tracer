#ifndef _NOISE_TEXTURE_H_
#define _NOISE_TEXTURE_H_

#include "texture.h"
#include "noise.h"

class NoiseTexture : public Texture
{
public:
    NoiseTexture(Color color);
    virtual Color getColor(float u, float v) const override;

private:
    Noise m_noise;
    Color m_color;
};

#endif