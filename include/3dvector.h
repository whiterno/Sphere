#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector{
    public:
    float x, y, z;
    float len;

    Vector(float x, float y, float z);

    Vector operator +(const Vector& other) const;
    Vector operator -(const Vector& other) const;
    Vector operator *(float coef) const;
    Vector operator /(float coef) const;
    Vector operator *(const Vector& other) const;
    Vector operator !() const;
    float operator |(const Vector& other) const;

    Vector operator =(const Vector& other);

    Vector reflect(const Vector& other);

    friend Vector operator *(float coef, const Vector& other);
};

#endif
