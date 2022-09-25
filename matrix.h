#ifndef _MATRIX_H_
#define _MATRIX_H_

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

    static const Matrix Identity;

    float m[4][4];
};

#endif