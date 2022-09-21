#include "lodepng.h"

#include "ray.h"
#include "ball.h"
#include "plane.h"
#include "objectpool.h"

#include <iostream>
using namespace std;

int main()
{
    const Vector3 centerOne(5, 5, 30);
    const Ball ballOne(centerOne, 10);

    const Vector3 centerTwo(-10, 0, 200);
    const Ball ballTwo(centerTwo, 60);

    const Vector3 centerLeft(-20, 0, 100);
    const Vector3 planeNormalLeft(1, 0, 0);
    const Plane planeLeft(centerLeft, planeNormalLeft, 40);

    const Vector3 centerRight(20, 0, 100);
    const Vector3 planeNormalRight(-1, 0, 0);
    const Plane planeRight(centerRight, planeNormalRight, 40);

    const Vector3 centerTop(0, 20, 100);
    const Vector3 planeNormalTop(0, -1, 0);
    const Plane planeTop(centerTop, planeNormalTop, 40);

    const Vector3 centerBottom(0, -20, 100);
    const Vector3 planeNormalBottom(0, 1, 0);
    const Plane planeBottom(centerBottom, planeNormalBottom, 40);

    ObjectPool pool;
    // pool.add(ballOne);
    pool.add(ballTwo);
    pool.add(planeLeft);
    pool.add(planeRight);
    pool.add(planeTop);
    pool.add(planeBottom);

    unsigned width = 512, height = 512;
    const float half_width = width / 2.0f;
    const float half_height = height / 2.0f;
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
        for (unsigned x = 0; x < width; x++)
        {
            const Vector3 origin(0, 0, 0);
            const Vector3 dir((x - half_width) / half_width, (y - half_height) / half_height, 2);
            Ray ray(origin, dir);

            bool isBall = true;
            bool hit = pool.hit(ray, isBall);

            char r = 0;
            char g = 0;

            if (hit)
            {
                if (isBall)
                    r = 255;
                else
                    g = 255;
            }

            image[4 * width * y + 4 * x + 0] = r;
            image[4 * width * y + 4 * x + 1] = g;
            image[4 * width * y + 4 * x + 2] = 0;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return 0;
}