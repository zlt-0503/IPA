#include "group.h"

void Group::setTargetSlot(const Vec slotPos) {
    targetSlot = slotPos;
}

bool Group::IsTeleport() {
    return isTeleport;
}

Vec Group::getAnchor() {
    return Anchor;
}

void Group::enter() {
    currentStatus = status::Entering;
}

void Group::exit() {
    currentStatus = status::Exiting;
}

Group::status Group::getStatus() {
    return currentStatus;
}

void Group::draw() {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->draw();
    }
}

void Group::move(Vec direction) {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->move(direction);
    }
    Anchor = Anchor + direction;
}

void Group::rotate(Vec center, float angle) {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->rotate(center, angle);
    }
    Anchor = Anchor - center;
    Anchor = Anchor >> angle;
    Anchor = Anchor + center;
    Direction = Direction >> angle;
}

void Group::zoom(float k) {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->zoom(Anchor, k);
    }
}

Car::Car(Vec InitialPos) {
    isTeleport = false;
    currentStatus = status::Entering;
    currentMovingStatus = movingStatus::movingUp;
    Anchor = InitialPos;
    Direction = Vec(0.0f, 0.1f);
    flagPos = 1.0f;
    movingUp = true;
    const Vec p1(Anchor.getX() - 0.5f * Height, Anchor.getY() - 0.5f * Width);
    const Vec p2(Anchor.getX() + 0.5f * Height, Anchor.getY() - 0.5f * Width);
    const Vec p3(Anchor.getX() + 0.5f * Height, Anchor.getY() + 0.5f * Width);
    const Vec p4(Anchor.getX() - 0.5f * Height, Anchor.getY() + 0.5f * Width);
    const Polygon body({p1, p2, p3, p4}, 250.0f / 255.0f, 235.0f / 255.0f, 215.0f / 255.0f);
    shapes.push_back(std::make_unique<Polygon>(body));
    const Vec p5(Anchor.getX() + 0.5f * Height, Anchor.getY() - 0.25f * Width);
    const Vec p6(Anchor.getX() + 0.5f * Height, Anchor.getY() + 0.25f * Width);
    const Circle wheel1(p5, WheelRadius, 100, 1.0f, 153.0f / 255.0f, 18.0f / 255.0f);
    const Circle wheel2(p6, WheelRadius, 100, 1.0f, 153.0f / 255.0f, 18.0f / 255.0f);
    shapes.push_back(std::make_unique<Circle>(wheel1));
    shapes.push_back(std::make_unique<Circle>(wheel2));
    const Vec p7(Anchor.getX() - 0.5f * Height, Anchor.getY() - 0.375f * Width);
    const Vec p8(Anchor.getX() - 0.5f * Height, Anchor.getY() + 0.375f * Width);
    const Vec p9(Anchor.getX() - 1.5f * Height, Anchor.getY() + 0.25f * Width);
    const Vec p10(Anchor.getX() - 1.5f * Height, Anchor.getY() - 0.25f * Width);
    const Polygon window({p7, p8, p9, p10}, 0.0f, 1.0f, 1.0f);
    shapes.push_back(std::make_unique<Polygon>(window));
    const Vec p11(Anchor.getX() - 0.5f * Height, Anchor.getY() - 0.4f * Width);
    const Vec p12(Anchor.getX() - 1.5f * Height, Anchor.getY() - 0.4f * Width);
    const Line flagpole(p11, p12, 0.0f, 0.0f, 0.0f);
    shapes.push_back(std::make_unique<Line>(flagpole));
    const Vec p13(Anchor.getX() - 1.5f * Height, Anchor.getY() - 0.4f * Width);
    const Vec p14(Anchor.getX() - 1.2f * Height, Anchor.getY() - 0.4f * Width);
    const Vec p15(Anchor.getX() - 1.2f * Height, Anchor.getY() - 0.55f * Width);
    const Polygon flag({p13, p14, p15}, 1.0f, 0.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(flag));
}

void Car::draw() {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->draw();
    }
    if (!movingUp) {
        flagPos -= 0.025f;
        if (flagPos < 0.3f) {
            movingUp = true;
        }
    }
    else
    {
        flagPos += 0.025f;
        if (flagPos > 1.0f) {
            movingUp = false;
        }
    }
    Vec movingDir;
    if (movingUp) {
        movingDir = (Direction << ((float)M_PI / 2.0f)) * (Height / 4.0f);
    }
    else
    {
        movingDir = (Direction >> ((float)M_PI / 2.0f)) * (Height / 4.0f);
    }
    shapes[5]->move(movingDir);
}

