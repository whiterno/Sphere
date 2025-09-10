#include "3dvector.h"

Vector::Vector (float x, float y, float z): x(x), y(y), z(z){
    len = std::sqrt(x * x + y * y + z * z);
}

Vector Vector::operator +(const Vector& other) const{
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator -(const Vector& other) const{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator *(float coef) const{
    return Vector(x * coef, y * coef, z * coef);
}

Vector Vector::operator /(float coef) const{
    return Vector(x / coef, y / coef, z / coef);
}

Vector Vector::operator *(const Vector& other) const{
    return Vector(x * other.x, y * other.y, z * other.z);
}

Vector operator *(float coef, const Vector& other){
    return Vector(other.x * coef, other.y * coef, other.z * coef);
}

Vector Vector::operator =(const Vector& other){
    x = other.x;
    y = other.y;
    z = other.z;

    len = std::sqrt(x * x + y * y + z * z);

    return *this;
}

Vector Vector::operator !() const{
    if (len < 10e-6f) return Vector(0, 0, 0);

    return Vector(x / len, y / len, z / len);
}

float Vector::operator |(const Vector& other) const{
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::reflect(const Vector& other){
    Vector unit_axis = !other;
    float dot = *this | unit_axis;

    return 2 * dot * unit_axis - *this;
}
