#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "color.h"

class Texture
{
public:
    Color getColor(float u, float v) const;
};

#endif