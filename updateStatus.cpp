#include "group.h"

void Group::update() {
    switch (currentStatus) {
        case Entering:
            handleEntering();
            break;
        case Exiting:
            handleExiting();
            break;
        case Out:
        case Parked:
            break;
        default:
            return;
    }
}

void Group::handleMU1() {
    if (Anchor.getY() < 250) {
        move(Vec(0, v));
    }
    else if (Anchor.getY() >= 450 && Anchor.getY() < 525)
    {
        move(Vec(0, v));
    }
    else
    {
        if (Anchor.getY() == 525) {
            currentStatus = Parked;
            currentMovingStatus = none;
        }
        else if (Anchor.getY() == 250)
        {
            currentMovingStatus = turningRight;
        }
    }
    lastMovingStatus = movingUp;
}

void Group::handleMD1() {
    if (Anchor.getY() > targetSlot.getY()) {
        move(Vec(0, -1.0f * v));
    }
    else
    {
        currentStatus = Parked;
        currentMovingStatus = none;
    }
    lastMovingStatus = movingDown;
}

void Group::handleMR1() {
    if (targetSlot.getY() < 350 && Anchor.getX() < targetSlot.getX() + 50.0f) {
        move(Vec(v, 0));
    }
    else if (targetSlot.getY() > 350 && Anchor.getX() < 750)
    {
        move(Vec(v, 0));
    }
    else
    {
        currentMovingStatus = turningLeft;
    }
    lastMovingStatus = movingRight;
}

void Group::handleML1() {
    if (Anchor.getX() > targetSlot.getX() - 50.0f) {
        move(Vec(-1.0f * v, 0));
    }
    else if (Anchor.getX() == targetSlot.getX() - 50.0f)
    {
        currentMovingStatus = turningLeft;
    }
    lastMovingStatus = movingLeft;
}

void Group::handleTR1() {
    if (Anchor.getX() < 150) {
        rotate(Vec(150, 250), av);
    }
    else
    {
        currentMovingStatus = movingRight;
    }
    lastMovingStatus = turningRight;
}

void Group::handleTL1() {
    if (targetSlot.getY() < 350) {
        if (Anchor.getY() > 250) {
            rotate(targetSlot + Vec(50, 75), -1.0f * av);
        }
        else
        {
            currentMovingStatus = movingDown;
        }                        
    }
    else
    {
        if (Anchor.getX() >= 750) {
            if (Anchor.getY() < 400.0f) {
                rotate(Vec(750, 350), -1.0f * av);
            }
            else
            {
                currentMovingStatus = movingLeft;
            }
        }
        else
        {
            if (Anchor.getY() < targetSlot.getY() - 75) {
                rotate(targetSlot - Vec(50, 75), -1.0f * av);
            }
            else
            {
                currentMovingStatus = movingUp;
            }
        }
    }
    lastMovingStatus = turningLeft;
}


void Group::handleEntering() {
    switch (currentMovingStatus) {
        case movingUp:
            handleMU1();
            break;
        case turningRight:
            handleTR1();
            break;
        case movingRight:
            handleMR1();
            break;
        case turningLeft:
            handleTL1();
            break;
        case movingDown:
            handleMD1();
            break;
        case movingLeft:
            handleML1();
            break;
        default:
            return;
    }
}

void Group::handleMU2() {
    if (Anchor.getX() <= 150) {
        if (Anchor.getY() < 750) {
            move(Vec(0, v));
        }
        else
        {
            currentStatus = Out;
        }
    }
    else
    {
        if (Anchor.getY() < 250) {
            move(Vec(0, v));
        }
        else
        {
            currentMovingStatus = turningRight;
        }
    }
    lastMovingStatus = turningRight;
}

void Group::handleMD2() {
    if (Anchor.getY() > 450) {
        move(Vec(0, -1.0f * v));
    }
    else if (Anchor.getY() == 450)
    {
        currentMovingStatus = turningRight;
    }
    lastMovingStatus = movingDown;
}

void Group::handleMR2() {
    if (Anchor.getX() < 750) {
        move(Vec(v, 0));
    }
    else
    {
        currentMovingStatus = turningLeft;
    }
    lastMovingStatus = movingRight;
}

void Group::handleML2() {
    if (Anchor.getX() > 150) {
        move(Vec(-1.0f * v, 0));
    }
    else
    {
        currentMovingStatus = turningRight;
    }
    lastMovingStatus = movingLeft;
}

void Group::handleTR2() {
    if (Anchor.getX() > 150) {
        if (targetSlot.getY() < 350 && Anchor.getY() < 350) {
            if (Anchor.getY() < 300) {
                rotate(targetSlot + Vec(50, 75), av);
            }
            else
            {
                currentMovingStatus = movingRight;
            }
        }
        else
        {
            if (Anchor.getY() > 400) {
                rotate(targetSlot - Vec(50, 75), av);
            }
            else
            {
                currentMovingStatus = movingLeft;
            }
        }
    }
    else
    {
        if (Anchor.getY() < 450) {
            rotate(Vec(150, 450), av);
        }
        else
        {
            currentMovingStatus = movingUp;
        }
    }
    lastMovingStatus = turningRight;
}

void Group::handleTL2() {
    if (Anchor.getY() < 400 && Anchor.getX() >= 750) {
        rotate(Vec(750, 350), -1.0f * av);
    }
    else
    {
        currentMovingStatus = movingLeft;
    }
    lastMovingStatus = turningLeft;
}


void Group::handleExiting() {
    switch (currentMovingStatus) {
        case none:
            switch (lastMovingStatus) {
                case movingDown:
                    currentMovingStatus = movingUp;
                    break;
                case movingUp:
                    currentMovingStatus = movingDown;
                    break;
                default:
                    break;
            }
               break;
        case movingUp:
            handleMU2();
            break;
        case turningRight:
            handleTR2();
            break;
        case movingRight:
            handleMR2();
            break;
        case turningLeft:
            handleTL2();
            break;
        case movingDown:
            handleMD2();
            break;
        case movingLeft:
            handleML2();
            break;
        default:
            break;
    }
}
