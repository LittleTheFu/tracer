#include "imageTexture.h"
#include <lodepng/lodepng.h>
#include <iostream>

ImageTexture::ImageTexture(const std::string fileName) : m_width(0), m_height(0)
{
    // decode
    unsigned error = lodepng::decode(m_data, m_width, m_height, fileName);

    // if there's an error, display it
    if (error)
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

Color ImageTexture::getColor(float u, float v) const
{
    //something wrong here, uv passed was out of range
    //should be fixed later
    float uu = u - (int)u;
    float vv = v - (int)v;

    unsigned uPixel = (static_cast<unsigned>(uu) * m_width);
    unsigned vPixel = (static_cast<unsigned>(vv) * m_height);

    unsigned index = vPixel * m_width + uPixel;

    float r = m_data.at(4 * index + 0) / 255.0f;
    float g = m_data.at(4 * index + 1) / 255.0f;
    float b = m_data.at(4 * index + 2) / 255.0f;

    return Color(r, g, b);
}