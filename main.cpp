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
#include "camera.h"
#include "transform.h"
#include <string>

int main()
{
    BrdfMgr brdfMgr;

    Material lambMtrlRed;
    lambMtrlRed.pBrdf = brdfMgr.getRedBrdf();

    Material lambMtrlYellow;
    lambMtrlYellow.pBrdf = brdfMgr.getYellowBrdf();

    Material lambMtrlAqua;
    lambMtrlAqua.pBrdf = brdfMgr.getAquaBrdf();

    Material lambMtrlPurple;
    lambMtrlPurple.pBrdf = brdfMgr.getPurpleBrdf();

    Material lambMtrlGreen;
    lambMtrlGreen.pBrdf = brdfMgr.getGreenBrdf();

    Material lambMtrlBlue;
    lambMtrlBlue.pBrdf = brdfMgr.getBlueBrdf();

    Material lambMtrlWhite;
    lambMtrlWhite.pBrdf = brdfMgr.getWhiteBrdf();

    Material MtrlMirror;
    MtrlMirror.pBrdf = brdfMgr.getMirrorBrdf();

    Material MtrlGlass;
    MtrlGlass.pBrdf = brdfMgr.getGlassBrdf();

    Ball *redBall = new Ball(Vector3::ZERO, Vector3(-75, 10, 300), 20, &lambMtrlRed);
    Ball *yellowBall = new Ball(Vector3::ZERO, Vector3(60, 80, 200), 20, &lambMtrlYellow);
    Ball *aquaBall = new Ball(Vector3::ZERO, Vector3(-50, -50, 300), 20, &lambMtrlAqua);
    Ball *whiteBall = new Ball(Vector3::ZERO, Vector3(20, -20, 300), 20, &lambMtrlWhite);
    Ball *glassBall = new Ball(Vector3::ZERO, Vector3(0, 0, 225), 20, &MtrlGlass);
    Ball *mirrorBall = new Ball(Vector3::ZERO, Vector3(-25, 40, 225), 20, &MtrlMirror);

    Light *light = new Light(Vector3(0, -80, 250));

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
    Plane *frontPlane = new Plane(frontRotate, frontPosition, r, &lambMtrlAqua);

    // Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    Plane *backPlane = new Plane(backRotate, backPosition, r, &lambMtrlRed);

    Vector3 glassRotate(-Common::PI / 2, 0, 0);
    Vector3 glassPosition(0, 0, -c * 0.5);
    Plane *glassPlane = new Plane(glassRotate, glassPosition, r, &MtrlGlass);

    ObjectPool *pool = new ObjectPool();

    frontPlane->setTag(0);
    backPlane->setTag(1);
    topPlane->setTag(2);
    bottomPlane->setTag(3);
    leftPlane->setTag(4);
    rightPlane->setTag(5);

    glassBall->setTag(100);
    glassPlane->setTag(101);

    mirrorBall->setTag(200);

    pool->add(light);

    pool->add(redBall);
    pool->add(yellowBall);
    pool->add(aquaBall);
    pool->add(whiteBall);

    pool->add(glassBall);
    pool->add(mirrorBall);

    pool->add(frontPlane);
    pool->add(backPlane);
    pool->add(topPlane);
    pool->add(bottomPlane);
    pool->add(leftPlane);
    pool->add(rightPlane);

    Camera camera(pool);
    camera.build(Vector3::ZERO, Vector3::ZERO);
    Transform t = camera.getTransform().getInverseTransform();
    pool->applyTransfrom(t);
    camera.render();
    camera.saveToImage("img");
    pool->applyTransfrom(t.getInverseTransform());

    // for (int i = 0; i < 20; i++)
    // {
    //     Camera camera(pool);
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