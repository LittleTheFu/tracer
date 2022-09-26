#include "transform.h"

Transform::Transform()
{
}

Transform::Transform(const Matrix &matrix, const Matrix &invMatrix)
{
    m_matrix = matrix;
    m_invMatrix = invMatrix;
}

void Transform::scale(float sx, float sy, float sz)
{
    Matrix s = Matrix::getScaleMatrix(sx, sy, sz);
    Matrix inv_s = Matrix::getScaleMatrix(1.0f / sx, 1.0f / sy, 1.0f / sz);

    m_matrix = Matrix::Mul(m_matrix, s);
    m_invMatrix = Matrix::Mul(inv_s, m_invMatrix);
}

void Transform::translate(float tx, float ty, float tz)
{
    Matrix t = Matrix::getTranslateMatrix(tx, ty, tz);
    Matrix inv_t = Matrix::getTranslateMatrix(-tx, -ty, -tz);

    m_matrix = Matrix::Mul(m_matrix, t);
    m_invMatrix = Matrix::Mul(inv_t, m_invMatrix);
}

void Transform::rotateX(float theta)
{
    Matrix r = Matrix::getRotXMatrix(theta);
    Matrix inv_r = Matrix::getRotXMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);
}

void Transform::rotateY(float theta)
{
    Matrix r = Matrix::getRotYMatrix(theta);
    Matrix inv_r = Matrix::getRotYMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);
}

void Transform::rotateZ(float theta)
{
    Matrix r = Matrix::getRotZMatrix(theta);
    Matrix inv_r = Matrix::getRotZMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);
}

void Transform::setOrigin(float x, float y, float z)
{
    m_invMatrix.m[0][3] = x;
    m_invMatrix.m[1][3] = y;
    m_invMatrix.m[2][3] = z;

    float projX = m_matrix.m[0][0] * x + m_matrix.m[1][0] * y + m_matrix.m[2][0] * z;
    float projY = m_matrix.m[0][1] * x + m_matrix.m[1][1] * y + m_matrix.m[2][1] * z;
    float projZ = m_matrix.m[0][2] * x + m_matrix.m[1][2] * y + m_matrix.m[2][2] * z;

    m_matrix.m[0][3] = -projX;
    m_matrix.m[1][3] = -projY;
    m_matrix.m[2][3] = -projZ;
}

Vector3 Transform::transformVector(const Vector3 &v) const
{
    return Matrix::MulVector(m_matrix, v);
}

Vector3 Transform::invTransformVector(const Vector3 &v) const
{
    return Matrix::MulVector(m_invMatrix, v);
}

Vector3 Transform::transformPoint(const Vector3 &p) const
{
    return Matrix::MulPoint(m_matrix, p);
}

Vector3 Transform::invTransformPoint(const Vector3 &p) const
{
    return Matrix::MulPoint(m_invMatrix, p);
}

Vector3 Transform::transformNormal(const Vector3 &n) const
{
    const Matrix mtx = Matrix::getTransposeMatrix(m_invMatrix);

    return Matrix::MulVector(mtx, n);
}

Vector3 Transform::invTransformNormal(const Vector3 &n) const
{
    const Matrix mtx = Matrix::getTransposeMatrix(m_matrix);

    return Matrix::MulVector(mtx, n);
}