#include "shape.h"
#include "vec.h"

void Shape::move(Vec direction) {
    std::transform(points.begin(), points.end(), points.begin(),[&direction](const Vec& point) {return point + direction;});
}

void Shape::rotate(Vec anchor, float angle) {
    for (auto& point : points) {
        point = point - anchor;
        point = point >> angle;
        point = point + anchor;
    }
}

void Shape::zoom(Vec anchor, const float k) {
    for (auto& point : points) {
        point = point - anchor;
        point = point * k;
        point = point + anchor;
    }
}

Polygon::Polygon(const std::vector<Vec>& vertice, float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
    points.reserve(vertice.size());
    std::copy(vertice.begin(), vertice.end(), std::back_inserter(points));
}

void Polygon::draw() {
    #ifndef NO_GUI
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
        for (const Vec p : points) {
            glVertex2f(p.getX(), p.getY());
        }
        glEnd();
    #endif
}

Circle::Circle(Vec p, float _radius, int _segment, float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
    segment = _segment;
    radius = _radius;
    points.push_back(p);
    for (int i = 0; i < segment; i++) {
        const float radian = 2 * (float)M_PI * (float)i / (float)segment;
        const float x = p.getX() + radius * cosf(radian);
        const float y = p.getY() + radius * sinf(radian);
        points.push_back(Vec(x, y));
    }
}

void Circle::draw() {
    #ifndef NO_GUI
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(points[0].getX(), points[0].getY());
            for (size_t i = 1; i < points.size(); i++) {
                glVertex2f(points[i].getX(), points[i].getY());
            }
            glVertex2f(points[1].getX(), points[1].getY());
        glEnd();
    #endif
}

HalfCircle::HalfCircle(Vec p, float _radius, int _segment, float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
    segment = _segment;
    radius = _radius;
    points.push_back(p);
    for (int i = 0; i < segment; i++) {
        const float radian = (float)M_PI * (float)i / (float)segment;
        const float x = p.getX() + radius * cosf(radian);
        const float y = p.getY() + radius * sinf(radian);
        points.push_back(Vec(x, y));
    }
}

void HalfCircle::draw() {
    #ifndef NO_GUI
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(points[0].getX(), points[0].getY());
            for (size_t i = 1; i < points.size(); i++) {
                glVertex2f(points[i].getX(), points[i].getY());
            }
            glVertex2f(points[1].getX(), points[1].getY());
        glEnd();
    #endif
}

Line::Line(Vec p1, Vec p2, float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
    points.push_back(p1);
    points.push_back(p2);
}

void Line::draw() {
    #ifndef NO_GUI
        glColor3f(r, g, b);
        glBegin(GL_LINES);
            glVertex2f(points[0].getX(), points[0].getY());
            glVertex2f(points[1].getX(), points[1].getY());
        glEnd();
    #endif
}