UFO::UFO(Vec InitialPos) {
    isTeleport = false;
    currentStatus = status::Entering;
    currentMovingStatus = movingStatus::movingUp;
    Anchor = InitialPos;
    const Vec p1 = Anchor;
    const Vec p10(Anchor.getX() - Radius, Anchor.getY() + Radius);
    const Line l1(p1, p10, 0.0f / 255.0f, 199.0f / 255.0f, 140.0f / 255.0f);
    shapes.push_back(std::make_unique<Line>(l1));
    const Vec p11(Anchor.getX() + Radius, Anchor.getY() + Radius);
    const Line l2(p1, p11, 0.0f / 255.0f, 199.0f / 255.0f, 140.0f / 255.0f);
    shapes.push_back(std::make_unique<Line>(l2));
    const HalfCircle body(p1, Radius, 100, 65.0f / 255.0f, 105.0f / 255.0f, 1.0f);
    shapes.push_back(std::make_unique<HalfCircle>(body));
    const Vec p2(Anchor.getX() - 0.8f * Radius, Anchor.getY());
    const Vec p3(Anchor.getX() - 0.2f * Radius, Anchor.getY());
    const Vec p4(Anchor.getX() - 0.1f * Radius, Anchor.getY() - 0.2f * Radius);
    const Vec p5(Anchor.getX() - 0.9f * Radius, Anchor.getY() - 0.2f * Radius);
    const Polygon Promoter1({p2, p3, p4, p5}, 218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f);
    shapes.push_back(std::make_unique<Polygon>(Promoter1));
    const Vec p6(Anchor.getX() + 0.8f * Radius, Anchor.getY());
    const Vec p7(Anchor.getX() + 0.2f * Radius, Anchor.getY());
    const Vec p8(Anchor.getX() + 0.1f * Radius, Anchor.getY() - 0.2f * Radius);
    const Vec p9(Anchor.getX() + 0.9f * Radius, Anchor.getY() - 0.2f * Radius);
    const Polygon Promoter2({p6, p7, p8, p9}, 218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f);
    shapes.push_back(std::make_unique<Polygon>(Promoter2));
}

void UFO::draw() {
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
    rotate(getAnchor(), (float)M_PI / 180.0f);
}

