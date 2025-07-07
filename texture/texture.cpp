#include "texture.h"

Texture::Texture()
{
    std::cout << "Texture::Texture()" << std::endl;
}

Texture::~Texture()
{
}

Color Texture::getColor(float u, float v) const
{
    return Color::COLOR_BLACK;
}
