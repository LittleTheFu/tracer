#include "transform.h"
#include "common.h"
#include <iostream>

Transform::Transform()
{
}

Transform::Transform(const Matrix &matrix, const Matrix &invMatrix)
{
    m_matrix = matrix;
    m_invMatrix = invMatrix;
}

Transform Transform::getInverseTransform()
{
    Transform t(m_invMatrix, m_matrix);

    return t;
}

Transform &Transform::applyTransform(const Transform &t)
{
    // m_matrix = Matrix::Mul(m_matrix, t.getMatrix());
    // m_invMatrix = Matrix::Mul(m_invMatrix, t.getInverseMatrix());

    m_matrix = Matrix::Mul(t.getMatrix(), m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, t.getInverseMatrix());
    // m_invMatrix = Matrix::Mul(t.getInverseMatrix(), m_invMatrix);

    return *this;
}

Transform &Transform::scale(float sx, float sy, float sz)
{
    Matrix s = Matrix::getScaleMatrix(sx, sy, sz);
    Matrix inv_s = Matrix::getScaleMatrix(1.0f / sx, 1.0f / sy, 1.0f / sz);

    // m_matrix = Matrix::Mul(m_matrix, s);
    // m_invMatrix = Matrix::Mul(inv_s, m_invMatrix);

    m_matrix = Matrix::Mul(s, m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_s);
    // m_invMatrix = Matrix::Mul(inv_s, m_invMatrix);

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

    // std::cout << "t:" << std::endl
    //           << t << std::endl;
    // std::cout << "inv_t:" << std::endl
    //           << inv_t << std::endl;

    // m_matrix = Matrix::Mul(m_matrix, t);
    // m_invMatrix = Matrix::Mul(inv_t, m_invMatrix);

    m_matrix = Matrix::Mul(t, m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_t);
    // m_invMatrix = Matrix::Mul(inv_t, m_invMatrix);

    std::cout << m_matrix << std::endl;
    std::cout << m_invMatrix << std::endl;

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

    std::cout << "r:" << std::endl
              << r << std::endl;
    std::cout << "inv_r:" << std::endl
              << inv_r << std::endl;

    // m_matrix = Matrix::Mul(m_matrix, r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    m_matrix = Matrix::Mul(r, m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    std::cout << m_matrix << std::endl;
    std::cout << m_invMatrix << std::endl;

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

    // std::cout << r << std::endl;
    // std::cout << inv_r << std::endl;

    // m_matrix = Matrix::Mul(m_matrix, r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    m_matrix = Matrix::Mul(r, m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    // std::cout << m_matrix << std::endl;
    // std::cout << m_invMatrix << std::endl;

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

    // std::cout << r << std::endl;
    // std::cout << inv_r << std::endl;

    // m_matrix = Matrix::Mul(m_matrix, r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    m_matrix = Matrix::Mul(r, m_matrix);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
    // m_invMatrix = Matrix::Mul(inv_r, m_invMatrix);

    // std::cout << m_matrix << std::endl;
    // std::cout << m_invMatrix << std::endl;

    return *this;
}

Transform &Transform::set(const Vector3 &rotateXYZ, const Vector3 &position)
{
    return rotate(rotateXYZ).translate(position);
    
    // rotate(rotateXYZ);
    // Vector3 localPoint = toLocal(position);

    // return translate(localPoint);
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

Matrix Transform::getMatrix() const
{
    return m_matrix;
}

Matrix Transform::getInverseMatrix() const
{
    return m_invMatrix;
}