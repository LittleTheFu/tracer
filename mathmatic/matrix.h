#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

#include "vector.h"

class Matrix
{
public:
    Matrix();

    static const Matrix getScaleMatrix(float sx, float sy, float sz);
    static const Matrix getTranslateMatrix(float tx, float ty, float tz);
    static const Matrix getRotXMatrix(float theta);
    static const Matrix getRotYMatrix(float theta);
    static const Matrix getRotZMatrix(float theta);

    static const Matrix Mul(const Matrix &m1, const Matrix &m2);
    static const Vector3 MulVector(const Matrix &m, const Vector3 &v);
    static const Vector3 MulPoint(const Matrix &m, const Vector3 &p);

    static const Matrix getTransposeMatrix(const Matrix &m);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    static const Matrix Identity;

    float m[4][4];
};

#endif