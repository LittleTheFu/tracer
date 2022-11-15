#include "noise.h"
#include "common.h"
#include <cmath>

Noise::Noise()
{
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < NUM; j++)
            for (int k = 0; k < NUM; k++)
            {
                m_data[0][0][0] = Common::genRamdomSignDecimal();
            }
}

float Noise::getValue(const Vector3 &v) const
{
    int iX, iY, iZ;
    float fX, fY, fZ;

    getComponent(v.x, iX, fX);
    getComponent(v.y, iY, fY);
    getComponent(v.z, iZ, fZ);

    int iiX = modIndex(iX + 1);
    int iiY = modIndex(iY + 1);
    int iiZ = modIndex(iZ + 1);

    float v00 = Common::interpolate(m_data[iX][iY][iZ], m_data[iiX][iY][iZ], fX);
    float v01 = Common::interpolate(m_data[iX][iY][iZ], m_data[iiX][iiY][iZ], fX);
    float v10 = Common::interpolate(m_data[iX][iY][iZ], m_data[iiX][iY][iiZ], fX);
    float v11 = Common::interpolate(m_data[iX][iY][iZ], m_data[iiX][iiY][iiZ], fX);

    float u0 = Common::interpolate(v00, v01, fY);
    float u1 = Common::interpolate(v10, v11, fY);

    float w = Common::interpolate(u0, u1, fZ);

    return w;
}

void Noise::getComponent(float a, int &i, float &f) const
{
    i = std::floor(a);
    f = a - i;
    i = modIndex(i);
}

int Noise::modIndex(int n) const
{
    int m = n % NUM;
    if (m < 0)
    {
        m += NUM;
    }

    return m;
}