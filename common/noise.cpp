#include "noise.h"
#include "mathUtility.h"
#include <cmath>

Noise::Noise()
{
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < NUM; j++)
            for (int k = 0; k < NUM; k++)
            {
                m_data[i][j][k] = MathUtility::genRamdomSignDecimal();
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

    // if(iiX < iX)
    // {
    //     std::swap(iX, iiX);
    // }

    // if(iiY < iY)
    // {
    //     std::swap(iY, iiY);
    // }

    // if(iiZ < iZ)
    // {
    //     std::swap(iZ, iiZ);
    // }

    float v00 = MathUtility::interpolate(m_data[iX][iY][iZ], m_data[iiX][iY][iZ], fX);
    float v01 = MathUtility::interpolate(m_data[iX][iiY][iZ], m_data[iiX][iiY][iZ], fX);
    float v10 = MathUtility::interpolate(m_data[iX][iY][iiZ], m_data[iiX][iY][iiZ], fX);
    float v11 = MathUtility::interpolate(m_data[iX][iiY][iiZ], m_data[iiX][iiY][iiZ], fX);

    float u0 = MathUtility::interpolate(v00, v01, fY);
    float u1 = MathUtility::interpolate(v10, v11, fY);

    float w = MathUtility::interpolate(u0, u1, fZ);

    return w;
}

float Noise::getValue(float u, float v) const
{
    float uu = u * NUM;
    float vv = v * NUM;

    // int iU, iV;
    // float fU, fV;

    // getComponent(uu, iU, fU);
    // getComponent(vv, iV, fV);

    // int iDummy = 0;
    // float fDummy = 0;
    const Vector3 fake_position(uu, vv, 0);

    return getValue(fake_position);
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