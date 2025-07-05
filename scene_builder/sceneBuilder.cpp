#include <memory>

#include "ball.h"
#include "curve.h"
#include "mathConstantDef.h"
#include "mesh.h"
#include "plane.h"
#include "resourceDef.h"
#include "room.h"
#include "sceneBuilder.h"
#include "tagDef.h"
#include "materialLambertian.h"
#include "geometryPrimitive.h"
#include "areaLight.h"
#include "emittingMaterial.h"
#include "materialPVC.h"
#include "materialMirror.h"
#include "materialGlass.h"
#include "materialSilk.h"
#include "materialTarkinTunic.h"
#include <cassert>
#include "materialRough.h"
#include "materialTRough.h"
#include <materialManager.h>
#include <model.h>


void SceneBuilder::init(std::shared_ptr<ObjectPool> pool)
{
    m_pObjectPool = pool;
}

void SceneBuilder::buildRoom()
{
    const float c = 100;
    const float r = 5 * c;

    MATERIAL_TYPE leftMtrl = getLeftWallMaterial();
    MATERIAL_TYPE rightMtrl = getRightWallMaterial();
    MATERIAL_TYPE topMtrl = getCeilingMaterial();
    MATERIAL_TYPE bottomMtrl = getFloorMaterial();
    MATERIAL_TYPE frontMtrl = getFrontWallMaterial();
    MATERIAL_TYPE backMtrl = getBackWallMaterial();

    Vector3 leftRotate(0, MathConstant::PI / 2, 0);
    Vector3 leftPosition(-c, 0, 0);
    std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(leftRotate, leftPosition, r);
    std::shared_ptr<Material> leftMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_RED);

    Vector3 rightRotate(0, -MathConstant::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(rightRotate, rightPosition, r);
    std::shared_ptr<Material> rightMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_BLUE);


    Vector3 bottomRotate(MathConstant::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    std::shared_ptr<Plane> bottomPlane = std::make_shared<Plane>(bottomRotate, bottomPosition, r);
    std::shared_ptr<Material> bottomMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_GREEN);
    

    Vector3 topRotate(-MathConstant::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(topRotate, topPosition, r);
    std::shared_ptr<Material> topMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_YELLOW);

    Vector3 frontRotate(MathConstant::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    std::shared_ptr<Plane> frontPlane = std::make_shared<Plane>(frontRotate, frontPosition, r);
    std::shared_ptr<Material> frontMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_PINK);

    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(backRotate, backPosition, r);
    std::shared_ptr<Material> backMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_ORANGE);

    //---------------for refactoring-------
    std::shared_ptr<GeometryPrimitive> leftPrimitive = std::make_shared<GeometryPrimitive>(leftPlane, leftMtrlLambertian);
    m_pObjectPool->addPrimitive(leftPrimitive);

    std::shared_ptr<GeometryPrimitive> rightPrimitive = std::make_shared<GeometryPrimitive>(rightPlane, rightMtrlLambertian);
    m_pObjectPool->addPrimitive(rightPrimitive);
    
    std::shared_ptr<GeometryPrimitive> topPrimitive = std::make_shared<GeometryPrimitive>(topPlane, topMtrlLambertian);

    m_pObjectPool->addPrimitive(topPrimitive);

    std::shared_ptr<GeometryPrimitive> bottomPrimitive = std::make_shared<GeometryPrimitive>(bottomPlane, bottomMtrlLambertian);
    m_pObjectPool->addPrimitive(bottomPrimitive);

    std::shared_ptr<GeometryPrimitive> frontPrimitive = std::make_shared<GeometryPrimitive>(frontPlane, frontMtrlLambertian);
    m_pObjectPool->addPrimitive(frontPrimitive);

    std::shared_ptr<GeometryPrimitive> backPrimitive = std::make_shared<GeometryPrimitive>(backPlane, backMtrlLambertian);
    m_pObjectPool->addPrimitive(backPrimitive);
}

MATERIAL_TYPE SceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_RED;
}

MATERIAL_TYPE SceneBuilder::getRightWallMaterial() const
{
    return MATERIAL_TYPE::M_BLUE;
}

