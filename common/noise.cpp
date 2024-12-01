#include "noise.h"
#include "mathUtility.h"
#include <cmath>

Noise::Noise()
{
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < NUM; j++)
            for (int k = 0; k < NUM; k++)
            {
                m_data[i][j][k] = Vector3::getRandomVector();
            }
}

float Noise::getValue(const Vector3 &v) const
{
    int iX, iY, iZ;
    float fX, fY, fZ;

    float factor = 0.5f;

    getComponent(v.x * factor, iX, fX);
    getComponent(v.y * factor, iY, fY);
    getComponent(v.z * factor, iZ, fZ);

    int iiX = modIndex(iX + 1);
    int iiY = modIndex(iY + 1);
    int iiZ = modIndex(iZ + 1);

    fX = MathUtility::smooth(fX);
    fY = MathUtility::smooth(fY);
    fZ = MathUtility::smooth(fZ);

    float v00 = MathUtility::interpolate(m_data[iX][iY][iZ] * (m_data[iX][iY][iZ] - v), m_data[iiX][iY][iZ] * (m_data[iiX][iY][iZ] - v), fX);
    float v01 = MathUtility::interpolate(m_data[iX][iiY][iZ] * (m_data[iX][iiY][iZ] - v), m_data[iiX][iiY][iZ] * (m_data[iiX][iiY][iZ] - v), fX);
    float v10 = MathUtility::interpolate(m_data[iX][iY][iiZ] * (m_data[iX][iY][iiZ] - v), m_data[iiX][iY][iiZ] * (m_data[iiX][iY][iiZ] - v), fX);
    float v11 = MathUtility::interpolate(m_data[iX][iiY][iiZ] * (m_data[iX][iiY][iiZ] - v), m_data[iiX][iiY][iiZ] * (m_data[iiX][iiY][iiZ] - v), fX);

    float u0 = MathUtility::interpolate(v00, v01, fY);
    float u1 = MathUtility::interpolate(v10, v11, fY);

    float w = MathUtility::interpolate(u0, u1, fZ);

    return w;
}

float Noise::getValue(float u, float v) const
{
    float uu = u * NUM;
    float vv = v * NUM;

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