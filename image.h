#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "texture.h"
#include <string>
#include <vector>

class Image : public Texture
{
public:
    Image(const std::string fileName);
    Color getColor(float u, float v) const;

private:
    unsigned m_width;
    unsigned m_height;

    std::vector<unsigned char> m_data;
};

#endif