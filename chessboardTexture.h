#ifndef _CHESSBOARD_TEXTURE_H_
#define _CHESSBOARD_TEXTURE_H_

#include "texture.h"

class ChessboardTexture : public Texture
{
public:
    Color getColor(float u, float v) const;
};

#endif