#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "matrix.h"

class Transform
{
public:
    Transform();
    Transform(const Matrix &matrix, const Matrix &invMatrix);

    Transform getInverseTransform();

    Transform &applyTransform(const Transform &t);

    Transform &scale(float sx, float sy, float sz);
    Transform &translate(const Vector3 &v);
    Transform &translate(float tx, float ty, float tz);
    Transform &rotate(const Vector3 &v);
    Transform &rotateX(float theta);
    Transform &rotateY(float theta);
    Transform &rotateZ(float theta);

    Transform &set(const Vector3 &rotateXYZ, const Vector3 &position);

    Vector3 transformVector(const Vector3 &v) const;
    Vector3 invTransformVector(const Vector3 &v) const;
    Vector3 transformPoint(const Vector3 &p) const;
    Vector3 invTransformPoint(const Vector3 &p) const;
    Vector3 transformNormal(const Vector3 &n) const;
    Vector3 invTransformNormal(const Vector3 &n) const;

    Matrix getMatrix() const;
    Matrix getInverseMatrix() const;

private:
    Vector3 getAxisX() const;
    Vector3 getAxisY() const;
    Vector3 getAxisZ() const;

    Vector3 toLocal(const Vector3 &worldPosition) const;

private:
    Matrix m_matrix;
    Matrix m_invMatrix;
};

#endif