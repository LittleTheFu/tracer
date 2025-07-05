#ifndef _MATERIAL_MANAGER_H_
#define _MATERIAL_MANAGER_H_

#include "material.h"
#include <memory>
#include <unordered_map>

class MaterialManager
{
public:
    MaterialManager();
    ~MaterialManager() = default;

    static MaterialManager &getInstance();

    int addMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> getMaterial(int id);

private:
    std::unordered_map<int, std::shared_ptr<Material>> m_materials;
};

#endif