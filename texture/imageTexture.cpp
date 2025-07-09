#include <iostream>
#include <lodepng/lodepng.h>

#include "imageTexture.h"
#include <algorithm>
#include "perlinNoise.h"
#include <cassert>

ImageTexture::ImageTexture() : m_width(0), m_height(0)
{
}

ImageTexture::ImageTexture(const std::string &fileName) : m_width(0), m_height(0)
{
    // decode
    unsigned error = lodepng::decode(m_data, m_width, m_height, fileName);

    assert(error != 0);

    // if there's an error, display it
    if (error)
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

ImageTexture::ImageTexture(unsigned int width, unsigned int height, std::vector<unsigned char> &&data)
{
    m_width = width;
    m_height = height;
    m_data = std::move(data);
    // std::cout << "ImageTexture::ImageTexture(unsigned int width, unsigned int height, std::vector<unsigned char> &&data)" << std::endl;
}

ImageTexture::~ImageTexture()
{
    // std::cout << "ImageTexture::~ImageTexture()" << std::endl;
}

Color ImageTexture::getColor(float u, float v) const
{
    // Using the clamped version for robustness for general image textures
    float u_clamped = std::clamp(u, 0.0f, 1.0f);
    float v_clamped = std::clamp(v, 0.0f, 1.0f);

    unsigned uPixel = static_cast<unsigned>(u_clamped * (m_width - 1));
    unsigned vPixel = static_cast<unsigned>(v_clamped * (m_height - 1));

    unsigned int index = vPixel * m_width + uPixel;

    float r = static_cast<float>(m_data.at(4 * index + 0)) / 255.0f;
    float g = static_cast<float>(m_data.at(4 * index + 1)) / 255.0f;
    float b = static_cast<float>(m_data.at(4 * index + 2)) / 255.0f;

    return Color(r, g, b);
}

bool ImageTexture::writeToFile(const std::string &fileName) const
{
    unsigned error = lodepng::encode(fileName, m_data, m_width, m_height);

    if (error)
    {
        std::cerr << "LodePNG error " << error << ": " << lodepng_error_text(error) << std::endl;
        return false;
    }
    else
    {
        std::cout << "Image successfully saved to " << fileName << std::endl;
        return true;
    }
}

ImageTexture ImageTexture::createPerlinNoiseTexture(
    unsigned int width,
    unsigned int height,
    float noiseScale,
    float zSlice)
{
    PerlinNoise noiseGenerator;

    std::vector<unsigned char> image_data;
    image_data.resize(width * height * 4); // RGBA

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            float px = static_cast<float>(x) / width * noiseScale;
            float py = static_cast<float>(y) / height * noiseScale;
            float pz = zSlice;

            Vector3 current_point(px, py, pz);
            float noise_value = noiseGenerator.get(current_point);

            unsigned char gray = static_cast<unsigned char>((noise_value + 1.0f) * 0.5f * 255.0f);

            unsigned int index = (y * width + x) * 4;
            image_data[index + 0] = gray; // R
            image_data[index + 1] = gray; // G
            image_data[index + 2] = gray; // B
            image_data[index + 3] = 255;  // A
        }
    }

    return ImageTexture(width, height, std::move(image_data));
}
