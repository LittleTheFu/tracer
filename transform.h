#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "matrix.h"

class Transform
{
public:
    Transform();
    Transform(const Matrix &matrix, const Matrix &invMatrix);

    void scale(float sx, float sy, float sz);
    void translate(const Vector3 &v);
    void translate(float tx, float ty, float tz);
    void rotate(const Vector3 &v);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);

    void set(const Vector3 &rotateXYZ, const Vector3 &position);

    Vector3 transformVector(const Vector3 &v) const;
    Vector3 invTransformVector(const Vector3 &v) const;
    Vector3 transformPoint(const Vector3 &p) const;
    Vector3 invTransformPoint(const Vector3 &p) const;
    Vector3 transformNormal(const Vector3 &n) const;
    Vector3 invTransformNormal(const Vector3 &n) const;

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