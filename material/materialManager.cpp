#include "materialManager.h"
#include "constTexture.h"
#include "imageTexture.h"
#include "resourceDef.h"
#include "config.h"

MaterialManager* MaterialManager::instance = nullptr;

MaterialManager::MaterialManager()
{
}

const MaterialManager *MaterialManager::getInstance()
{
    if (!MaterialManager::instance)
    {
        MaterialManager::instance = new MaterialManager();
        MaterialManager::instance->init();
    }

    return MaterialManager::instance;
}

void MaterialManager::init()
{
    float rho = configLambdaScale;

    lambMtrlRed = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_RED), rho);
    lambMtrlYellow = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_YELLOW), rho);
    lambMtrlAqua = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_AQUA), rho);
    lambMtrlPurple = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_PURPLE), rho);
    lambMtrlGreen = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_GREEN), rho);
    lambMtrlBlue = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_BLUE), rho);
    lambMtrlWhite = std::make_shared<LambertianMaterial>(std::make_shared<ConstTexture>(Color::COLOR_WHITE), rho);

    lambMtrlTexLena = std::make_shared<LambertianMaterial>(std::make_shared<ImageTexture>(ResourceDef::LENA), 1);

    mirrorMtrl = std::make_shared<MirrorMaterial>();
    glassMtrl = std::make_shared<GlassMaterial>();

    m_map[MATERIAL_TYPE::M_RED] = lambMtrlRed;
    m_map[MATERIAL_TYPE::M_YELLOW] = lambMtrlYellow;
    m_map[MATERIAL_TYPE::M_AQUA] = lambMtrlAqua;
    m_map[MATERIAL_TYPE::M_PURPLE] = lambMtrlPurple;
    m_map[MATERIAL_TYPE::M_GREEN] = lambMtrlGreen;
    m_map[MATERIAL_TYPE::M_BLUE] = lambMtrlBlue;
    m_map[MATERIAL_TYPE::M_WHITE] = lambMtrlWhite;
    m_map[MATERIAL_TYPE::M_LENA] = lambMtrlTexLena;
    m_map[MATERIAL_TYPE::M_MIRROR] = mirrorMtrl;
    m_map[MATERIAL_TYPE::M_GLASS] = glassMtrl;
}

std::shared_ptr<const Material> MaterialManager::get(MATERIAL_TYPE type) const
{
    auto it = m_map.find(type);

    if (it == m_map.end())
        return nullptr;

    return it->second;  
}