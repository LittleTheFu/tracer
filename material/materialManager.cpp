#include "materialManager.h"
#include "constTexture.h"

MaterialManager* MaterialManager::instance = nullptr;

MaterialManager::MaterialManager()
{
}

const MaterialManager *MaterialManager::getInstance()
{
    if(!MaterialManager::instance)
    {
        MaterialManager::instance = new MaterialManager();
        MaterialManager::instance->init();
    }

    return MaterialManager::instance;
}

void MaterialManager::init()
{
    float rho = 0.4f;

    lambMtrlRed = new LambertianMaterial(new ConstTexture(Color::COLOR_RED), rho);
    lambMtrlYellow = new LambertianMaterial(new ConstTexture(Color::COLOR_YELLOW), rho);
    lambMtrlAqua = new LambertianMaterial(new ConstTexture(Color::COLOR_AQUA), rho);
    lambMtrlPurple = new LambertianMaterial(new ConstTexture(Color::COLOR_PURPLE), rho);
    lambMtrlGreen = new LambertianMaterial(new ConstTexture(Color::COLOR_GREEN), rho);
    lambMtrlBlue = new LambertianMaterial(new ConstTexture(Color::COLOR_BLUE), rho);
    lambMtrlWhite = new LambertianMaterial(new ConstTexture(Color::COLOR_WHITE), rho);

    MtrlMirror = new MirrorMaterial();
    MtrlGlass = new GlassMaterial();

    m_map.insert(std::make_pair(MATERIAL_TYPE::M_RED, lambMtrlRed));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_YELLOW, lambMtrlYellow));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_AQUA, lambMtrlAqua));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_PURPLE, lambMtrlPurple));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_GREEN, lambMtrlGreen));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_BLUE, lambMtrlBlue));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_WHITE, lambMtrlWhite));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_MIRROR, MtrlMirror));
    m_map.insert(std::make_pair(MATERIAL_TYPE::M_GLASS, MtrlGlass));
}

const Material *MaterialManager::get(MATERIAL_TYPE type) const
{
    auto it = m_map.find(type);

    if(it == m_map.end())
        return nullptr;
        
    return it->second;
}
