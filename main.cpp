#include "lodepng.h"

#include "ray.h"
#include "ball.h"
#include "plane.h"
#include "objectpool.h"

#include <iostream>
using namespace std;

int main()
{
    const Vector3 centerOne(33, 44, 40);
    const Ball ballOne(centerOne, 27);

    const Vector3 centerTwo(-17, -67, 53);
    const Ball ballTwo(centerTwo,20);

    const float c = 100;
    const float r = 5 * c;
    const Vector3 wallLeftCenter(-c, 0, 0);
    const Vector3 wallNormalLeft(1, 0, 0);
    const Plane wallLeft(wallLeftCenter, wallNormalLeft, r);

    const Vector3 wallRightCenter(c, 0, 0);
    const Vector3 wallNormalRight(-1, 0, 0);
    const Plane wallRight(wallRightCenter, wallNormalRight, r);

    const Vector3 wallTopCenter(0, c, 0);
    const Vector3 wallNormalTop(0, -1, 0);
    const Plane wallTop(wallTopCenter, wallNormalTop, r);

    const Vector3 wallBottomCenter(0, -c, 0);
    const Vector3 wallNormalBottom(0, 1, 0);
    const Plane wallBottom(wallBottomCenter, wallNormalBottom, r);

    const Vector3 wallFrontCenter(0, 0, c);
    const Vector3 wallNormalFront(0, 0, -1);
    const Plane wallFront(wallFrontCenter, wallNormalFront, r);

    const Vector3 wallBackCenter(0, 0, -c);
    const Vector3 wallNormalBack(0, 0, 1);
    const Plane wallBack(wallBackCenter, wallNormalBack, r);

    ObjectPool pool;
    pool.add(ballOne);
    pool.add(ballTwo);
    pool.add(wallLeft);
    pool.add(wallRight);
    pool.add(wallTop);
    pool.add(wallBottom);
    pool.add(wallFront);
    pool.add(wallBack);

    // unsigned width = 512, height = 512;
    // const float half_width = width / 2.0f;
    // const float half_height = height / 2.0f;
    // std::vector<unsigned char> image;
    // image.resize(width * height * 4);
    // for (unsigned y = 0; y < height; y++)
    //     for (unsigned x = 0; x < width; x++)
    //     {
    //         const Vector3 origin(0, 0, 0);
    //         const Vector3 dir((x - half_width) / half_width, (y - half_height) / half_height, 2);
    //         Ray ray(origin, dir);

    //         Vector3 hitPoint;
    //         Vector3 hitNormal;
    //         bool isBall = true;
    //         bool hit = pool.hit(ray, isBall, hitPoint, hitNormal);

    //         char r = 0;
    //         char g = 0;

    //         if (hit)
    //         {
    //             if (isBall)
    //                 r = 255;
    //             else
    //                 g = 255;
    //         }

    //         image[4 * width * y + 4 * x + 0] = r;
    //         image[4 * width * y + 4 * x + 1] = g;
    //         image[4 * width * y + 4 * x + 2] = 0;
    //         image[4 * width * y + 4 * x + 3] = 255;
    //     }

    // unsigned error = lodepng::encode("img.png", image, width, height);

    // if (error)
    //     std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    const Vector3 traceRayOrigin = Vector3(0, 0, 0);
    const Vector3 traceRayDir = Vector3(5, 9, 7);
    const Ray traceRay = Ray(traceRayOrigin, traceRayDir);

    pool.trace(traceRay);

    return 0;
}