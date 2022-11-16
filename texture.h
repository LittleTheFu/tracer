#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "color.h"

class Texture
{
public:
    virtual Color getColor(float u, float v) const = 0;
};

#endif