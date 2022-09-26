#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "matrix.h"

class Transform
{
public:
    Transform();
    Transform(const Matrix &matrix, const Matrix &invMatrix);

    void scale(float sx, float sy, float sz);
    void translate(float tx, float ty, float tz);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);

    Matrix m_matrix;
    Matrix m_invMatrix;
};

#endif