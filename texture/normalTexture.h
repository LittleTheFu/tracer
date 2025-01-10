#ifndef _NORMAL_TEXTURE_H_
#define _NORMAL_TEXTURE_H_

#include <string>
#include <memory>

#include "imageTexture.h"
#include "texture.h"
#include "vector.h"


class NormalTexture : public Texture
{
public:
    NormalTexture(const std::string fileName);
    virtual Color getColor(float u, float v) const override;

    Vector3 getNormal(float u, float v) const;

private:
    std::shared_ptr<ImageTexture> m_ImageTexture;
};


#endif