#include "image.h"
#include "lodepng.h"
#include <iostream>

Image::Image(const std::string fileName) : m_width(0), m_height(0)
{
    // decode
    unsigned error = lodepng::decode(m_data, m_width, m_height, fileName);

    // if there's an error, display it
    if (error)
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

Color Image::getColor(float u, float v) const
{
    float uPixel = (unsigned)(u * m_width);
    float vPixel = (unsigned)(v * m_height);

    unsigned index = vPixel * m_width + uPixel;

    float r = m_data.at(4 * index + 0) / 255.0f;
    float g = m_data.at(4 * index + 1) / 255.0f;
    float b = m_data.at(4 * index + 2) / 255.0f;

    return Color(r, g, b);
}