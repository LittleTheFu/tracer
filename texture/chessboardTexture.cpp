#include "chessboardTexture.h"

Color ChessboardTexture::getColor(float u, float v) const
{
    int iU = (int)(u / 0.5);
    int iV = (int)(v / 0.5);

    if (iU == 0 && iV == 0)
    {
        return Color::COLOR_WHITE;
    }

    if (iU == 1 && iV == 1)
    {
        return Color::COLOR_WHITE;
    }

    return Color::COLOR_BLACK;
}