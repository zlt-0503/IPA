#ifndef INTERFACE_H
#define INTERFACE_H
#include <getopt.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "PLmanager.h"

class TimerData {
private:
    int passedTime;
    int lastingTime;
    TimerData() : passedTime(0), lastingTime(0) {}
public:
    static TimerData& getInstance();
    void setLastingTime(int time);
    bool updateTime(int delta);
    TimerData(const TimerData&) = delete;
    TimerData& operator=(const TimerData&) = delete;
};

void reshape(int width, int height);

void keyboard(unsigned char key, int x, int y);

void Timer(int value);

void PrintString(float x, float y, void *font, const std::string &string);

void glDraw();

void printHelpMessage();

void cla(int argc, char* argv[], int* lasting_time);

#endif
