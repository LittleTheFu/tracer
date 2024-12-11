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
    std::shared_ptr<const Material> lambMtrlRed;
    std::shared_ptr<const Material> lambMtrlYellow;
    std::shared_ptr<const Material> lambMtrlAqua;
    std::shared_ptr<const Material> lambMtrlPurple;
    std::shared_ptr<const Material> lambMtrlGreen;
    std::shared_ptr<const Material> lambMtrlBlue;
    std::shared_ptr<const Material> lambMtrlWhite;

    std::shared_ptr<const Material> lambMtrlTexLena;
    std::shared_ptr<const Material> lambMtrlTexChessBoard;

    std::shared_ptr<const Material> mirrorMtrl;
    std::shared_ptr<const Material> glassMtrl;

    std::shared_ptr<const Material> mixMtrl;
    std::shared_ptr<const Material> combinedMtrl;
};

#endif