Spacecraft::Spacecraft(Vec InitialPos) {
    isTeleport = false;
    currentStatus = status::Entering;
    currentMovingStatus = movingStatus::movingUp;
    Anchor = InitialPos;
    zoomingOut = true;
    zoomRate = 1.0f;
    const Vec p1(Anchor.getX() - 0.5f * BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Vec p2(Anchor.getX() + 0.5f * BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Vec p3(Anchor.getX() + 0.5f * BodyWidth, Anchor.getY() + 0.5f * BodyHeight);
    const Vec p4(Anchor.getX() - 0.5f * BodyWidth, Anchor.getY() + 0.5f * BodyHeight);
    const Polygon body({p1, p2, p3, p4}, 1.0f, 1.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(body));
    const Vec p5(Anchor.getX() - 2.5f * WindowWidth, Anchor.getY() + 4.0f * WindowWidth);
    const Vec p6(Anchor.getX() - 1.5f * WindowWidth, Anchor.getY() + 4.0f * WindowWidth);
    const Vec p7(Anchor.getX() - 1.5f * WindowWidth, Anchor.getY() + 5.0f * WindowWidth);
    const Vec p8(Anchor.getX() - 2.5f * WindowWidth, Anchor.getY() + 5.0f * WindowWidth);
    const Polygon LeftWindow({p5, p6, p7, p8}, 1.0f, 0.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(LeftWindow));
    const Vec p9(Anchor.getX() + 2.5f * WindowWidth, Anchor.getY() + 4.0f * WindowWidth);
    const Vec p10(Anchor.getX() + 1.5f * WindowWidth, Anchor.getY() + 4.0f * WindowWidth);
    const Vec p11(Anchor.getX() + 1.5f * WindowWidth, Anchor.getY() + 5.0f * WindowWidth);
    const Vec p12(Anchor.getX() + 2.5f * WindowWidth, Anchor.getY() + 5.0f * WindowWidth);
    const Polygon RightWindow({p9, p10, p11, p12}, 1.0f, 0.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(RightWindow));
    const Vec p13(Anchor.getX() - 0.5f * WindowWidth, Anchor.getY());
    const Vec p14(Anchor.getX() + 0.5f * WindowWidth, Anchor.getY());
    const Vec p15(Anchor.getX() + 0.5f * WindowWidth, Anchor.getY() + 2.0f * WindowWidth);
    const Vec p16(Anchor.getX() - 0.5f * WindowWidth, Anchor.getY() + 2.0f * WindowWidth);
    const Polygon MidWindow({p13, p14, p15, p16}, 0.0f, 1.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(MidWindow));
    const Vec p17(Anchor.getX() - 0.4f *  BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Vec p18(Anchor.getX() + 0.4f * BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Vec p19(Anchor.getX() + 0.5f * BodyWidth, Anchor.getY() - 0.625f * BodyHeight);
    const Vec p20(Anchor.getX() - 0.5f * BodyWidth, Anchor.getY() - 0.625f * BodyHeight);
    const Polygon promoter({p17, p18, p19, p20}, 0.0f, 0.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(promoter));
    const Vec p21(Anchor.getX() - 0.5f * BodyWidth, Anchor.getY());
    const Vec p22(Anchor.getX() - 1.2f * BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Polygon LeftWing({p1, p22, p21}, 1.0f, 0.6f, 0.067f);
    shapes.push_back(std::make_unique<Polygon>(LeftWing));
    const Vec p23(Anchor.getX() + 0.5f * BodyWidth, Anchor.getY());
    const Vec p24(Anchor.getX() + 1.2f * BodyWidth, Anchor.getY() - 0.5f * BodyHeight);
    const Polygon RightWing({p2, p24, p23}, 1.0f, 0.6f, 0.067f);
    shapes.push_back(std::make_unique<Polygon>(RightWing));
    const Vec p25(Anchor.getX(), Anchor.getY() + 0.5f * BodyHeight + 0.866f * BodyWidth);
    const Polygon head({p25, p3, p4}, 0.5f, 1.0f, 0.0f);
    shapes.push_back(std::make_unique<Polygon>(head));
}

void Spacecraft::draw() {
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
    if (!zoomingOut) {
        zoomRate /= 1.005f;
        if (zoomRate < powf(1.0f / 1.005f, 5)) {
            zoomingOut = true;
        }
    }
    else
    {
        zoomRate *= 1.005f;
        if (zoomRate > powf(1.005f, 5)) {
            zoomingOut = false;
        }
    }
    zoom(zoomRate);
}

Teleport::Teleport(Vec initialPos) : colorPhase(0.0f) {
    isTeleport = true;
    currentStatus = status::Entering;
    Anchor = initialPos;
    srand((unsigned int)(time(NULL)));
    colors.resize(4, std::vector<float>(3));
    changecolor();
    points.push_back(Anchor + Vec(-0.5f * Width, -0.5f * Height));
    points.push_back(Anchor + Vec(0.5f * Width, -0.5f * Height));
    points.push_back(Anchor + Vec(0.5f * Width, 0.5f * Height));
    points.push_back(Anchor + Vec(-0.5f * Width, 0.5f * Height));
}

void Teleport::changecolor() {
    colorPhase += 0.05f;
    for (size_t i = 0; i < 4; ++i) {
        colors[i][0] = (std::sin(colorPhase + (float)i * 0.5f) + 1) / 2;
        colors[i][1] = (std::sin(colorPhase + 2.0f + (float)i * 0.5f) + 1) / 2;
        colors[i][2] = (std::sin(colorPhase + 4.0f + (float)i * 0.5f) + 1) / 2;
    }
}

void Teleport::draw() {
    #ifndef NO_GUI
    glBegin(GL_QUADS);
    for (size_t i = 0; i < points.size(); i++) {
        glColor3fv(&colors[i][0]);
        const float dx = (float)(rand() % 1000 - 500) / 500.0f;
        const float dy = (float)(rand() % 1000 - 500) / 500.0f;
        glVertex2f(points[i].getX() + dx, points[i].getY() + dy);
    }
    glEnd();
    changecolor();
    #endif
}

void Teleport::move(Vec direction) {
    Anchor = Anchor + direction;
    points[0] = Anchor + Vec(-0.5f * Width, -0.5f * Height);
    points[1] = Anchor + Vec(0.5f * Width, -0.5f * Height);
    points[2] = Anchor + Vec(0.5f * Width, 0.5f * Height);
    points[3] = Anchor + Vec(-0.5f * Width, 0.5f * Height);
}

void Teleport::enter() {
    currentStatus = Parked;
}

void Teleport::exit() {
    currentStatus = Out;
}
