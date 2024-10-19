#include "sceneBuilder.h"
#include "plane.h"
#include "common.h"
#include "mesh.h"
#include "ball.h"
#include "materialManager.h"

void SceneBuilder::init(ObjectPool *pool)
{
     m_pObjectPool = pool;
}

void SceneBuilder::buildRoom()
{
    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, Common::PI / 2, 0);
    Vector3 leftPosition(-c, 0, 0);
    // CPlane *leftPlane = new CPlane(leftRotate, leftPosition, r, &MtrlMirror);
    Plane *leftPlane = new Plane(leftRotate, leftPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    Vector3 rightRotate(0, -Common::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    Plane *rightPlane = new Plane(rightRotate, rightPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));

    Vector3 topRotate(-Common::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    Plane *topPlane = new Plane(topRotate, topPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));

    Vector3 bottomRotate(Common::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    Plane *bottomPlane = new Plane(bottomRotate, bottomPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));

    Vector3 frontRotate(Common::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    // CPlane *frontPlane = new CPlane(frontRotate, frontPosition, r, &MtrlMirror);
    Plane *frontPlane = new Plane(frontRotate, frontPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));

    // Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    Plane *backPlane = new Plane(backRotate, backPosition, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    // frontPlane->setTag(Common::TAG_PLANE_FRONT);
    // backPlane->setTag(Common::TAG_PLANE_BACK);
    // topPlane->setTag(Common::TAG_PLANE_TOP);
    // bottomPlane->setTag(Common::TAG_PLANE_BOTTOM);
    // leftPlane->setTag(Common::TAG_PLANE_LEFT);
    // rightPlane->setTag(Common::TAG_PLANE_RIGHT);

    m_pObjectPool->add(frontPlane);
    m_pObjectPool->add(backPlane);
    m_pObjectPool->add(topPlane);
    m_pObjectPool->add(bottomPlane);
    m_pObjectPool->add(leftPlane);
    m_pObjectPool->add(rightPlane);
}

void SceneBuilder::buildLight(const Vector3& pos, float r)
{
    // Light *light = new Light(Vector3(0, 0, 300), 50);
    Light *light = new Light(pos, r);
    light->setTag(Common::TAG_LIGHT);

    m_pObjectPool->add(light);
}

void SceneBuilder::buildSceneWithDefaultConfig()
{
}

void SceneBuilder::buildGlassBall(const Vector3 &pos, float r)
{
    // Ball *redBall = new Ball(Vector3::ZERO, Vector3(70, 70, 350), 20, lambMtrlRed);
    Ball *glassBall = new Ball(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));
    m_pObjectPool->add(glassBall);
}
void SceneBuilder::buildMirrorBall(const Vector3 &pos, float r)
{
    // Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(25, 70, 350), 20, MtrlMirror);
    Ball *mirrorBall = new Ball(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_MIRROR));
    m_pObjectPool->add(mirrorBall);
}

void SceneBuilder::buildRedBall(const Vector3& pos, float r)
{
    // Ball *redBall = new Ball(Vector3::ZERO, Vector3(70, 70, 350), 20, lambMtrlRed);
    Ball *redBall = new Ball(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(redBall);
}

void SceneBuilder::buildAquaBall(const Vector3 &pos, float r)
{
    Ball *aquaBall = new Ball(Vector3::ZERO, pos, r, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_pObjectPool->add(aquaBall);
}

void SceneBuilder::buildMixBall(const Vector3& pos, float r)
{
    // Ball *mixBall = new Ball(Vector3::ZERO, Vector3(-28, 72, 350), 20, MtrlMix);
    // Ball *mixBall = new Ball(Vector3::ZERO, pos, r, MtrlMix);
    // m_pObjectPool->add(mixBall);
}

void SceneBuilder::buildBunny(const Vector3& pos, float scale)
{
    // Vector3 pos(60, 60, 350);
    // float scale = 300;

    Mesh *bunny = new Mesh(Common::LOW_LOW_BUNNY, pos, scale, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    bunny->addToPool(m_pObjectPool);
}

void SceneBuilder::buildRedTri(const Vector3 &pos)
{
    TriVertex a(-30, -30, -20);
    TriVertex b(-30, 30, 0);
    TriVertex c(10, -20, -10);

    Tri *tri = new Tri(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildGreenTri(const Vector3 &pos)
{
    TriVertex a(-150, 10, 30);
    TriVertex c(40, 0, 10);
    TriVertex b(-170, 40, 50);

    Tri *tri = new Tri(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GREEN));
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildGlassTri(const Vector3 &pos)
{
    TriVertex a(-100, -100, -20);
    TriVertex b(-80, 90, 0);
    TriVertex c(40, -90, -10);

    Tri *tri = new Tri(a, b, c, pos, MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));
    m_pObjectPool->add(tri);
}
