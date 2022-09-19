#include "lodepng.h"

#include "ray.h"
#include "ball.h"

#include <iostream>
using namespace std;

int main()
{
    const Vector3 origin(0, 0, 0);
    const Vector3 dir(1,0,0);
    Ray ray(origin, dir);

    const Vector3 center(10,1,0);
    const Ball ball(center, 1);

    bool hit = ray.hit(ball);
    // // generate some image
    // unsigned width = 512, height = 512;
    // std::vector<unsigned char> image;
    // image.resize(width * height * 4);
    // for (unsigned y = 0; y < height; y++)
    //     for (unsigned x = 0; x < width; x++)
    //     {
    //         image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
    //         image[4 * width * y + 4 * x + 1] = x ^ y;
    //         image[4 * width * y + 4 * x + 2] = x | y;
    //         image[4 * width * y + 4 * x + 3] = 255;
    //     }

    // unsigned error = lodepng::encode("img.png", image, width, height);

    // if (error)
    //     std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;


    cout << hit << endl;
    return 0;
}