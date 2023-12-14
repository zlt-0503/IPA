#include "interface.h"

TimerData& TimerData::getInstance() {
    static TimerData instance;
    return instance;
}
void TimerData::setLastingTime(int time) {
    lastingTime = time;
}
bool TimerData::updateTime(int delta) {
    passedTime += delta;
    return passedTime >= lastingTime;
}
void reshape(int width, int height) {
    (void)width;
    (void)height;
    #ifndef NO_GUI
    if (height == 0) height = 1;
    const float aspect = (GLfloat)width / (GLfloat)height;
    const float desiredAspect = 900.0f / 700.0f;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= desiredAspect) {
        const float newWidth = (float)height * desiredAspect;
        const float extraWidth = ((float)width - newWidth) / 2.0f;
        glViewport((int)extraWidth, 0, (int)newWidth, height);
        gluOrtho2D(0.0, 900.0, 0.0, 700.0);
    } else {
        const float newHeight = (float)width / desiredAspect;
        const float extraHeight = (float)((float)height - (float)newHeight) / 2.0f;
        glViewport(0, (int)extraHeight, width, (int)newHeight);
        gluOrtho2D(0.0, 900.0, 0.0, 700.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    #endif
}

void keyboard(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    ParkingLotManager& manager = ParkingLotManager::getInstance();
    if (key >= '0' && key <= '9') {
        const int floor = key - '0' - 1;
        manager.setCurrentFloor(floor);
    }
}

void Timer(int value) {
    TimerData& data = TimerData::getInstance();
    if (data.updateTime(value)) {
        exit(0);
    }
    ParkingLotManager& manager = ParkingLotManager::getInstance();
    manager.prepareAllFloors();
    #ifndef NO_GUI
    manager.getCurrentFloor().drawAll();
    glutPostRedisplay();
    glutTimerFunc((unsigned int)value, Timer, value);
    #endif
}

void PrintString(float x, float y, void *font, const std::string &string) {
    (void)x;
    (void)y;
    (void)font;
    (void)string;
    #ifndef NO_GUI
    glRasterPos2f(x, y);
    for (const char c : string) {
        glutBitmapCharacter(font, c);
    }
    #endif
}

void glDraw() {
    const time_t now = time(0);
    struct tm *localTime = localtime(&now);
    std::stringstream timeStream;
    timeStream << std::setfill('0') << std::setw(2) << 1900 + localTime->tm_year << '-'
               << std::setfill('0') << std::setw(2) << 1 + localTime->tm_mon << '-'
               << std::setfill('0') << std::setw(2) << localTime->tm_mday << ' '
               << std::setfill('0') << std::setw(2) << localTime->tm_hour << ':'
               << std::setfill('0') << std::setw(2) << localTime->tm_min << ':'
               << std::setfill('0') << std::setw(2) << localTime->tm_sec;
    const std::string currentTime = timeStream.str();
    ParkingLotManager& manager = ParkingLotManager::getInstance();
    const int currentFloor = manager.getFloorNumber();
    std::stringstream ss;
    ss << "Floor " << currentFloor;
    const std::string floorText = ss.str();
    manager.prepareAllFloors();
    #ifndef NO_GUI
    glClear(GL_COLOR_BUFFER_BIT);
    manager.getCurrentFloor().drawAll();
    glColor3f(0.0, 0.0, 0.0);
    PrintString(200, 620, GLUT_BITMAP_TIMES_ROMAN_24, floorText);
    glColor3f(0.0, 0.0, 0.0);
    PrintString(320, 620, GLUT_BITMAP_TIMES_ROMAN_24, currentTime);
    glutSwapBuffers();
    #endif
}

void printHelpMessage() {
    std::cout << "-h | --help            Print help message\n";
    std::cout << "-t | --lasting-time\tSet the running time. (default: 120 seconds)\n";
}

void cla(int argc, char* argv[], int* lasting_time) {
    const std::string optString = "hf:t:";
    const struct option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"lasting-time", required_argument, nullptr, 't'},
        {nullptr, 0, nullptr, 0},
    };
    int opt = 0;
    int option_index = 0;
    while((opt = getopt_long_only(argc, argv, optString.c_str(), long_options, &option_index)) != -1) {
        switch(opt) {
            case 'h':
                printHelpMessage();
                exit(0);
                break;
            case 't':
                *lasting_time = std::stoi(optarg);
                if (*lasting_time < 60) {
                    std::cerr << "Lasting time is too short.\n";
                }
                break;
            default:
                std::cerr << "Invalid Command.\n";
                exit(1);
        }
    }
}
