#include "sceneBuilder.h"
#include "plane.h"
#include "mathConstantDef.h"
#include "mesh.h"
#include "resourceDef.h"
#include "ball.h"
#include "materialManager.h"
#include "room.h"
#include "tagDef.h"
#include <memory>

void SceneBuilder::init(std::shared_ptr<ObjectPool> pool)
{
    m_pObjectPool = pool;
}

void SceneBuilder::buildRoom()
{
    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, MathConstant::PI / 2, 0);
    Vector3 leftPosition(-c, 0, 0);
    std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(leftRotate, leftPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    Vector3 rightRotate(0, -MathConstant::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(rightRotate, rightPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));

    Vector3 topRotate(-MathConstant::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(topRotate, topPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_CHESSBOARD));

    Vector3 bottomRotate(MathConstant::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    std::shared_ptr<Plane> bottomPlane = std::make_shared<Plane>(bottomRotate, bottomPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_CHESSBOARD));

    Vector3 frontRotate(MathConstant::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    std::shared_ptr<Plane> frontPlane = std::make_shared<Plane>(frontRotate, frontPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));

    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(backRotate, backPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    m_pObjectPool->add(frontPlane);
    m_pObjectPool->add(backPlane);
    m_pObjectPool->add(topPlane);
    m_pObjectPool->add(bottomPlane);
    m_pObjectPool->add(leftPlane);
    m_pObjectPool->add(rightPlane);
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
    TriVertex a(-30, -30, -20);
    TriVertex b(-30, 30, 0);
    TriVertex c(20, -20, -10);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildGreenTri(const Vector3 &pos)
{
    TriVertex a(-150, 10, 30);
    TriVertex c(40, 0, 10);
    TriVertex b(-170, 40, 50);

    std::shared_ptr<Tri> tri = std::make_shared<Tri>(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GREEN));
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