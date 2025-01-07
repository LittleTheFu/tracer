#include "chessboardTexture.h"

ChessboardTexture::ChessboardTexture()
{
    m_factor = 0.02f;
}

Color ChessboardTexture::getColor(float u, float v) const
{
    auto iU = (static_cast<unsigned int>(u / m_factor)) % 2;
    auto iV = (static_cast<unsigned int>(v / m_factor)) % 2;

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