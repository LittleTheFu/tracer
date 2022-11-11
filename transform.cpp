#include "transform.h"
#include "common.h"

Transform::Transform()
{
}

Transform::Transform(const Matrix &matrix, const Matrix &invMatrix)
{
    m_matrix = matrix;
    m_invMatrix = invMatrix;
}

Transform &Transform::scale(float sx, float sy, float sz)
{
    Matrix s = Matrix::getScaleMatrix(sx, sy, sz);
    Matrix inv_s = Matrix::getScaleMatrix(1.0f / sx, 1.0f / sy, 1.0f / sz);

    m_matrix = Matrix::Mul(m_matrix, s);
    m_invMatrix = Matrix::Mul(inv_s, m_invMatrix);

    return *this;
}

Transform &Transform::translate(const Vector3 &v)
{
    return translate(v.x, v.y, v.z);
}

Transform &Transform::translate(float tx, float ty, float tz)
{
    Matrix t = Matrix::getTranslateMatrix(tx, ty, tz);
    Matrix inv_t = Matrix::getTranslateMatrix(-tx, -ty, -tz);

    m_matrix = Matrix::Mul(m_matrix, t);
    m_invMatrix = Matrix::Mul(inv_t, m_invMatrix);

    return *this;
}

Transform &Transform::rotate(const Vector3 &v)
{
    return rotateX(v.x).rotateY(v.y).rotateZ(v.z);
}

Transform &Transform::rotateX(float theta)
{
    if (Common::is_float_zero(theta))
    {
        return *this;
    }

    Matrix r = Matrix::getRotXMatrix(theta);
    Matrix inv_r = Matrix::getRotXMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    return *this;
}

Transform &Transform::rotateY(float theta)
{
    if (Common::is_float_zero(theta))
    {
        return *this;
    }

    Matrix r = Matrix::getRotYMatrix(theta);
    Matrix inv_r = Matrix::getRotYMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    return *this;
}

Transform &Transform::rotateZ(float theta)
{
    if (Common::is_float_zero(theta))
    {
        return *this;
    }

    Matrix r = Matrix::getRotZMatrix(theta);
    Matrix inv_r = Matrix::getRotZMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    return *this;
}

Transform &Transform::set(const Vector3 &rotateXYZ, const Vector3 &position)
{
    Vector3 localPoint = toLocal(position);
    
    return rotate(rotateXYZ).translate(localPoint);
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

Vector3 Transform::getAxisX() const
{
    float x = m_matrix.m[0][0];
    float y = m_matrix.m[1][0];
    float z = m_matrix.m[2][0];

    return Vector3(x, y, z);
}

Vector3 Transform::getAxisY() const
{
    float x = m_matrix.m[0][1];
    float y = m_matrix.m[1][1];
    float z = m_matrix.m[2][1];

    return Vector3(x, y, z);
}

Vector3 Transform::getAxisZ() const
{
    float x = m_matrix.m[0][2];
    float y = m_matrix.m[1][2];
    float z = m_matrix.m[2][2];

    return Vector3(x, y, z);
}

Vector3 Transform::toLocal(const Vector3 &worldPosition) const
{
    float x = worldPosition * getAxisX();
    float y = worldPosition * getAxisY();
    float z = worldPosition * getAxisZ();

    return Vector3(x, y, z);
}