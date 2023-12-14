#ifndef FIGURE_H
#define FIGURE_H
#include <vector>
#include <utility>
#ifdef __APPLE__
#include <GL/glut.h>
#elif defined(__linux__) || defined(_WIN32)
#include <GL/freeglut.h>
#endif
#include "vec.h"
// The base class for all figures, including vehicle figures and basic shapes
class Figure {
    public:
        virtual void move(Vec direction) = 0;
        virtual void rotate(Vec anchor, float) = 0;
        virtual void draw() = 0;
        virtual ~Figure() {}
};
#endif
