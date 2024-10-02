#include "scene.h"
#include "lambertianMaterial.h"
#include "ray.h"
#include "objectpool.h"
#include "material.h"
#include "common.h"
#include <iostream>
#include "brdfMgr.h"
#include "material.h"
#include "ball.h"
#include "plane.h"
#include "hitrecord.h"
#include "light.h"
#include "transform.h"
#include <string>
#include "color.h"
#include "lambertianMaterial.h"
#include "glassMaterial.h"
#include "mirrorMaterial.h"
#include "chessboardTexture.h"
#include "imageTexture.h"
#include "constTexture.h"
#include "uvTexture.h"
#include "noiseTexture.h"
#include "triangle.h"
#include "mixMaterial.h"
#include "tri.h"
#include "mesh.h"

Scene::Scene()
{
    m_pObjectPool = new ObjectPool();
    m_pCamera = new PinholeCamera();
}

void Scene::run()
{
    preConstructScene();
    constructScene();

    preRender();
    render();
    postRender();
}

void Scene::preConstructScene()
{
    createMaterials();
}

void Scene::constructScene()
{
    buildRoom();
    buildLight();

    buildMirrorBall();
    buildRedBall();
    buildMixBall();
}

void Scene::preRender()
{
    m_pCamera->setPool(m_pObjectPool);
    m_pCamera->build(Vector3(0, 0, 0), Vector3(0, 0, 0));

    Transform t = m_pCamera->getTransform().getInverseTransform();
    m_pObjectPool->applyTransfrom(t);
}

void Scene::render()
{
    m_pCamera->render();
}

void Scene::postRender()
{
    m_pCamera->saveToImage("img");
    // m_pObjectPool->applyTransfrom(t.getInverseTransform());
}

void Scene::createMaterials()
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

void Scene::buildRoom()
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
    Plane *bottomPlane = new Plane(bottomRotate, bottomPosition, r, lambMtrlGreen);

    Vector3 frontRotate(Common::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    // CPlane *frontPlane = new CPlane(frontRotate, frontPosition, r, &MtrlMirror);
    Plane *frontPlane = new Plane(frontRotate, frontPosition, 100, lambMtrlRed);

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

void Scene::buildLight()
{
    Light *light = new Light(Vector3(0, 0, 300), 40);
    light->setTag(Common::TAG_LIGHT);

    m_pObjectPool->add(light);
}

void Scene::buildSceneWithDefaultConfig()
{
    Mesh *bunny = new Mesh(Common::LOW_BUNNY, lambMtrlAqua);

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

void Scene::buildMirrorBall()
{
    Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(25, 70, 350), 20, MtrlMirror);
    m_pObjectPool->add(mirrorBall);
}

void Scene::buildRedBall()
{
    Ball *redBall = new Ball(Vector3::ZERO, Vector3(70, 70, 350), 20, lambMtrlRed);
    m_pObjectPool->add(redBall);
}

void Scene::buildMixBall()
{
    Ball *mixBall = new Ball(Vector3::ZERO, Vector3(-28, 72, 350), 20, MtrlMix);
    m_pObjectPool->add(mixBall);
}
