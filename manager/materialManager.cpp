#include "materialManager.h"
#include "id.h"

MaterialManager::MaterialManager()
{
}

int MaterialManager::addMaterial(std::shared_ptr<Material> material)
{
    int id = ID::genId();
    m_materials[id] = material;
    return id;
}

std::shared_ptr<Material> MaterialManager::getMaterial(int id)
{
    if (m_materials.find(id) == m_materials.end())
        return nullptr;

    return m_materials[id];
}

MaterialManager &MaterialManager::getInstance()
{
    static MaterialManager instance;
    return instance;
}