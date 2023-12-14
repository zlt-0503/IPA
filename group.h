#ifndef GROUP_H
#define GROUP_H
#include <memory>
#include <vector>
#include <cmath>
#include <utility>
#include "figure.h"
#include "shape.h"

// Class for the whole graph of vehicles
class Group : public Figure {
    public:
        enum status {
            Parked,
            Entering,
            Exiting,
            Out
        };
        enum movingStatus {
            turningRight,
            turningLeft,
            movingRight,
            movingLeft,
            movingUp,
            movingDown,
            none
        };
        void setTargetSlot(const Vec slotPos);
        status getStatus();
        void move(Vec direction) override;
        void rotate(Vec anchor, float angle) override;
        void zoom(float k);
        virtual void enter();
        virtual void exit();
        Vec getAnchor();
        void draw() override;
        bool IsTeleport();
        void update();
        void handleEntering(); void handleExiting();
        void handleMU1();
        void handleMD1();
        void handleMR1();
        void handleML1();
        void handleTR1();
        void handleTL1();
        void handleMU2();
        void handleMD2();
        void handleMR2();
        void handleML2();
        void handleTR2();
        void handleTL2();
        virtual ~Group() {}
    protected:
        Vec Anchor;
        Vec Direction;
        std::vector<std::unique_ptr<Shape>> shapes;
        status currentStatus;
        movingStatus currentMovingStatus = none;
        movingStatus lastMovingStatus = none;
        Vec targetSlot;
        bool isTeleport;
        float v = 2.5f;
        float av = (float)M_PI / 50.0f;
};
// Inheritance class of Group
class Car : public Group {
    public:
        explicit Car(Vec InitialPos);
        void draw() override;
    private:
        float flagPos;
        bool movingUp;
        float Width = 75;
        float Height = Width / 4.0f;
        float WheelRadius = Width / 8.0f;
};

class UFO : public Group {
    public:
        explicit UFO(Vec InittialPos);
        void draw() override;
    private:
        float Radius = 32;
};

class Spacecraft : public Group {
    public:
        explicit Spacecraft(Vec InitialPos);
        void draw() override;
    private:
        float BodyWidth = 15;
        float BodyHeight = 3.0f * BodyWidth;
        float WindowWidth = BodyWidth / 7.0f;
        bool zoomingOut;
        float zoomRate;
};

class Teleport : public Group{
    public:
        explicit Teleport(Vec initialPos);
        void changecolor();
        void draw() override;
        void move(Vec direction) override;
        void enter() override;
        void exit() override;
    private:
        std::vector<std::vector<float>> colors;
        std::vector<Vec> points;
        float colorPhase;
        float Width = 45;
        float Height = 1.5f * Width;
};

#endif
