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
    const Ball ballOne(centerOne, 3);

    const Vector3 centerTwo(-5, -15, 50);
    const Ball ballTwo(centerTwo, 4);

    const Vector3 centerThree(-25, -25, 80);
    const Vector3 planeNormal(10, 10, -1);
    const Plane plane(centerThree, planeNormal);

    ObjectPool pool;
    pool.add(ballOne);
    pool.add(ballTwo);
    pool.add(plane);

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

            bool hit = pool.hit(ray);

            image[4 * width * y + 4 * x + 0] = hit ? 255 : 0;
            image[4 * width * y + 4 * x + 1] = 0;
            image[4 * width * y + 4 * x + 2] = 0;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return 0;
}