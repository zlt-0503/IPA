#ifndef VEC_H
#define VEC_H
#include <cmath>

class Vec {
    private:
        float x, y;
    public:
        //initialize a Vec [default: (0, 0)]
        explicit Vec(float _x = 0, float _y = 0) : x(_x), y(_y) {}
        //get the coodinate of the Vec
        float getX() const;
        float getY() const;
        // return current vector added by another vector v
        Vec operator + (const Vec v) const;
        // return current vector substracted by another vector v
        Vec operator - (const Vec v) const;
        // return current vector multiplied by a constant k
        Vec operator * (const float k) const;
        // return the dot product of the current vector and another vector v
        float operator * (const Vec v) const;
        // return current vector rotated counter clockwise by a
        Vec operator << (const float a) const;
        // return current vector rotated clockwise by a
        Vec operator >> (const float angle) const;
};

#endif
