#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3 &that);
    float operator*(const Vector3 &that);

    void normalize();

    float x;
    float y;
    float z;

private:
    float length();
};

#endif