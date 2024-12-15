#include "materialManager.h"
#include "constTexture.h"
#include "imageTexture.h"
#include "resourceDef.h"
#include "config.h"
#include "diffuseMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "dielectricMaterial.h"
#include "combinedMaterial.h"
#include "chessboardTexture.h"

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

    diffuseMtrlRed = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_RED), rho);
    diffuseMtrlYellow = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_YELLOW), rho);
    diffuseMtrlAqua = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_AQUA), rho);
    diffuseMtrlPurple = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_PURPLE), rho);
    diffuseMtrlGreen = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_GREEN), rho);
    diffuseMtrlBlue = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_BLUE), rho);
    diffuseMtrlWhite = std::make_shared<DiffuseMaterial>(std::make_shared<ConstTexture>(Color::COLOR_WHITE), rho);

    diffuseMtrlTexLena = std::make_shared<DiffuseMaterial>(std::make_shared<ImageTexture>(ResourceDef::LENA), 0.2f);
    diffuseMtrlTexChessBoard = std::make_shared<DiffuseMaterial>(std::make_shared<ChessboardTexture>(), 0.2f);

    mirrorMtrl = std::make_shared<MirrorMaterial>();
    glassMtrl = std::make_shared<GlassMaterial>();

    dielectricMtrl = std::make_shared<DielectricMaterial>();

    combinedMtrl = std::make_shared<CombinedMaterial>(diffuseMtrlTexChessBoard, mirrorMtrl);

    m_map[MATERIAL_TYPE::M_RED] = diffuseMtrlRed;
    m_map[MATERIAL_TYPE::M_YELLOW] = diffuseMtrlYellow;
    m_map[MATERIAL_TYPE::M_AQUA] = diffuseMtrlAqua;
    m_map[MATERIAL_TYPE::M_PURPLE] = diffuseMtrlPurple;
    m_map[MATERIAL_TYPE::M_GREEN] = diffuseMtrlGreen;
    m_map[MATERIAL_TYPE::M_BLUE] = diffuseMtrlBlue;
    m_map[MATERIAL_TYPE::M_WHITE] = diffuseMtrlWhite;
    m_map[MATERIAL_TYPE::M_LENA] = diffuseMtrlTexLena;
    m_map[MATERIAL_TYPE::M_CHESSBOARD] = diffuseMtrlTexChessBoard;
    m_map[MATERIAL_TYPE::M_MIRROR] = mirrorMtrl;
    m_map[MATERIAL_TYPE::M_GLASS] = glassMtrl;
    m_map[MATERIAL_TYPE::M_DIELECTRIC] = dielectricMtrl;
    m_map[MATERIAL_TYPE::M_COMBINED] = combinedMtrl;
}

std::shared_ptr<Material> MaterialManager::get(MATERIAL_TYPE type) const
{
    auto it = m_map.find(type);

    if (it == m_map.end())
        return nullptr;

    return it->second;  
}