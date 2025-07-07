#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "texture.h"
#include <memory>
#include <unordered_map>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager() = default;

    static TextureManager &getInstance();

    int addTexture(std::shared_ptr<Texture> texture);
    std::shared_ptr<Texture> getTexture(int id);

private:
    std::unordered_map<int, std::shared_ptr<Texture>> m_textures;
};

#endif