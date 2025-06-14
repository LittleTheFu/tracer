#include <memory>

#include "ball.h"
#include "curve.h"
#include "mathConstantDef.h"
#include "materialManager.h"
#include "mesh.h"
#include "plane.h"
#include "resourceDef.h"
#include "room.h"
#include "sceneBuilder.h"
#include "tagDef.h"
#include "materialLambertian.h"
#include "geometryPrimitive.h"
#include <areaLight.h>
#include <emittingMaterial.h>
#include <materialPVC.h>
#include <materialMirror.h>

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
    std::shared_ptr<MaterialPlus> leftMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_RED);

    Vector3 rightRotate(0, -MathConstant::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(rightRotate, rightPosition, r);
    std::shared_ptr<MaterialPlus> rightMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_BLUE);


    Vector3 bottomRotate(MathConstant::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    std::shared_ptr<Plane> bottomPlane = std::make_shared<Plane>(bottomRotate, bottomPosition, r);
    std::shared_ptr<MaterialPlus> bottomMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_GREEN);
    

    Vector3 topRotate(-MathConstant::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(topRotate, topPosition, r);
    std::shared_ptr<MaterialPlus> topMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_YELLOW);

    Vector3 frontRotate(MathConstant::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    std::shared_ptr<Plane> frontPlane = std::make_shared<Plane>(frontRotate, frontPosition, r);
    std::shared_ptr<MaterialPlus> frontMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_AQUA);

    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(backRotate, backPosition, r);
    std::shared_ptr<MaterialPlus> backMtrlLambertian = std::make_shared<MaterialLambertian>(Color::COLOR_ORANGE);

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
    std::shared_ptr<Geometry> ball = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPlus> lightMaterial = std::make_shared<EmittingMaterial>();
    std::shared_ptr<GeometryPrimitive> lightPrimitive = std::make_shared<GeometryPrimitive>(ball, lightMaterial);
    std::shared_ptr<AreaLight> areaLight = std::make_shared<AreaLight>(lightPrimitive);

    m_pObjectPool->setLight(areaLight);
    m_pObjectPool->addPrimitive(lightPrimitive);
}

void SceneBuilder::setLightIntensity(float intensity)
{
    if (!m_pObjectPool)
        return;

    if (!m_pObjectPool->light_)
        return;

    m_pObjectPool->light_->setIntensity(intensity);
}

void SceneBuilder::buildSceneWithDefaultConfig()
{
}

void SceneBuilder::buildGlassBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> glassBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(glassBall);
}

void SceneBuilder::buildMirrorBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> mirrorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPlus> mirrorMaterial = std::make_shared<MaterialMirror>();
    std::shared_ptr<GeometryPrimitive> mirrorPrimitive = std::make_shared<GeometryPrimitive>(mirrorBall, mirrorMaterial);
    m_pObjectPool->addPrimitive(mirrorPrimitive);

    // m_pObjectPool->add(mirrorBall);
}

void SceneBuilder::buildRedBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> redBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPlus> redMaterial = std::make_shared<MaterialLambertian>(Color::COLOR_RED);

    std::shared_ptr<GeometryPrimitive> redPrimitive = std::make_shared<GeometryPrimitive>(redBall, redMaterial);

    m_pObjectPool->addPrimitive(redPrimitive);
}

void SceneBuilder::buildAquaBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> aquaBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPlus> aquaMaterial = std::make_shared<MaterialLambertian>(Color::COLOR_AQUA);
    std::shared_ptr<GeometryPrimitive> aquaPrimitive = std::make_shared<GeometryPrimitive>(aquaBall, aquaMaterial);

    m_pObjectPool->addPrimitive(aquaPrimitive);
}

void SceneBuilder::buildConductorBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> conductorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(conductorBall);
}

void SceneBuilder::buildMixBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> mixBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(mixBall);
}

void SceneBuilder::buildMeasuredWhiteBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredWhiteBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredWhiteBall);
}

void SceneBuilder::buildMeasuredGreenBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredGreenBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredGreenBall);
}

void SceneBuilder::buildMeasuredMetalBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredMetalBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredMetalBall);
}

void SceneBuilder::buildMeasuredMintBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredMintBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredMintBall);
}

void SceneBuilder::buildMeasuredGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);
    std::shared_ptr<MaterialPVC> material = std::make_shared<MaterialPVC>();
    // std::shared_ptr<MaterialMirror> material = std::make_shared<MaterialMirror>();

    std::shared_ptr<GeometryPrimitive> measuredGreenPvcPrimitive = std::make_shared<GeometryPrimitive>(measuredGreenPvcBall, material);

    m_pObjectPool->addPrimitive(measuredGreenPvcPrimitive);
}

void SceneBuilder::buildMeasuredBrushedAluminiumBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredBrushedAluminiumBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredBrushedAluminiumBall);
}

void SceneBuilder::buildMeasuredTarkinTunicBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredTarkinTunicBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredTarkinTunicBall);
}

void SceneBuilder::buildMeasuredSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(measuredSariSilkBall);
}

void SceneBuilder::buildNormalMapGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(normalMapGreenPvcBall);
}

void SceneBuilder::buildNormalMapSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(normalMapSariSilkBall);
}

void SceneBuilder::buildVolumeBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> volumeBall = std::make_shared<Ball>(Vector3::ZERO, pos, r);

    // m_pObjectPool->add(volumeBall);
}

void SceneBuilder::buildBunny(const Vector3 &pos, float scale, const std::string &res, MATERIAL_TYPE materialType)
{
    // std::shared_ptr<MaterialLambertian> material = std::make_shared<MaterialLambertian>(Color::COLOR_GREEN);
    std::shared_ptr<MaterialPlus> material = std::make_shared<MaterialMirror>(); 
    std::shared_ptr<Mesh> bunny = std::make_shared<Mesh>(res, pos, scale);
    bunny->addToPool(m_pObjectPool, material);
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

    // m_pObjectPool->add(tri);
}

void SceneBuilder::buildGreenTri(const Vector3 &pos)
{
    Vector3 a(-150, 10, 30);
    Vector3 b(-170, 40, 50);
    Vector3 c(40, 0, 10);

    Vector3 na = (a - b).cross(a - c);
    Vector3 nb = (b - c).cross(b - a);
    Vector3 nc = (c - a).cross(c - b);

    TriVertex ta(a, na);
    TriVertex tb(b, nb);
    TriVertex tc(c, nc);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(ta, tb, tc, pos);

    // m_pObjectPool->add(tri);
}

void SceneBuilder::buildGlassTri(const Vector3 &pos)
{
    // TriVertex a(-100, -100, -20);
    // TriVertex b(-80, 90, 0);
    // TriVertex c(40, -90, -10);

    // std::shared_ptr<Tri> tri = std::make_shared<Tri>(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));

    // m_pObjectPool->add(tri);
}

void SceneBuilder::buildRedCurve(const Vector3 &pos)
{
    // Vector3 p0 = {-150, -50, 280};
    // Vector3 p1 = {-150, 50, 280};
    // Vector3 p2 = {150, -150, 280};
    // Vector3 p3 = {150, 150, 280};

    // std::shared_ptr<Curve> redCurve = std::make_shared<Curve>(p0, p1, p2, p3);

    // m_pObjectPool->add(redCurve);
}
