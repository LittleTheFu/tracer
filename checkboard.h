#ifndef _CHECKBOARD_H_
#define _CHECKBOARD_H_

#include "texture.h"

class Checkboard : public Texture
{
public:
    Color getColor(float u, float v) const;
};

#endif