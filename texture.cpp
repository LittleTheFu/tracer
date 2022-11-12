#include "texture.h"

Color Texture::getColor(float u, float v) const
{
    int iU = (int)(u / 0.1);
    int iV = (int)(v / 0.1);

    if(iU%2 && iV%2)
    {
        return Color::COLOR_WHITE;
    }

    return Color::COLOR_BLACK;
}