#include "sceneBuilder.h"
#include "plane.h"
#include "common.h"
#include "mesh.h"
#include "triangle.h"
#include "ball.h"
#include "imageTexture.h"
#include "lambertianMaterial.h"
#include "chessboardTexture.h"
#include "uvTexture.h"
#include "noiseTexture.h"
#include "constTexture.h"

void SceneBuilder::init(ObjectPool *pool)
{
     m_pObjectPool = pool;

     createMaterials();
}

void SceneBuilder::createMaterials()
{
    rho = 0.4f;

    lambMtrlLena = new LambertianMaterial(new ImageTexture(Common::LENA), rho);
    lambMtrlChessboard = new LambertianMaterial(new ChessboardTexture(), rho);
    lambUV = new LambertianMaterial(new UvTexture(), 1);
    lambNoise = new LambertianMaterial(new NoiseTexture(Color::COLOR_WHITE), rho);

    lambMtrlRed = new LambertianMaterial(new ConstTexture(Color::COLOR_RED), rho);
    lambMtrlYellow = new LambertianMaterial(new ConstTexture(Color::COLOR_YELLOW), rho);
    lambMtrlAqua = new LambertianMaterial(new ConstTexture(Color::COLOR_AQUA), rho);
    lambMtrlPurple = new LambertianMaterial(new ConstTexture(Color::COLOR_PURPLE), rho);
    lambMtrlGreen = new LambertianMaterial(new ConstTexture(Color::COLOR_GREEN), rho);
    lambMtrlBlue = new LambertianMaterial(new ConstTexture(Color::COLOR_BLUE), rho);
    lambMtrlWhite = new LambertianMaterial(new ConstTexture(Color::COLOR_WHITE), rho);

    MtrlMirror = new MirrorMaterial();
    MtrlGlass = new GlassMaterial();

    MtrlMix = new MixMaterial();
}

