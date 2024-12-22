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
    std::shared_ptr<Material> get(MATERIAL_TYPE type) const;

private:
    void init();

private:
    static MaterialManager *instance;

private:
    std::map<MATERIAL_TYPE, std::shared_ptr<Material>> m_map;

private:
    std::shared_ptr<Material> diffuseMtrlRed;
    std::shared_ptr<Material> diffuseMtrlYellow;
    std::shared_ptr<Material> diffuseMtrlAqua;
    std::shared_ptr<Material> diffuseMtrlPurple;
    std::shared_ptr<Material> diffuseMtrlGreen;
    std::shared_ptr<Material> diffuseMtrlBlue;
    std::shared_ptr<Material> diffuseMtrlWhite;

    std::shared_ptr<Material> diffuseMtrlTexLena;
    std::shared_ptr<Material> diffuseMtrlTexChessBoard;

    std::shared_ptr<Material> mirrorMtrl;
    std::shared_ptr<Material> glassMtrl;

    std::shared_ptr<Material> dielectricMtrl;
    std::shared_ptr<Material> combinedMtrl;

    std::shared_ptr<Material> conductorMtrl;

    std::shared_ptr<Material> measuredWhiteMtrl;
    std::shared_ptr<Material> measuredGreenMtrl;
    std::shared_ptr<Material> measuredMetalMtrl;
    std::shared_ptr<Material> measuredMintMtrl;
};

#endif