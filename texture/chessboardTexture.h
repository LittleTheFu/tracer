#ifndef _CHESSBOARD_TEXTURE_H_
#define _CHESSBOARD_TEXTURE_H_

#include "texture.h"

class ChessboardTexture : public Texture
{
public:
    ChessboardTexture();
    Color getColor(float u, float v) const;

private:
    float m_factor;
};

#endif