MATERIAL_TYPE SceneBuilder::getFloorMaterial() const
{
    return MATERIAL_TYPE::M_COMBINED;
}

MATERIAL_TYPE SceneBuilder::getCeilingMaterial() const
{
    return MATERIAL_TYPE::M_CHESSBOARD;
}

MATERIAL_TYPE SceneBuilder::getFrontWallMaterial() const
{
    return MATERIAL_TYPE::M_YELLOW;
}

MATERIAL_TYPE SceneBuilder::getBackWallMaterial() const
{
    return MATERIAL_TYPE::M_RED;
}

void SceneBuilder::buildMeshRoom()
{
    // std::shared_ptr<Room> room = std::make_shared<Room>();
    // m_pObjectPool->add(room->getTris());
}

void SceneBuilder::buildLight(const Vector3 &pos, float r)
{
    std::shared_ptr<Material> lightMaterial = std::make_shared<EmittingMaterial>();

    //----------------------first--------
    std::shared_ptr<Geometry> ballFirst = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<GeometryPrimitive> lightPrimitiveFirst = std::make_shared<GeometryPrimitive>(ballFirst, lightMaterial);
    std::shared_ptr<AreaLight> areaLightFirst = std::make_shared<AreaLight>(lightPrimitiveFirst);

    m_pObjectPool->addLight(areaLightFirst);
    m_pObjectPool->addPrimitive(lightPrimitiveFirst);

    //----------------------second--------
    // std::shared_ptr<Geometry> ballSecond = std::make_shared<Ball>(Vector3::ZERO, pos + Vector3(50, 0, 0), r);
    // std::shared_ptr<GeometryPrimitive> lightPrimitiveSecond = std::make_shared<GeometryPrimitive>(ballSecond, lightMaterial);
    // std::shared_ptr<AreaLight> areaLightSecond = std::make_shared<AreaLight>(lightPrimitiveSecond);

    // m_pObjectPool->addLight(areaLightSecond);
    // m_pObjectPool->addPrimitive(lightPrimitiveSecond);

    //----------------------third--------
    // std::shared_ptr<Geometry> ballThird = std::make_shared<Ball>(Vector3::ZERO, pos + Vector3(-50, 0, 0), r);
    // std::shared_ptr<GeometryPrimitive> lightPrimitiveThird = std::make_shared<GeometryPrimitive>(ballThird, lightMaterial);
    // std::shared_ptr<AreaLight> areaLightThird = std::make_shared<AreaLight>(lightPrimitiveThird);

    // m_pObjectPool->addLight(areaLightThird);
    // m_pObjectPool->addPrimitive(lightPrimitiveThird);
}

void SceneBuilder::setLightIntensity(size_t index, float intensity)
{
    if (!m_pObjectPool)
        return;

    if ( index >= m_pObjectPool->lights_.size())
        return;

    m_pObjectPool->lights_.at(index)->setIntensity(intensity);
}

void SceneBuilder::buildSceneWithDefaultConfig()
{
}

void SceneBuilder::buildGlassBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> glassBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<Material> glassMaterial = std::make_shared<MaterialGlass>();

    std::shared_ptr<GeometryPrimitive> glassPrimitive = std::make_shared<GeometryPrimitive>(glassBall, glassMaterial);
    m_pObjectPool->addPrimitive(glassPrimitive);
}

void SceneBuilder::buildMirrorBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> mirrorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<Material> mirrorMaterial = std::make_shared<MaterialMirror>();
    std::shared_ptr<GeometryPrimitive> mirrorPrimitive = std::make_shared<GeometryPrimitive>(mirrorBall, mirrorMaterial);
    m_pObjectPool->addPrimitive(mirrorPrimitive);
}

void SceneBuilder::buildRedBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> redBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<Material> redMaterial = std::make_shared<MaterialLambertian>(Color::COLOR_RED);

    std::shared_ptr<GeometryPrimitive> redPrimitive = std::make_shared<GeometryPrimitive>(redBall, redMaterial);

    m_pObjectPool->addPrimitive(redPrimitive);
}

