#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <vector>

#include "texture.h"

class ImageTexture : public Texture
{
public:
    ImageTexture(const std::string fileName);
    Color getColor(float u, float v) const;

private:
    unsigned m_width;
    unsigned m_height;

    std::vector<unsigned char> m_data;
};

#endif