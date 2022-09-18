#include "lodepng.h"
#include <iostream>
using namespace std;

int main()
{
    // generate some image
    unsigned width = 512, height = 512;
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
        for (unsigned x = 0; x < width; x++)
        {
            image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
            image[4 * width * y + 4 * x + 1] = x ^ y;
            image[4 * width * y + 4 * x + 2] = x | y;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    // if there's an error, display it
    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    cout << "Hello World !" << endl;
    return 0;
}