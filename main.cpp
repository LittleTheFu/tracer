#include "lodepng.h"

#include "ray.h"
#include "ball.h"
#include "objectpool.h"

#include <iostream>
using namespace std;

int main()
{
    // const Vector3 origin(0, 0, 0);
    // const Vector3 dir(1,0,0);
    // Ray ray(origin, dir);

    // const Vector3 center(10,1,0);
    // const Ball ball(center, 1);

    // bool hit = ray.hit(ball);
    // // generate some image

    const Vector3 center(5, 5, 30);
    const Ball ball(center, 3);

    ObjectPool pool;
    pool.add(ball);

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

            // bool hit = ray.hit(ball);
            bool hit = pool.hit(ray);
            // hit = true;
            // cout << hit << endl;

            image[4 * width * y + 4 * x + 0] = hit ? 255 : 0;
            image[4 * width * y + 4 * x + 1] = 0;
            image[4 * width * y + 4 * x + 2] = 0;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    // cout << hit << endl;
    return 0;
}