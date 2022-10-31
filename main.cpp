#include "lodepng.h"

#include "ray.h"
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

    Rmaterial lambMtrlRed;
    lambMtrlRed.pBrdf = brdfMgr.getRedBrdf();

    Rmaterial lambMtrlGreen;
    lambMtrlGreen.pBrdf = brdfMgr.getGreenBrdf();

    Rmaterial lambMtrlBlue;
    lambMtrlBlue.pBrdf = brdfMgr.getBlueBrdf();

    Rmaterial lambMtrlWhite;
    lambMtrlWhite.pBrdf = brdfMgr.getWhiteBrdf();

    CBall *myBall = new CBall(Vector3::ZERO, Vector3(5, 5, 60), 5, lambMtrlRed);

    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, -Common::PI / 2, 0);
    Vector3 leftPosition(0, 0, -c);
    CPlane *leftPlane = new CPlane(leftRotate, leftPosition, r, lambMtrlRed);

    Vector3 rightRotate(0, Common::PI / 2, 0);
    Vector3 rightPosition(0, 0, -c);
    CPlane *rightPlane = new CPlane(rightRotate, rightPosition, r, lambMtrlRed);

    Vector3 topRotate(Common::PI / 2, 0, 0);
    Vector3 topPosition(0, 0, -c);
    CPlane*  topPlane = new CPlane(topRotate, topPosition, r, lambMtrlBlue);

    Vector3 bottomRotate(-Common::PI / 2, 0, 0);
    Vector3 bottomPosition(0, 0, -c);
    CPlane* bottomPlane = new CPlane(bottomRotate, bottomPosition, r, lambMtrlBlue);

    Vector3 frontRotate(0, Common::PI, 0);
    Vector3 frontPosition(0, 0, -3 * c);
    CPlane* frontPlane = new CPlane(frontRotate, frontPosition, r, lambMtrlGreen);

    Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backPosition(0, 0, -3 * c);
    CPlane* backPlane = new CPlane(backRotate, backPosition, r, lambMtrlGreen);

    ObjectPool pool;

    pool.add(myBall);
    pool.add(frontPlane);
    pool.add(backPlane);
    pool.add(topPlane);
    pool.add(bottomPlane);
    pool.add(leftPlane);
    pool.add(rightPlane);

    pool.setLight(0, 0, 20, 8);

    // unsigned width = 512 * 8, height = 512 * 8;
    // unsigned width = 512 * 4, height = 512 * 4;
    unsigned width = 512 * 1, height = 512 * 1;
    const float half_width = width / 2.0f;
    const float half_height = height / 2.0f;
    const int bounceTime = 5;
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
            record.reflectPdf = 1;
            record.dot = 1;

            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            // if (pool.hitScene(ray, record))
            // {
            //     ((Lambertian *)(record.mtrl.pBrdf))->m_rho.getConvertedValue(r, g, b);
            // }

            Color color = Color::COLOR_BLACK;
            for (int i = 2; i < bounceTime; i++)
            {
                // bool hit = pool.traceWithTimes(ray, i, outIndex, info, Material::MTRL_WHITE);
                color += pool.trace(ray, i, record);
            }

            color.getConvertedValue(r, g, b);

            image[4 * width * y + 4 * x + 0] = r;
            image[4 * width * y + 4 * x + 1] = g;
            image[4 * width * y + 4 * x + 2] = b;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    unsigned error = lodepng::encode("img.png", image, width, height);

    if (error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return 0;
}