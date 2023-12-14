#include "parkinglot.h"

bool Slot::isEmptySlot() const {
    return isEmpty;
}

void Slot::parkVehicle(std::shared_ptr<Group> v) {
    parkedVehicle = std::move(v);
    parkedVehicle->setTargetSlot(position);
    parkedVehicle->enter();
    if (parkedVehicle->IsTeleport()) {
        parkedVehicle->move(position - parkedVehicle->getAnchor());
    }
    isEmpty = false;
}

std::shared_ptr<Group> Slot::removeVehicle() {
    isEmpty = true;
    parkedVehicle->exit();
    return std::move(parkedVehicle);
}

Group* Slot::getVehicle() const{
    return parkedVehicle.get();
}

ParkingLot::ParkingLot() : enterance(Vec(100.0f, -50.0f)) {
    for (int i = 0; i < 6; ++i) {
        slots.emplace_back(Vec((float)(200 + i * 100), 175));
    }
    for (int i = 0; i < 6; ++i) {
        slots.emplace_back(Vec((float)(200 + i * 100), 525));
    }  
}

Slot* ParkingLot::findEmptySlot() {
    std::vector<int> emptySlotsIndices;
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].isEmptySlot()) {
            emptySlotsIndices.push_back((int)i);
        }
    }
    if (emptySlotsIndices.empty()) {
        return nullptr;
    } else {
        const int randomIndex = emptySlotsIndices[(size_t)rand() % emptySlotsIndices.size()];
        return &slots[(size_t)randomIndex];
    }
}


bool ParkingLot::isFull() {
    return findEmptySlot() == nullptr;
}

std::unique_ptr<Group> ParkingLot::generateRandomVehicle() {
    const int type = rand() % 4;
    switch (type) {
        case 1:
            return std::make_unique<Car>(enterance);
        case 2:
            return std::make_unique<UFO>(enterance);
        case 3:
            return std::make_unique<Spacecraft>(enterance);
        case 0:
            return std::make_unique<Teleport>(enterance);
        default:
            return nullptr;
    }
}

void ParkingLot::parkRandomVehicle() {
    Slot* emptySlot = findEmptySlot();
    if (emptySlot != nullptr) {
        const std::shared_ptr<Group> vehicle = generateRandomVehicle();
        if (vehicle) {
            if (!vehicle->IsTeleport()) {
                movingVehicles.push_back(vehicle);
            }
            emptySlot->parkVehicle(vehicle);
        }
    }
}

void ParkingLot::removeRandomVehicle() {
    std::vector<Slot*> eligibleSlots;
    for (Slot& slot : slots) {
        if (!slot.isEmptySlot() && slot.getVehicle()->getStatus() == Group::status::Parked) {
            eligibleSlots.push_back(&slot);
        }
    }
    if (!eligibleSlots.empty()) {
        const int selectedNum = rand() % static_cast<int>(eligibleSlots.size());
        Slot* selectedSlot = eligibleSlots[(size_t)selectedNum];
        Group* vehicle = selectedSlot->getVehicle();
        vehicle->exit();
        if (vehicle->IsTeleport()) {
            selectedSlot->removeVehicle();
        } else {
            movingVehicles.push_back(selectedSlot->removeVehicle());
        }
    }
}

void ParkingLot::PLdraw() {
    #ifndef NO_GUI
        const float r = 0.0f, g = 0.0f, b = 0.0f;
        const Vec sideWidth(50.0f, 50.0f);
        Line(Vec(0.0f, 0.0f) + sideWidth, Vec(0.0f, 600.0f) + sideWidth, r, g, b).draw();
        Line(Vec(0.0f, 300.0f) + sideWidth, Vec(700.0f, 300.0f) + sideWidth, r, g, b).draw();
        Line(Vec(800.0f, 50.0f) + sideWidth, Vec(800.0f, 550.0f) + sideWidth, r, g, b).draw();
        Line(Vec(100.0f, 0.0f) + sideWidth, Vec(100.0f, 200.0f) + sideWidth, r, g, b).draw();
        Line(Vec(100.0f, 400.0f) + sideWidth, Vec(100.0f, 600.0f) + sideWidth, r, g, b).draw();
        Line(Vec(100.0f, 50.0f) + sideWidth, Vec(800.0f, 50.0f) + sideWidth, r, g, b).draw();
        Line(Vec(100.0f, 550.0f) + sideWidth, Vec(800.0f, 550.0f) + sideWidth, r, g, b).draw();
        for (float i = 2.0f; i <= 7.0f; i++) {
            Line(Vec(i * 100.0f, 50.0f) + sideWidth, Vec(i * 100.0f, 200.0f) + sideWidth, r, g, b).draw();
            Line(Vec(i * 100.0f, 400.0f) + sideWidth, Vec(i * 100.0f, 550.0f) + sideWidth, r, g, b).draw();
        }
    #endif
}

void ParkingLot::update() {
    for (auto& vehicle : movingVehicles) {
        bool isPaused = false;
        const Vec vehicleAnchor = vehicle->getAnchor();
        for (auto& other : movingVehicles) {
            if (vehicle != other && !other->IsTeleport()&& !vehicle->IsTeleport()) {
                const Vec otherAnchor = other->getAnchor();
                if (vehicleAnchor.getX() < 150 && otherAnchor.getX() < 150) {
                    if (vehicleAnchor.getY() < 350 && otherAnchor.getY() < 350) {
                        const float dy = std::abs(vehicleAnchor.getY() - otherAnchor.getY());
                        if (dy <= 100) {
                            isPaused = true;
                            break;
                        }
                    }
                }
                else
                {
                    bool isFrontVehicle = false;
                    if (vehicleAnchor.getY() < 350 && otherAnchor.getY() < 350 && otherAnchor.getX() >= vehicleAnchor.getX()) {
                        if (otherAnchor.getX() > vehicleAnchor.getX()) {isFrontVehicle = true; }
                        else
                        {
                            if (otherAnchor.getY() > vehicleAnchor.getY()) {isFrontVehicle = true; }
                        }
                    }
                    if (isFrontVehicle) {
                        const float dx = std::abs(vehicleAnchor.getX() - otherAnchor.getX());
                        if (dx <= 100) {
                            isPaused = true;
                            break;
                        }
                    }
                }
            }
        }
        if (!isPaused) {
            vehicle->update();
        }
    }
    for (auto it = movingVehicles.begin(); it != movingVehicles.end(); ) {
        if ((*it)->getStatus() == Group::status::Out || (*it)->getStatus() == Group::status::Parked) {
            it = movingVehicles.erase(it);
        } else {
            ++it;
        }
    }
}

void ParkingLot::drawAll() {
    for (auto& vehicle : movingVehicles) {
        if (vehicle) {
            vehicle->draw();
        }
    }
    for (const auto& slot : slots) {
        if (!slot.isEmptySlot() && slot.getVehicle()->getStatus() == Group::status::Parked) {
            slot.getVehicle()->draw();
        }
    }
    PLdraw();
}

int ParkingLot::getParkedNum() const{
    const int count = (int)std::count_if(slots.begin(), slots.end(), [](const Slot& slot) {return !slot.isEmptySlot();});
    return count;
}

void ParkingLot::change() {
    if (!isFull() && rand() % 100 < 80) {
        parkRandomVehicle();
    }
    if (rand() % 100 < 50 && getParkedNum() > 4) {
        removeRandomVehicle();
    }
}

void ParkingLot::prepare() {
    static int timerCount = 100;
    const int intervalCount = 8000 / 50;
    update();
    timerCount++;
    if (timerCount >= intervalCount) {
        change();
        timerCount = 0;
    }
}
