#ifndef SHAPE_H
#define SHAPE_H
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "figure.h"

// Class for basic shapes
class Shape : public Figure {
    public:
        void move(Vec direction) override;
        void rotate(Vec anchor, float) override;
        void zoom(Vec anchor, const float k);
        void draw() override = 0;
    protected:
        std::vector<Vec> points;
};
// Inheritance classes of Shape.
class Polygon : public Shape {
public:
    Polygon(const std::vector<Vec>& points, float r, float g, float b);
    void draw() override;
private:
    float r = 0.0f, g = 0.0f, b = 0.0f;
};

class Circle : public Shape {
    public:
        Circle(Vec p1, float radius, int _segment, float r, float g, float b);
        void draw() override;
    private:
        float r = 0.0f, g = 0.0f, b = 0.0f;
        float radius;
        int segment;
};

class HalfCircle : public Shape {
    public:
        HalfCircle(Vec p1, float radius, int _segment, float r, float g, float b);
        void draw() override;
    private:
        float r = 0.0f, g = 0.0f, b = 0.0f;
        float radius;
        int segment;
};

class Line : public Shape {
    public:
        Line(Vec p1, Vec p2, float r, float g, float b);
        void draw() override;
    private:
        float r = 0.0f, g = 0.0f, b = 0.0f;
};
#endif
