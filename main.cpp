#include "lodepng.h"

#include "ray.h"
#include "ball.h"
#include "plane.h"
#include "objectpool.h"
#include "material.h"
#include "hitinfo.h"

#include <iostream>
using namespace std;

int main()
{
    const Vector3 centerOne(-10, 0, 70);
    Ball ballOne(centerOne, 3);
    ballOne.setMaterial(Material::MTRL_AQUA);

    const Vector3 centerTwo(15, 0, 50);
    Ball ballTwo(centerTwo, 3);
    ballTwo.setMaterial(Material::MTRL_RED);

    const Vector3 centerThree(25, 25, 80);
    Ball ballThree(centerThree, 3);
    ballThree.setMaterial(Material::MTRL_BLUE);

    const Vector3 centerFour(-2, 5, 25);
    Ball ballFour(centerFour, 2);
    ballFour.setMaterial(Material::MTRL_PURPLE);

    const Vector3 centerFive(-15, -25, 60);
    Ball ballFive(centerFive, 2);
    ballFive.setMaterial(Material::MTRL_PURPLE);

    const Vector3 centerSix(-3, -5, 20);
    Ball ballSix(centerSix, 0.7);
    ballSix.setMaterial(Material::MTRL_PURPLE);

    const float c = 100;
    const float r = 5 * c;
    const Vector3 wallLeftCenter(-c, 0, 0);
    const Vector3 wallNormalLeft(1, 0, 0);
    Plane wallLeft(wallLeftCenter, wallNormalLeft, r);
    wallLeft.setMaterial(Material::MTRL_BLUE);

    const Vector3 wallRightCenter(c, 0, 0);
    const Vector3 wallNormalRight(-1, 0, 0);
    Plane wallRight(wallRightCenter, wallNormalRight, r);
    wallRight.setMaterial(Material::MTRL_YELLOW);

    const Vector3 wallTopCenter(0, c, 0);
    const Vector3 wallNormalTop(0, -1, 0);
    Plane wallTop(wallTopCenter, wallNormalTop, r);
    wallTop.setMaterial(Material::MTRL_SILVER);

    const Vector3 wallBottomCenter(0, -c, 0);
    const Vector3 wallNormalBottom(0, 1, 0);
    Plane wallBottom(wallBottomCenter, wallNormalBottom, r);
    wallBottom.setMaterial(Material::MTRL_RED);

    const Vector3 wallFrontCenter(0, 0, 3 * c);
    const Vector3 wallNormalFront(0, 0, -1);
    Plane wallFront(wallFrontCenter, wallNormalFront, r);
    wallFront.setMaterial(Material::MTRL_GRAY);

    const Vector3 wallBackCenter(0, 0, -3 * c);
    const Vector3 wallNormalBack(0, 0, 1);
    Plane wallBack(wallBackCenter, wallNormalBack, r);
    wallBack.setMaterial(Material::MTRL_WHITE);

    ObjectPool pool;
    pool.add(ballOne);
    pool.add(ballTwo);
    pool.add(ballThree);
    pool.add(ballFour);
    pool.add(ballFive);
    pool.add(ballSix);
    pool.add(wallLeft);
    pool.add(wallRight);
    pool.add(wallTop);
    pool.add(wallBottom);
    pool.add(wallFront);
    pool.add(wallBack);

    pool.setLight(0, 0, 10, 8);

    // bool bTestHit = false;
    // Vector3 testOrigin = Vector3(0,0,0);
    // Vector3 testDir = Vector3(-200, 0, 100);
    // Ray testRay = Ray(testOrigin, testDir);
    // int testIndex = 0;
    // bTestHit = pool.directTrace(testRay, testIndex);

    // const Vector3 centerAplha(0, 0, 70);
    // Ball ballAlpha(centerAplha, 3);
    // ballAlpha.setMaterial(Material::MTRL_AQUA);

    // pool.add(ballAlpha);

    // const Vector3 centerRayAlpha = Vector3(0, 0, 0);
    // const Vector3 dirRayAlpha = Vector3(0, 0, 1);
    // const Ray rayAlpha = Ray(centerRayAlpha, dirRayAlpha);

    // float t1, t2;
    // int out1, out2;
    // HitInfo info1, info2;
    // bool flag1, flag2;

    // flag1 = pool.hitSceneObjectOld(rayAlpha, t1, out1, info1);
    // flag2 = pool.hitSceneObject(rayAlpha, t2, out2, info2);

    unsigned width = 512, height = 512;
    const float half_width = width / 2.0f;
    const float half_height = height / 2.0f;
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

            Vector3 hitPoint;
            Vector3 hitNormal;
            // bool isBall = true;
            int outIndex = 0;
            // float factor = 1;
            HitInfo info;
            // bool hit = pool.directTrace(ray, outIndex, info);
            Material mtrl(Material::MTRL_BLACK);
            float weight = 0;

            for (int i = 2; i < 5; i++)
            {
                bool hit = pool.traceWithTimes(ray, i, outIndex, info);
                int power = (i - 1);
                float w = 1;
                float m = 0.5;
                for (int i = 0; i < power; i++)
                {
                    w *= m;
                }

                if (hit)
                {
                    mtrl += info.m_mtrl * w;
                }
            }

            if (weight > 1)
            {
                weight = 1;
            }

            // cout<<"weight:"<<weight<<endl;
            // mtrl *= weight;

            // if (hit)
            // {
            //     mtrl = info.m_mtrl;
            // }

            image[4 * width * y + 4 * x + 0] = mtrl.r;
            image[4 * width * y + 4 * x + 1] = mtrl.g;
            image[4 * width * y + 4 * x + 2] = mtrl.b;
            image[4 * width * y + 4 * x + 3] = mtrl.a;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    // const Vector3 traceRayOrigin = Vector3(0, 0, 0);
    // const Vector3 traceRayDir = Vector3(0, 0, 1);
    // const Ray traceRay = Ray(traceRayOrigin, traceRayDir);

    // pool.trace(traceRay);

    return 0;
}