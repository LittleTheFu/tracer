#ifndef _CONST_TEXTURE_H_
#define _CONST_TEXTURE_H_

#include "texture.h"
#include "color.h"

class ConstTexture : public Texture
{
public:
    ConstTexture(const Color &color);
    Color getColor(float u, float v) const;

private:
    Color m_color;
};

#endif