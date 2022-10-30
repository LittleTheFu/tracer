#include "lodepng.h"

#include "ray.h"
#include "ball.h"
#include "plane.h"
#include "objectpool.h"
#include "material.h"
#include "hitinfo.h"
#include "common.h"
#include <iostream>
#include "brdfMgr.h"
#include "rmaterial.h"
#include "cball.h"
#include "cplane.h"
#include "hitrecord.h"
using namespace std;

int main()
{
    BrdfMgr brdfMgr;
    Rmaterial lambMtrl;
    lambMtrl.pBrdf = brdfMgr.getBrdf();

    CBall myBall(Vector3::ZERO, Vector3(0, 0, 20), 5, lambMtrl);

    const Vector3 centerOne(-30, 20, 70);
    Ball ballOne(centerOne, 3);
    ballOne.setMaterial(Material::MTRL_AQUA * Material::rho);

    const Vector3 centerTwo(5, 0, 30);
    Ball ballTwo(centerTwo, 3);
    ballTwo.setMaterial(Material::MTRL_RED * Material::rho);
    ballTwo.mtrl.specular = true;

    const Vector3 centerThree(1, 1, 70);
    Ball ballThree(centerThree, 3);
    ballThree.setMaterial(Material::MTRL_AQUA * Material::rho);
    ballThree.mtrl.specular = false;

    const Vector3 centerFour(-5, -30, 90);
    Ball ballFour(centerFour, 3);
    ballFour.setMaterial(Material::MTRL_PURPLE * Material::rho);
    ballFour.mtrl.specular = false;

    const Vector3 centerFive(0, 5, 20);
    Ball ballFive(centerFive, 3);
    ballFive.setMaterial(Material::MTRL_WHITE * Material::rho);
    ballFive.mtrl.specular = false;

    const Vector3 centerSix(-5, -20, 80);
    Ball ballSix(centerSix, 3);
    ballSix.setMaterial(Material::MTRL_RED * Material::rho);
    ballSix.mtrl.specular = true;

    const Vector3 centerSeven(13, -8, 50);
    Ball ballSeven(centerSeven, 3);
    ballSeven.setMaterial(Material::MTRL_BLUE * Material::rho);
    ballSeven.mtrl.specular = false;

    const Vector3 centerEight(-3, 0, 30);
    Ball ballEight(centerEight, 3);
    ballEight.setMaterial(Material::MTRL_RED * Material::rho);
    ballEight.mtrl.specular = true;

    const float c = 100;
    const float r = 5 * c;
    const Vector3 wallLeftCenter(-c, 0, 0);
    const Vector3 wallNormalLeft(1, 0, 0);
    Plane wallLeft(wallLeftCenter, wallNormalLeft, r);
    wallLeft.setMaterial(Material::MTRL_BLUE);
    wallLeft.transform.rotateY(-Common::PI / 2);
    wallLeft.transform.translate(0, 0, -c);
    // wallLeft.transform.setOrigin(wallLeft.center.x, wallLeft.center.y, wallLeft.center.z);

    const Vector3 wallRightCenter(c, 0, 0);
    const Vector3 wallNormalRight(-1, 0, 0);
    Plane wallRight(wallRightCenter, wallNormalRight, r);
    wallRight.setMaterial(Material::MTRL_BLUE);
    wallRight.transform.rotateY(Common::PI / 2);
    wallRight.transform.translate(0, 0, -c);

    const Vector3 wallTopCenter(0, c, 0);
    const Vector3 wallNormalTop(0, -1, 0);
    Plane wallTop(wallTopCenter, wallNormalTop, r);
    wallTop.setMaterial(Material::MTRL_RED);
    wallTop.transform.rotateX(Common::PI / 2);
    wallTop.transform.translate(0, 0, -c);

    const Vector3 wallBottomCenter(0, -c, 0);
    const Vector3 wallNormalBottom(0, 1, 0);
    Plane wallBottom(wallBottomCenter, wallNormalBottom, r);
    wallBottom.setMaterial(Material::MTRL_RED);
    wallBottom.transform.rotateX(-Common::PI / 2);
    wallBottom.transform.translate(0, 0, -c);

    const Vector3 wallFrontCenter(0, 0, 3 * c);
    const Vector3 wallNormalFront(0, 0, -1);
    Plane wallFront(wallFrontCenter, wallNormalFront, r);
    wallFront.setMaterial(Material::MTRL_YELLOW);
    wallFront.transform.rotateX(Common::PI);
    wallFront.transform.translate(0, 0, -3 * c);

    Vector3 rotate(0, Common::PI, 0);
    Vector3 position(0, 0, -3 * c);
    CPlane frontPlane(rotate, position, r, lambMtrl);

    const Vector3 wallBackCenter(0, 0, -3 * c);
    const Vector3 wallNormalBack(0, 0, 1);
    Plane wallBack(wallBackCenter, wallNormalBack, r);
    wallBack.setMaterial(Material::MTRL_YELLOW);
    wallBack.transform.translate(0, 0, -3 * c);

    ObjectPool pool;

    // pool.add(&myBall);
    pool.add(&frontPlane);
    // pool.add(ballOne);
    // pool.add(ballTwo);
    // pool.add(ballThree);
    // pool.add(ballFour);
    // pool.add(ballFive);
    // pool.add(ballSix);
    // pool.add(ballSeven);
    // pool.add(ballEight);

    // pool.add(wallLeft);
    // pool.add(wallRight);
    // pool.add(wallTop);
    // pool.add(wallBottom);
    // pool.add(wallFront);
    // pool.add(wallBack);

    pool.setLight(0, 0, 20, 8);

    // unsigned width = 512 * 8, height = 512 * 8;
    // unsigned width = 512 * 4, height = 512 * 4;
    unsigned width = 512 * 1, height = 512 * 1;
    const float half_width = width / 2.0f;
    const float half_height = height / 2.0f;
    const int bounceTime = 8;
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
        for (unsigned x = 0; x < width; x++)
        {
            if (x == 0)
            {
                std::cout << "x:y --- "
                          << "(" << x << "," << y << ")" << std::endl;
            }
            const Vector3 origin(0, 0, 0);
            const Vector3 dir((x - half_width) / half_width, (y - half_height) / half_height, 2);
            Ray ray(origin, dir);

            Material mtrl = Material::MTRL_BLUE;
            HitRecord record;
            if (pool.hitScene(ray, record))
            {
                mtrl = Material::MTRL_RED;
            }

            // int outIndex = 0;

            // HitInfo info;
            // Material mtrl(Material::MTRL_BLACK);

            // for (int i = 2; i < bounceTime; i++)
            // {
            //     bool hit = pool.traceWithTimes(ray, i, outIndex, info, Material::MTRL_WHITE);
            //     int power = (i - 1);
            //     float w = 1;
            //     float m = 1;
            //     for (int i = 0; i < power; i++)
            //     {
            //         w *= m;
            //     }

            //     if (hit)
            //     {
            //         mtrl.safeAdd(info.m_mtrl);
            //     }
            // }

            image[4 * width * y + 4 * x + 0] = mtrl.r;
            image[4 * width * y + 4 * x + 1] = mtrl.g;
            image[4 * width * y + 4 * x + 2] = mtrl.b;
            image[4 * width * y + 4 * x + 3] = mtrl.a;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return 0;
}