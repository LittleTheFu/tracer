#ifndef _MATERIAL_MANAGER_H_
#define _MATERIAL_MANAGER_H_

#include "lambertianMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "materialDef.h"
#include <map>

class MaterialManager
{
public:
    MaterialManager();
    const static MaterialManager *getInstance();
    const Material *get(MATERIAL_TYPE type) const;

private:
    void init();

private:
    static MaterialManager *instance;

private:
    std::map<MATERIAL_TYPE, const Material *> m_map;

private:
    const Material *lambMtrlRed;
    const Material *lambMtrlYellow;
    const Material *lambMtrlAqua;
    const Material *lambMtrlPurple;
    const Material *lambMtrlGreen;
    const Material *lambMtrlBlue;
    const Material *lambMtrlWhite;

    const Material *mirrorMtrl;
    const Material *glassMtrl;
};

#endif