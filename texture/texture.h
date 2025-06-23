#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "color.h"

class Texture
{
public:
    Texture();
    virtual ~Texture();

    virtual Color getColor(float u, float v) const;
};

#endif