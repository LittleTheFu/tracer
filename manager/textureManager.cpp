#include "textureManager.h"
#include "id.h"
#include "materialManager.h"

TextureManager::TextureManager()
{
}

TextureManager &TextureManager::getInstance()
{
    static TextureManager instance;
    return instance;
}

int TextureManager::addTexture(std::shared_ptr<Texture> texture)
{
    int id = ID::genId();
    m_textures[id] = texture;
    return id;
}

std::shared_ptr<Texture> TextureManager::getTexture(int id)
{
    if (m_textures.find(id) == m_textures.end())
        return nullptr;

    return m_textures[id];
}
