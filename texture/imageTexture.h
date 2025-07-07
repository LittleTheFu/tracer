#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <vector>
#include <color.h>

#include "texture.h"

class ImageTexture : public Texture
{
public:
    ImageTexture();
    ImageTexture(const std::string &fileName);
    ImageTexture(unsigned int width, unsigned int height, std::vector<unsigned char> &&data);

    ~ImageTexture();

    virtual Color getColor(float u, float v) const override;

    bool writeToFile(const std::string &fileName) const;

    // Hotfix: should be extracted elsewhere later
    static ImageTexture createPerlinNoiseTexture(unsigned int width, unsigned int height, float noiseScale, float zSlice);

private:
    unsigned m_width;
    unsigned m_height;

    std::vector<unsigned char> m_data;
};

#endif