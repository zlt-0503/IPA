#ifndef PLMANAGER_H
#define PLMANAGER_H
#include <vector>
#include <memory>
#include "parkinglot.h"

class ParkingLotManager {
private:
    std::vector<std::unique_ptr<ParkingLot>> floors;
    int currentFloor;
    ParkingLotManager() : currentFloor(0) {}
public:
    static ParkingLotManager& getInstance() {
        static ParkingLotManager instance;
        return instance;
    }
    void initializeFloors(int numberOfFloors) {
        for (int i = 0; i < numberOfFloors; ++i) {
            floors.emplace_back(std::make_unique<ParkingLot>());
        }
        currentFloor = 0;
    }
    int getFloorNumber() {
        return (currentFloor + 1);
    }
    void prepareAllFloors() {
        for (std::unique_ptr<ParkingLot>& floor : floors) {
            floor->prepare();
        }
    }
    void setCurrentFloor(int floor) {
        if (floor >= 0 && floor < static_cast<int>(floors.size())) {
            currentFloor = floor;
        }
    }
    ParkingLot& getCurrentFloor() {
        return *(floors[(size_t)currentFloor]);
    }
    ParkingLotManager(const ParkingLotManager&) = delete;
    void operator=(const ParkingLotManager&) = delete;
};

#endif
