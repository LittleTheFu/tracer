#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include "texture.h"

class Chessboard : public Texture
{
public:
    Color getColor(float u, float v) const;
};

#endif