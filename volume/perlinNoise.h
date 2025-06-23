#ifndef _PERLIN_NOISE_
#define _PERLIN_NOISE_

#include "vector.h"
#include <array>

class PerlinNoise
{
public:
    PerlinNoise();
    
    float get(const Vector3& point) const;

private:
    void initTable();
    float grad(int hash, const Vector3& distanceVector) const;

private:
    static const Vector3 grad3[12];

    static const int BASE_COUNT = 256;
    static const int TABLE_SIZE = BASE_COUNT * 2;
    std::array<int, TABLE_SIZE> table_;
};

#endif