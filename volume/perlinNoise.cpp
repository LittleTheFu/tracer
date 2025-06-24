#include "perlinNoise.h"
#include <vector>
#include <random>
#include <mathUtility.h>
#include <cassert>

const Vector3 PerlinNoise::grad3[12] = {
    {1, 1, 0},
    {-1, 1, 0},
    {1, -1, 0},
    {-1, -1, 0},
    {1, 0, 1},
    {-1, 0, 1},
    {1, 0, -1},
    {-1, 0, -1},
    {0, 1, 1},
    {0, -1, 1},
    {0, 1, -1},
    {0, -1, -1},
};

PerlinNoise::PerlinNoise()
{
    initTable();
}

float PerlinNoise::get(const Vector3 &point) const
{
    if (std::isnan(point.x))
    {
        int a = 3;
    }

    Vector3 floorPoint = point.getFloor();
    Vector3 fractionalPoint = point.getFractional();

    int xi = static_cast<int>(floorPoint.x);
    int yi = static_cast<int>(floorPoint.y);
    int zi = static_cast<int>(floorPoint.z);

    float u = fractionalPoint.x;
    float v = fractionalPoint.y;
    float w = fractionalPoint.z;

    float su = MathUtility::smoothStep(u);
    float sv = MathUtility::smoothStep(v);
    float sw = MathUtility::smoothStep(w);

    int i = xi & 255;
    int j = yi & 255;
    int k = zi & 255;

    int aaa = table_.at(table_.at(table_.at(i) + j) + k);
    int aba = table_.at(table_.at(table_.at(i) + j + 1) + k);
    int aab = table_.at(table_.at(table_.at(i) + j) + k + 1);
    int abb = table_.at(table_.at(table_.at(i) + j + 1) + k + 1);
    int baa = table_.at(table_.at(table_.at(i + 1) + j) + k);
    int bba = table_.at(table_.at(table_.at(i + 1) + j + 1) + k);
    int bab = table_.at(table_.at(table_.at(i + 1) + j) + k + 1);
    int bbb = table_.at(table_.at(table_.at(i + 1) + j + 1) + k + 1);

    float u1 = u - 1.0f;
    float v1 = v - 1.0f;
    float w1 = w - 1.0f;

    float g_aaa = grad(aaa, Vector3(u, v, w));    // (xi, yi, zi)
    float g_baa = grad(baa, Vector3(u1, v, w));   // (xi+1, yi, zi)
    float g_aba = grad(aba, Vector3(u, v1, w));   // (xi, yi+1, zi)
    float g_bba = grad(bba, Vector3(u1, v1, w));  // (xi+1, yi+1, zi)
    float g_aab = grad(aab, Vector3(u, v, w1));   // (xi, yi, zi+1)
    float g_bab = grad(bab, Vector3(u1, v, w1));  // (xi+1, yi, zi+1)
    float g_abb = grad(abb, Vector3(u, v1, w1));  // (xi, yi+1, zi+1)
    float g_bbb = grad(bbb, Vector3(u1, v1, w1)); // (xi+1, yi+1, zi+1)

    float x_interp_00 = MathUtility::interpolate(g_aaa, g_baa, su);
    float x_interp_10 = MathUtility::interpolate(g_aba, g_bba, su);
    float x_interp_01 = MathUtility::interpolate(g_aab, g_bab, su);
    float x_interp_11 = MathUtility::interpolate(g_abb, g_bbb, su);

    float y_interp_0 = MathUtility::interpolate(x_interp_00, x_interp_10, sv);
    float y_interp_1 = MathUtility::interpolate(x_interp_01, x_interp_11, sv);

    float final_noise_value = MathUtility::interpolate(y_interp_0, y_interp_1, sw);

    assert(!std::isnan(final_noise_value));
    return final_noise_value;
}

void PerlinNoise::initTable()
{
    std::array<int, BASE_COUNT> v;
    for (int i = 0; i < BASE_COUNT; i++)
    {
        v.at(i) = i;

    }

    std::random_device rd;

    // for debug
    std::mt19937 g(123);

    std::shuffle(v.begin(), v.end(), g);

    for (int i = 0; i < BASE_COUNT; i++)
    {
        table_.at(i) = v.at(i);
        table_.at(i + BASE_COUNT) = v.at(i);
    }
}

float PerlinNoise::grad(int hash, const Vector3 &distanceVector) const
{
    int index = hash & 11;

    return grad3[index] * distanceVector;
}