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
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_s);
}

void Transform::translate(float tx, float ty, float tz)
{
    Matrix t = Matrix::getTranslateMatrix(tx, ty, tz);
    Matrix inv_t = Matrix::getTranslateMatrix(-tx, -ty, -tz);

    m_matrix = Matrix::Mul(m_matrix, t);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_t);
}

void Transform::rotateX(float theta)
{
    Matrix r = Matrix::getRotXMatrix(theta);
    Matrix inv_r = Matrix::getRotXMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
}

void Transform::rotateY(float theta)
{
    Matrix r = Matrix::getRotYMatrix(theta);
    Matrix inv_r = Matrix::getRotYMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
}

void Transform::rotateZ(float theta)
{
    Matrix r = Matrix::getRotZMatrix(theta);
    Matrix inv_r = Matrix::getRotZMatrix(-theta);

    m_matrix = Matrix::Mul(m_matrix, r);
    m_invMatrix = Matrix::Mul(m_invMatrix, inv_r);
}