#ifdef __APPLE__
#include <GL/glut.h>
#elif defined(__linux__) || defined(_WIN32)
#include <GL/freeglut.h>
#endif
#include <iostream>
#include "group.h"
#include "parkinglot.h"
#include "PLmanager.h"
#include "interface.h"

int main (int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    const int num_floor = 3;
    int lasting_time = 120;
    cla(argc, argv, &lasting_time);
    TimerData::getInstance().setLastingTime(lasting_time * 1000);
    ParkingLotManager& manager = ParkingLotManager::getInstance();
    manager.initializeFloors(num_floor);
    #ifndef NO_GUI
    glutInit(&argc, argv);
    glutInitWindowSize(900, 700);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("IPA");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(50, Timer, 50);
    glutMainLoop();
    #endif
    return 0;
}
