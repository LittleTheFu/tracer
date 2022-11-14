#ifndef _UV_TEXTURE_H_
#define _UV_TEXTURE_H_

#include "texture.h"
#include "color.h"

class UvTexture : public Texture
{
public:
    Color getColor(float u, float v) const;
};

#endif
