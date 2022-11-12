#include "matrix.h"
#include <cmath>

const Matrix Matrix::Identity = Matrix();

Matrix::Matrix()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = 0;
        }
    }

    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
}

const Matrix Matrix::getScaleMatrix(float sx, float sy, float sz)
{
    Matrix mtx;

    mtx.m[0][0] = sx;
    mtx.m[1][1] = sy;
    mtx.m[2][2] = sz;

    return mtx;
}

const Matrix Matrix::getTranslateMatrix(float tx, float ty, float tz)
{
    Matrix mtx;

    mtx.m[0][3] = tx;
    mtx.m[1][3] = ty;
    mtx.m[2][3] = tz;

    return mtx;
}

const Matrix Matrix::getRotXMatrix(float theta)
{
    Matrix mtx;

    mtx.m[1][1] = std::cos(theta);
    mtx.m[1][2] = -std::sin(theta);
    mtx.m[2][1] = std::sin(theta);
    mtx.m[2][2] = std::cos(theta);

    // mtx.m[1][1] = std::cos(theta);
    // mtx.m[1][2] = std::sin(theta);
    // mtx.m[2][1] = -std::sin(theta);
    // mtx.m[2][2] = std::cos(theta);

    return mtx;
}
const Matrix Matrix::getRotYMatrix(float theta)
{
    Matrix mtx;

    mtx.m[0][0] = std::cos(theta);
    mtx.m[0][2] = std::sin(theta);
    mtx.m[2][0] = -std::sin(theta);
    mtx.m[2][2] = std::cos(theta);

    // mtx.m[0][0] = std::cos(theta);
    // mtx.m[0][2] = -std::sin(theta);
    // mtx.m[2][0] = std::sin(theta);
    // mtx.m[2][2] = std::cos(theta);

    return mtx;
}

const Matrix Matrix::getRotZMatrix(float theta)
{
    Matrix mtx;

    mtx.m[0][0] = std::cos(theta);
    mtx.m[0][1] = -std::sin(theta);
    mtx.m[1][0] = std::sin(theta);
    mtx.m[1][1] = std::cos(theta);

    // mtx.m[0][0] = std::cos(theta);
    // mtx.m[0][1] = std::sin(theta);
    // mtx.m[1][0] = -std::sin(theta);
    // mtx.m[1][1] = std::cos(theta);

    return mtx;
}

const Matrix Matrix::Mul(const Matrix &m1, const Matrix &m2)
{
    Matrix r;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            r.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] +
                        m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
        }
    }
    return r;
}

const Vector3 Matrix::MulVector(const Matrix &m, const Vector3 &v)
{
    float x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
    float y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
    float z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;

    return Vector3(x, y, z);
}

const Vector3 Matrix::MulPoint(const Matrix &m, const Vector3 &p)
{
    float x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z + m.m[0][3];
    float y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z + m.m[1][3];
    float z = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z + m.m[2][3];

    // float w = 1;

    return Vector3(x, y, z);
}

const Matrix Matrix::getTransposeMatrix(const Matrix &m)
{
    Matrix r;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            r.m[i][j] = m.m[j][i];
        }
    }

    return r;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    os << "[" << matrix.m[0][0] << "," << matrix.m[0][1] << "," << matrix.m[0][2] << "," << matrix.m[0][3] << "]" << std::endl;
    os << "[" << matrix.m[1][0] << "," << matrix.m[1][1] << "," << matrix.m[1][2] << "," << matrix.m[1][3] << "]" << std::endl;
    os << "[" << matrix.m[2][0] << "," << matrix.m[2][1] << "," << matrix.m[2][2] << "," << matrix.m[2][3] << "]" << std::endl;
    os << "[" << matrix.m[3][0] << "," << matrix.m[3][1] << "," << matrix.m[3][2] << "," << matrix.m[3][3] << "]" << std::endl;

    return os;
}