void SceneBuilder::buildAquaBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> aquaBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<Material> aquaMaterial = std::make_shared<MaterialLambertian>(Color::COLOR_AQUA);
    std::shared_ptr<GeometryPrimitive> aquaPrimitive = std::make_shared<GeometryPrimitive>(aquaBall, aquaMaterial);

    m_pObjectPool->addPrimitive(aquaPrimitive);
}

// void SceneBuilder::buildConductorBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> conductorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

// void SceneBuilder::buildMeasuredWhiteBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> measuredWhiteBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

// void SceneBuilder::buildMeasuredGreenBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> measuredGreenBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

// void SceneBuilder::buildMeasuredMetalBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> measuredMetalBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

// void SceneBuilder::buildMeasuredMintBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> measuredMintBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

void SceneBuilder::buildMeasuredGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPVC> material = std::make_shared<MaterialPVC>();
    std::shared_ptr<GeometryPrimitive> measuredGreenPvcPrimitive = std::make_shared<GeometryPrimitive>(measuredGreenPvcBall, material);

    m_pObjectPool->addPrimitive(measuredGreenPvcPrimitive);
}

// void SceneBuilder::buildMeasuredBrushedAluminiumBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> measuredBrushedAluminiumBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

void SceneBuilder::buildMeasuredTarkinTunicBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredTarkinTunicBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialTarkinTunic> material = std::make_shared<MaterialTarkinTunic>();
    std::shared_ptr<GeometryPrimitive> measuredTarkinTunicPrimitive = std::make_shared<GeometryPrimitive>(measuredTarkinTunicBall, material);

    m_pObjectPool->addPrimitive(measuredTarkinTunicPrimitive);
}

void SceneBuilder::buildMeasuredSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialSilk> material = std::make_shared<MaterialSilk>();
    std::shared_ptr<GeometryPrimitive> measuredSariSilkPrimitive = std::make_shared<GeometryPrimitive>(measuredSariSilkBall, material);

    m_pObjectPool->addPrimitive(measuredSariSilkPrimitive);
}

void SceneBuilder::buildNormalMapGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPVC> material = std::make_shared<MaterialPVC>();
    std::shared_ptr<NormalTexture> normalTexture = std::make_shared<NormalTexture>(ResourceDef::NORMAL);
    material->setNormalTexture(normalTexture);
    
    std::shared_ptr<GeometryPrimitive> normalMapGreenPvcPrimitive = std::make_shared<GeometryPrimitive>(normalMapGreenPvcBall, material);

    m_pObjectPool->addPrimitive(normalMapGreenPvcPrimitive);
}

void SceneBuilder::buildNormalMapSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialSilk> material = std::make_shared<MaterialSilk>();
    std::shared_ptr<NormalTexture> normalTexture = std::make_shared<NormalTexture>(ResourceDef::NORMAL);

    material->setNormalTexture(normalTexture);
    std::shared_ptr<GeometryPrimitive> normalMapSariSilkPrimitive = std::make_shared<GeometryPrimitive>(normalMapSariSilkBall, material);

    m_pObjectPool->addPrimitive(normalMapSariSilkPrimitive);
}

// void SceneBuilder::buildVolumeBall(const Vector3 &pos, float r)
// {
//     std::shared_ptr<Ball> volumeBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
// }

