#include "vec.h"

float Vec::getX() const{ return x; }
float Vec::getY() const{ return y; }
// return current vector added by another vector v
Vec Vec::operator + (const Vec v) const{
    return Vec(x + v.getX(), y + v.getY());
}
// return current vector substracted by another vector v
Vec Vec::operator - (const Vec v) const{
    return Vec(x - v.getX(), y - v.getY());
}
// return current vector multiplied by a constant k
Vec Vec::operator * (const float k) const{
    return Vec(x * k, y * k);
}
// return the dot product of the current vector and another vector v
float Vec::operator * (const Vec v) const{
    return (x * v.getX() + y * v.getY());
}
// return current vector rotated counter clockwise by a
Vec Vec::operator << (const float a) const{
    return Vec((float)(x * cos(a) - y * sin(a)), (float)(x * sin(a) + y * cos(a)));
}
// return current vector rotated clockwise by a
Vec Vec::operator >> (const float a) const{
    return Vec((float)(x * cos(a) + y * sin(a)), (float)(y * cos(a) - x * sin(a)));
}