void SceneBuilder::buildRoom()
{
    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, Common::PI / 2, 0);
    Vector3 leftPosition(-c, 0, 0);
    // CPlane *leftPlane = new CPlane(leftRotate, leftPosition, r, &MtrlMirror);
    Plane *leftPlane = new Plane(leftRotate, leftPosition, r, lambMtrlYellow);

    Vector3 rightRotate(0, -Common::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    Plane *rightPlane = new Plane(rightRotate, rightPosition, r, lambMtrlBlue);

    Vector3 topRotate(-Common::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    Plane *topPlane = new Plane(topRotate, topPosition, r, lambMtrlPurple);

    Vector3 bottomRotate(Common::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    Plane *bottomPlane = new Plane(bottomRotate, bottomPosition, r, lambMtrlYellow);

    Vector3 frontRotate(Common::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    // CPlane *frontPlane = new CPlane(frontRotate, frontPosition, r, &MtrlMirror);
    Plane *frontPlane = new Plane(frontRotate, frontPosition, 100, lambMtrlGreen);

    // Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    Plane *backPlane = new Plane(backRotate, backPosition, 100, lambMtrlRed);

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
    Mesh *bunny = new Mesh(Common::LOW_BUNNY, Vector3::ZERO, 300, lambMtrlAqua);

    TriVertex v_a(0, 0, 50);
    TriVertex v_b(50, 0, 0);
    TriVertex v_c(0, 50, 0);
    Tri *tri = new Tri(v_a, v_b, v_c, Vector3(30, 30, 300), lambMtrlGreen);

    TriAngleVertex va = TriAngleVertex(-20, 20, 0, 0);
    TriAngleVertex vb = TriAngleVertex(0, -20, 0.5, 1);
    TriAngleVertex vc = TriAngleVertex(20, 20, 1, 0);
    TriAngle *triAngle = new TriAngle(va, vb, vc,
                                      Vector3(0, -Common::PI / 4, 0), Vector3(-50, 50, 300),
                                      lambMtrlLena);

    Ball *redBall = new Ball(Vector3::ZERO, Vector3(-55, 10, 240), 20, lambMtrlRed);
    Ball *yellowBall = new Ball(Vector3::ZERO, Vector3(60, 80, 225), 20, lambMtrlYellow);
    Ball *aquaBall = new Ball(Vector3::ZERO, Vector3(-50, 70, 370), 20, lambMtrlAqua);
    Ball *whiteBall = new Ball(Vector3::ZERO, Vector3(20, -20, 250), 20, lambMtrlWhite);
    Ball *glassBall = new Ball(Vector3::ZERO, Vector3(75, 72, 300), 20, MtrlGlass);
    // Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(25, 40, 225), 20, MtrlMirror);
    Ball *textureBall = new Ball(Vector3::ZERO, Vector3(-45, 40, 220), 20, lambMtrlChessboard);

    Vector3 squareRotate(Common::PI, -Common::PI / 4, Common::PI);
    Vector3 squarePosition(70, -25, 290);
    Plane *squarePlane = new Plane(squareRotate, squarePosition, 20, lambMtrlLena);

    glassBall->setTag(Common::TAG_GLASS_BALL);
    // glassPlane->setTag(101);

    // mirrorBall->setTag(200);

    // m_pObjectPool->add(aquaBall);
    // m_pObjectPool->add(tri);

    // m_pObjectPool->add(triAngle);

    // pool->add(redBall);
    // pool->add(yellowBall);
    // m_pObjectPool->add(aquaBall);

    // m_pObjectPool->add(whiteBall);

    m_pObjectPool->add(glassBall);
    // pool->add(mirrorBall);
    // m_pObjectPool->add(mixBall);

    // pool->add(textureBall);
    // bunny->addToPool(m_pObjectPool);
}

void SceneBuilder::buildMirrorBall(const Vector3& pos, float r)
{
    // Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(25, 70, 350), 20, MtrlMirror);
    Ball *mirrorBall = new Ball(Vector3::ZERO, pos, r, MtrlMirror);
    m_pObjectPool->add(mirrorBall);
}

void SceneBuilder::buildRedBall(const Vector3& pos, float r)
{
    // Ball *redBall = new Ball(Vector3::ZERO, Vector3(70, 70, 350), 20, lambMtrlRed);
    Ball *redBall = new Ball(Vector3::ZERO, pos, r, lambMtrlRed);
    m_pObjectPool->add(redBall);
}

void SceneBuilder::buildMixBall(const Vector3& pos, float r)
{
    // Ball *mixBall = new Ball(Vector3::ZERO, Vector3(-28, 72, 350), 20, MtrlMix);
    Ball *mixBall = new Ball(Vector3::ZERO, pos, r, MtrlMix);
    m_pObjectPool->add(mixBall);
}

void SceneBuilder::buildBunny(const Vector3& pos, float scale)
{
    // Vector3 pos(60, 60, 350);
    // float scale = 300;

    Mesh *bunny = new Mesh(Common::LOW_LOW_BUNNY, pos, scale, MtrlMirror);
    bunny->addToPool(m_pObjectPool);
}

void SceneBuilder::buildRedTri(const Vector3 &pos)
{
    TriVertex a(-40, -10, 0, 0, 0, -1);
    TriVertex b(20, 40, 30, 0, 0, -1);
    TriVertex c(40, -10, 0, 0, 0, -1);

    Tri *tri = new Tri(a, b, c, pos, lambMtrlRed);
    m_pObjectPool->add(tri);
}

void SceneBuilder::buildGreenTri(const Vector3 &pos)
{
    TriVertex a(0, 10, 0, 0, 0, 1);
    TriVertex c(40, 0, 10, 0, 0, 1);
    TriVertex b(0, 40, 0, 0, 0, 1);

    Tri *tri = new Tri(a, b, c, pos, lambMtrlGreen);
    m_pObjectPool->add(tri);
}