void SceneBuilder::buildModel(const Vector3 &pos,
                              float scale,
                              const std::string &path,
                              MATERIAL_TYPE materialType,
                              bool useNormalMap)
{
    std::shared_ptr<ImageTexture> albedoTexture = std::make_shared<ImageTexture>(ResourceDef::LENA);
    std::shared_ptr<Material> material = nullptr;

    if(materialType == MATERIAL_TYPE::M_RED)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_RED);
    }
    else if(materialType == MATERIAL_TYPE::M_YELLOW)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_YELLOW);
    }
    else if(materialType == MATERIAL_TYPE::M_GREEN)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_GREEN);
    }
    else if(materialType == MATERIAL_TYPE::M_BLUE)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_BLUE);
    }
    else if(materialType == MATERIAL_TYPE::M_AQUA)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_AQUA);
    }
    else if(materialType == MATERIAL_TYPE::M_WHITE)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_WHITE);
    }
    else if(materialType == MATERIAL_TYPE::M_PURPLE)
    {
        material = std::make_shared<MaterialLambertian>(Color::COLOR_PURPLE);
    }
    else if(materialType == MATERIAL_TYPE::M_LENA)
    {
        material = std::make_shared<MaterialLambertian>(albedoTexture);
    }
    else if(materialType == MATERIAL_TYPE::M_MEASURED_SARI_SILK_BRDF)
    {
        material = std::make_shared<MaterialSilk>();
    }
    else if(materialType == MATERIAL_TYPE::M_MEASURED_TARKIN_TUNIC_BRDF)
    {
        material = std::make_shared<MaterialTarkinTunic>();
    }
    else if(materialType == MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF)
    {
        material = std::make_shared<MaterialPVC>();
    }
    else if(materialType == MATERIAL_TYPE::M_GLASS)
    {
        material = std::make_shared<MaterialGlass>();
    }
    else if(materialType == MATERIAL_TYPE::M_MIRROR)
    {
        material = std::make_shared<MaterialMirror>();
    }
    else if(materialType == MATERIAL_TYPE::M_MICRO_FACET_SPECULAR)
    {
        material = std::make_shared<MaterialRough>();
    }
    // else if(materialType == MATERIAL_TYPE::M_MICRO_FACET_TRANSMISSION)
    // {
    //     material = std::make_shared<MaterialTRough>();
    // }
    else
    {
        assert(0);
    }

    if(useNormalMap)
    {
        std::shared_ptr<NormalTexture> normalTexture = std::make_shared<NormalTexture>(ResourceDef::NORMAL);
        material->setNormalTexture(normalTexture);
    }
    
    // std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(model, pos, scale);
    std::shared_ptr<Model> model = std::make_shared<Model>(path, pos, scale);
    for (auto mesh : model->getMeshes())
    {
        int materialId = mesh->getMaterialId();
        if (materialId != -1)
        {
            material = MaterialManager::getInstance().getMaterial(materialId);
        }

        mesh->addToPool(m_pObjectPool, material);
    }
}

void SceneBuilder::buildRedTri(const Vector3 &pos)
{
    Vector3 a(-30, -30, -20);
    Vector3 b(-30, 30, 0);
    Vector3 c(20, -20, -10);

    Vector3 na = (a - b).cross(a - c);
    Vector3 nb = (b - c).cross(b - a);
    Vector3 nc = (c - a).cross(c - b);

    TriVertex ta(a, na);
    TriVertex tb(b, nb);
    TriVertex tc(c, nc);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(ta, tb, tc, pos);
    std::shared_ptr<Material> material = std::make_shared<MaterialLambertian>(Color::COLOR_RED);
    std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(tri, material);

    m_pObjectPool->addPrimitive(primitive);
}

void SceneBuilder::buildGreenTri(const Vector3 &pos)
{
    Vector3 a(-30, -30, -20);
    Vector3 b(-30, 30, 0);
    Vector3 c(20, -20, -10);

    Vector3 na = (a - b).cross(a - c);
    Vector3 nb = (b - c).cross(b - a);
    Vector3 nc = (c - a).cross(c - b);

    TriVertex ta(a, na);
    TriVertex tb(b, nb);
    TriVertex tc(c, nc);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(ta, tb, tc, pos);
    std::shared_ptr<Material> material = std::make_shared<MaterialLambertian>(Color::COLOR_YELLOW); 
    std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(tri, material);

    m_pObjectPool->addPrimitive(primitive);
}

// void SceneBuilder::buildGlassTri(const Vector3 &pos)
// {
    // TriVertex a(-100, -100, -20);
    // TriVertex b(-80, 90, 0);
    // TriVertex c(40, -90, -10);
// }

// void SceneBuilder::buildRedCurve(const Vector3 &pos)
// {
    // Vector3 p0 = {-150, -50, 280};
    // Vector3 p1 = {-150, 50, 280};
    // Vector3 p2 = {150, -150, 280};
    // Vector3 p3 = {150, 150, 280};

    // std::shared_ptr<Curve> redCurve = std::make_shared<Curve>(p0, p1, p2, p3);

    // m_pObjectPool->add(redCurve);
// }
