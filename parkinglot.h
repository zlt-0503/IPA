#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include "group.h"
class Slot {
    public:
        explicit Slot(Vec pos) : isEmpty(true), position(pos) {}
        bool isEmptySlot() const;
        void parkVehicle(std::shared_ptr<Group> v);
        std::shared_ptr<Group> removeVehicle();
        Group* getVehicle() const;
    private:
        bool isEmpty;
        Vec position;
        std::shared_ptr<Group> parkedVehicle;
};

class ParkingLot {
    public:
        ParkingLot();
        void PLdraw();
        Slot* findEmptySlot();
        bool isFull();
        void parkRandomVehicle();
        void removeRandomVehicle();
        void update();
        void drawAll();
        void prepare();
        void change();
        int getParkedNum() const;
    private:
        std::unique_ptr<Group> generateRandomVehicle();
        std::vector<Slot> slots;
        std::vector<std::shared_ptr<Group>> movingVehicles;
        Vec enterance;
};

#endif
