#include "lodepng.h"

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
using namespace std;

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

    Light *light = new Light(Vector3(0, -80, 220));

    const float c = 100;
    const float r = 5 * c;

    Vector3 leftRotate(0, -Common::PI / 2, 0);
    Vector3 leftPosition(0, 0, -c);
    // CPlane *leftPlane = new CPlane(leftRotate, leftPosition, r, &MtrlMirror);
    Plane *leftPlane = new Plane(leftRotate, leftPosition, r, &lambMtrlYellow);

    Vector3 rightRotate(0, Common::PI / 2, 0);
    Vector3 rightPosition(0, 0, -c);
    Plane *rightPlane = new Plane(rightRotate, rightPosition, r, &lambMtrlBlue);

    Vector3 topRotate(Common::PI / 2, 0, 0);
    Vector3 topPosition(0, 0, -c);
    Plane *topPlane = new Plane(topRotate, topPosition, r, &lambMtrlPurple);

    Vector3 bottomRotate(-Common::PI / 2, 0, 0);
    Vector3 bottomPosition(0, 0, -c);
    Plane *bottomPlane = new Plane(bottomRotate, bottomPosition, r, &lambMtrlGreen);

    Vector3 frontRotate(0, Common::PI, 0);
    Vector3 frontPosition(0, 0, -5 * c);
    // CPlane *frontPlane = new CPlane(frontRotate, frontPosition, r, &MtrlMirror);
    Plane *frontPlane = new Plane(frontRotate, frontPosition, r, &lambMtrlAqua);

    // Vector3 backRotate(0, -Common::PI, 0);
    Vector3 backRotate(0, 0, 0);
    Vector3 backPosition(0, 0, -3 * c);
    Plane *backPlane = new Plane(backRotate, backPosition, r, &lambMtrlRed);

    Vector3 glassRotate(-Common::PI / 2, 0, 0);
    Vector3 glassPosition(0, 0, -c * 0.5);
    Plane *glassPlane = new Plane(glassRotate, glassPosition, r, &MtrlGlass);

    ObjectPool pool;

    frontPlane->setTag(0);
    backPlane->setTag(1);
    topPlane->setTag(2);
    bottomPlane->setTag(3);
    leftPlane->setTag(4);
    rightPlane->setTag(5);

    glassBall->setTag(100);
    glassPlane->setTag(101);

    mirrorBall->setTag(200);

    pool.add(light);

    pool.add(redBall);
    pool.add(yellowBall);
    pool.add(aquaBall);
    pool.add(whiteBall);

    pool.add(glassBall);
    pool.add(mirrorBall);

    pool.add(frontPlane);
    pool.add(backPlane);
    pool.add(topPlane);
    pool.add(bottomPlane);
    pool.add(leftPlane);
    pool.add(rightPlane);

    // pool.add(glassPlane);

    // unsigned width = 512 * 8, height = 512 * 8;
    // unsigned width = 512 * 4, height = 512 * 4;
    // unsigned width = 512 * 2, height = 512 * 2;
    unsigned width = 512 * 1, height = 512 * 1;
    const float half_width = width / 2.0f;
    const float half_height = height / 2.0f;
    const int bounceTime = 10;
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

            HitRecord record;
            // record.reflectPdf = Common::INV_TWO_PI;
            record.reflectPdf = 1;
            record.dot = 1;
            record.f = Color::COLOR_WHITE;

            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            // if (pool.hitScene(ray, record))
            // {
            //     ((Lambertian *)(record.mtrl.pBrdf))->m_rho.getConvertedValue(r, g, b);
            // }
            if (x == 114 && y == 103)
            {
                std::cout << "test" << std::endl;
                int b = 3;
            }

            Color color = Color::COLOR_BLACK;
            for (int i = 2; i < bounceTime; i++)
            {
                // bool hit = pool.traceWithTimes(ray, i, outIndex, info, Material::MTRL_WHITE);
                color += pool.trace(ray, i, record);
            }

            color.getConvertedValue(r, g, b);

            // if (r == 0 && g == 0 && b == 0)
            // {
            //     int a = 3;
            // }

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