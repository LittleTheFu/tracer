#include "ray.h"
#include "objectpool.h"
#include "material.h"
#include "common/common.h"
#include <iostream>
#include "brdfMgr.h"
#include "material.h"
#include "ball.h"
#include "plane.h"
#include "hitrecord.h"
#include "light.h"
#include "pinholeCamera.h"
#include "orthographicCamera.h"
#include "fishEyeCamera.h"
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

int main()
{
    float rho = 1;

    LambertianMaterial lambMtrlLena(new ImageTexture(Common::LENA), rho);
    LambertianMaterial lambMtrlChessboard(new ChessboardTexture(), rho);
    LambertianMaterial lambUV(new UvTexture(), 1);
    LambertianMaterial lambNoise(new NoiseTexture(Color::COLOR_WHITE), rho);

    LambertianMaterial lambMtrlRed(new ConstTexture(Color::COLOR_RED), rho);
    LambertianMaterial lambMtrlYellow(new ConstTexture(Color::COLOR_YELLOW), rho);
    LambertianMaterial lambMtrlAqua(new ConstTexture(Color::COLOR_AQUA), rho);
    LambertianMaterial lambMtrlPurple(new ConstTexture(Color::COLOR_PURPLE), rho);
    LambertianMaterial lambMtrlGreen(new ConstTexture(Color::COLOR_GREEN), rho);
    LambertianMaterial lambMtrlBlue(new ConstTexture(Color::COLOR_BLUE), rho);
    LambertianMaterial lambMtrlWhite(new ConstTexture(Color::COLOR_WHITE), rho);

    MirrorMaterial MtrlMirror;
    GlassMaterial MtrlGlass;

    MixMaterial MtrlMix;

    TriAngleVertex va = TriAngleVertex(-20, 20, 0, 0);
    TriAngleVertex vb = TriAngleVertex(0, -20, 0.5, 1);
    TriAngleVertex vc = TriAngleVertex(20, 20, 1, 0);
    TriAngle *triAngle = new TriAngle(va, vb, vc,
                                      Vector3(0, -Common::PI / 4, 0), Vector3(-80, -50, 215),
                                      &lambMtrlLena);

    Ball *redBall = new Ball(Vector3::ZERO, Vector3(-55, 10, 240), 20, &lambMtrlRed);
    Ball *yellowBall = new Ball(Vector3::ZERO, Vector3(60, 80, 225), 20, &lambMtrlYellow);
    Ball *aquaBall = new Ball(Vector3::ZERO, Vector3(-50, -50, 300), 20, &lambMtrlAqua);
    Ball *whiteBall = new Ball(Vector3::ZERO, Vector3(20, -20, 300), 20, &lambMtrlWhite);
    Ball *glassBall = new Ball(Vector3::ZERO, Vector3(2, -2, 225), 20, &MtrlGlass);
    Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(25, 40, 225), 20, &MtrlMirror);
    Ball *textureBall = new Ball(Vector3::ZERO, Vector3(-45, 40, 220), 20, &lambMtrlChessboard);
    Ball *mixBall = new Ball(Vector3::ZERO, Vector3(0, 0, 220), 20, &MtrlMix);

    Light *light = new Light(Vector3(0, -80, 230));

    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, Common::PI / 2, 0);
    Vector3 leftPosition(-c, 0, 0);
    // CPlane *leftPlane = new CPlane(leftRotate, leftPosition, r, &MtrlMirror);
    Plane *leftPlane = new Plane(leftRotate, leftPosition, r, &lambMtrlYellow);

    Vector3 rightRotate(0, -Common::PI / 2, 0);
    Vector3 rightPosition(c, 0, 0);
    Plane *rightPlane = new Plane(rightRotate, rightPosition, r, &lambMtrlBlue);

    Vector3 topRotate(-Common::PI / 2, 0, 0);
    Vector3 topPosition(0, -c, 0);
    Plane *topPlane = new Plane(topRotate, topPosition, r, &lambMtrlPurple);

    Vector3 bottomRotate(Common::PI / 2, 0, 0);
    Vector3 bottomPosition(0, c, 0);
    Plane *bottomPlane = new Plane(bottomRotate, bottomPosition, r, &lambMtrlGreen);

    Vector3 frontRotate(Common::PI, 0, 0);
    Vector3 frontPosition(0, 0, 5 * c);
    // CPlane *frontPlane = new CPlane(frontRotate, frontPosition, r, &MtrlMirror);
    Plane *frontPlane = new Plane(frontRotate, frontPosition, 100, &lambMtrlRed);

    // Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    Plane *backPlane = new Plane(backRotate, backPosition, 100, &lambMtrlRed);

    Vector3 glassRotate(-Common::PI / 2, 0, 0);
    Vector3 glassPosition(0, 0, -c * 0.5);
    Plane *glassPlane = new Plane(glassRotate, glassPosition, r, &MtrlGlass);

    Vector3 squareRotate(Common::PI, -Common::PI / 4, Common::PI);
    Vector3 squarePosition(70, -25, 290);
    Plane *squarePlane = new Plane(squareRotate, squarePosition, 20, &lambMtrlLena);

    ObjectPool *pool = new ObjectPool();

    frontPlane->setTag(Common::TAG_PLANE_FRONT);
    backPlane->setTag(Common::TAG_PLANE_BACK);
    topPlane->setTag(Common::TAG_PLANE_TOP);
    bottomPlane->setTag(Common::TAG_PLANE_BOTTOM);
    leftPlane->setTag(Common::TAG_PLANE_LEFT);
    rightPlane->setTag(Common::TAG_PLANE_RIGHT);

    light->setTag(Common::TAG_LIGHT);

    // glassBall->setTag(100);
    // glassPlane->setTag(101);

    // mirrorBall->setTag(200);

    pool->add(light);

    // pool->add(triAngle);

    // pool->add(redBall);
    // pool->add(yellowBall);
    // pool->add(aquaBall);
    pool->add(whiteBall);

    // pool->add(glassBall);
    // pool->add(mirrorBall);
    // pool->add(mixBall);

    // pool->add(textureBall);

    pool->add(frontPlane);
    pool->add(backPlane);
    pool->add(topPlane);
    pool->add(bottomPlane);
    pool->add(leftPlane);
    pool->add(rightPlane);

    // pool->add(squarePlane);

    // FishEyeCamera camera(pool);
    // OrthographicCamera camera(pool);
    PinholeCamera camera(pool);
    camera.build(Vector3(0, 0, 0), Vector3(0, 0, 0));
    Transform t = camera.getTransform().getInverseTransform();
    pool->applyTransfrom(t);
    camera.render();
    camera.saveToImage("img");
    pool->applyTransfrom(t.getInverseTransform());

    // for (int i = 7; i < 8; i++)
    // {
    //     FishEyeCamera camera(pool);
    //     std::string name = "b_img" + std::to_string(i);
    //     camera.build(Vector3(0, 0, -200 + i * 30), Vector3(0, 0, Common::PI / 10 * i));
    //     Transform t = camera.getTransform().getInverseTransform();
    //     pool->applyTransfrom(t);
    //     camera.render();
    //     camera.saveToImage(name);
    //     pool->applyTransfrom(t.getInverseTransform());
    // }

    return 0;
}