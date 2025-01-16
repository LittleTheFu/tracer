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
    std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(leftRotate, leftPosition, r, MaterialManager::getInstance()->get(leftMtrl));

    Vector3 rightRotate(0, -MathConstant::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(rightRotate, rightPosition, r, MaterialManager::getInstance()->get(rightMtrl));

    Vector3 bottomRotate(MathConstant::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    std::shared_ptr<Plane> bottomPlane = std::make_shared<Plane>(bottomRotate, bottomPosition, r, MaterialManager::getInstance()->get(bottomMtrl));

    Vector3 topRotate(-MathConstant::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(topRotate, topPosition, r, MaterialManager::getInstance()->get(topMtrl));

    Vector3 frontRotate(MathConstant::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    std::shared_ptr<Plane> frontPlane = std::make_shared<Plane>(frontRotate, frontPosition, r, MaterialManager::getInstance()->get(frontMtrl));

    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(backRotate, backPosition, r, MaterialManager::getInstance()->get(backMtrl));

    m_pObjectPool->add(frontPlane);
    m_pObjectPool->add(backPlane);
    m_pObjectPool->add(topPlane);
    m_pObjectPool->add(bottomPlane);
    m_pObjectPool->add(leftPlane);
    m_pObjectPool->add(rightPlane);
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
    std::shared_ptr<Room> room = std::make_shared<Room>();
    m_pObjectPool->add(room->getTris());
}

void SceneBuilder::buildLight(const Vector3& pos, float r)
{
    std::shared_ptr<Light> light = std::make_shared<Light>(pos, r);
    light->setTag(Tag::TAG_LIGHT);

    m_pObjectPool->add(light);
}

void SceneBuilder::setLightIntensity(float intensity)
{
    if (!m_pObjectPool)
        return;

    if (!m_pObjectPool->m_pLight)
        return;

    m_pObjectPool->m_pLight->setIntensity(intensity);
}

void SceneBuilder::buildSceneWithDefaultConfig()
{
}

void SceneBuilder::buildGlassBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> glassBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));
    m_pObjectPool->add(glassBall);
}

void SceneBuilder::buildMirrorBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> mirrorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MIRROR));
    m_pObjectPool->add(mirrorBall);
}

void SceneBuilder::buildRedBall(const Vector3& pos, float r)
{
    std::shared_ptr<Ball> redBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(redBall);
}

void SceneBuilder::buildAquaBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> aquaBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_pObjectPool->add(aquaBall);
}

void SceneBuilder::buildConductorBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> conductorBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_CONDUCTOR));
    m_pObjectPool->add(conductorBall);
}

void SceneBuilder::buildMixBall(const Vector3& pos, float r)
{
    std::shared_ptr<Ball> mixBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_DIELECTRIC));
    m_pObjectPool->add(mixBall);
}

void SceneBuilder::buildMeasuredWhiteBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredWhiteBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_WHITE_BRDF));
    m_pObjectPool->add(measuredWhiteBall);
}

void SceneBuilder::buildMeasuredGreenBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredGreenBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_GREEN_BRDF));
    m_pObjectPool->add(measuredGreenBall);
}

void SceneBuilder::buildMeasuredMetalBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredMetalBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_METAL_BRDF));
    m_pObjectPool->add(measuredMetalBall);
}

void SceneBuilder::buildMeasuredMintBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredMintBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_MINT_BRDF));
    m_pObjectPool->add(measuredMintBall);
}

void SceneBuilder::buildMeasuredGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF));
    m_pObjectPool->add(measuredGreenPvcBall);
}

void SceneBuilder::buildMeasuredBrushedAluminiumBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredBrushedAluminiumBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_BRUSHED_ALUMINIUM_BRDF));
    m_pObjectPool->add(measuredBrushedAluminiumBall);
}

void SceneBuilder::buildMeasuredTarkinTunicBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredTarkinTunicBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_TARKIN_TUNIC_BRDF));
    m_pObjectPool->add(measuredTarkinTunicBall);
}

void SceneBuilder::buildMeasuredSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> measuredSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MEASURED_SARI_SILK_BRDF));
    m_pObjectPool->add(measuredSariSilkBall);
}

void SceneBuilder::buildNormalMapGreenPvcBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapGreenPvcBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_NORMAL_MAP_GREEN_PVC));
    m_pObjectPool->add(normalMapGreenPvcBall);
}

void SceneBuilder::buildNormalMapSariSilkBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> normalMapSariSilkBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_NORMAL_MAP_SARI_SILK));
    m_pObjectPool->add(normalMapSariSilkBall);
}

void SceneBuilder::buildVolumeBall(const Vector3 &pos, float r)
{
    std::shared_ptr<Ball> volumeBall = std::make_shared<Ball>(Vector3::ZERO, pos, r, nullptr);
    m_pObjectPool->add(volumeBall);
}

void SceneBuilder::buildBunny(const Vector3 &pos, float scale, const std::string &res, MATERIAL_TYPE materialType)
{
    std::shared_ptr<Mesh> bunny = std::make_shared<Mesh>(res, pos, scale, MaterialManager::getInstance()->get(materialType));
    bunny->addToPool(m_pObjectPool);
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

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(ta, tb, tc, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(tri);
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

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(ta, tb, tc, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GREEN));
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildGlassTri(const Vector3 &pos)
{
    TriVertex a(-100, -100, -20);
    TriVertex b(-80, 90, 0);
    TriVertex c(40, -90, -10);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildRedCurve(const Vector3 &pos)
{
    std::shared_ptr<Curve> redCurve = std::make_shared<Curve>(pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(redCurve);
}
