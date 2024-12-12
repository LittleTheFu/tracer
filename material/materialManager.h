#ifndef _MATERIAL_MANAGER_H_
#define _MATERIAL_MANAGER_H_

#include "material.h"
#include "materialDef.h"
#include <map>
#include <memory>

class MaterialManager
{
public:
    MaterialManager();
    const static MaterialManager *getInstance();
    std::shared_ptr<const Material> get(MATERIAL_TYPE type) const;

private:
    void init();

private:
    static MaterialManager *instance;

private:
    std::map<MATERIAL_TYPE, std::shared_ptr<const Material>> m_map;

private:
    std::shared_ptr<const Material> diffuseMtrlRed;
    std::shared_ptr<const Material> diffuseMtrlYellow;
    std::shared_ptr<const Material> diffuseMtrlAqua;
    std::shared_ptr<const Material> diffuseMtrlPurple;
    std::shared_ptr<const Material> diffuseMtrlGreen;
    std::shared_ptr<const Material> diffuseMtrlBlue;
    std::shared_ptr<const Material> diffuseMtrlWhite;

    std::shared_ptr<const Material> diffuseMtrlTexLena;
    std::shared_ptr<const Material> diffuseMtrlTexChessBoard;

    std::shared_ptr<const Material> mirrorMtrl;
    std::shared_ptr<const Material> glassMtrl;

    std::shared_ptr<const Material> dielectricMtrl;
    std::shared_ptr<const Material> combinedMtrl;
};

#endif