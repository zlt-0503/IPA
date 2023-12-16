#include "interface.h"

TimerData& TimerData::getInstance() {
    static TimerData instance;
    return instance;
}
void TimerData::setLastingTime(int time) {
    lastingTime = time;
}
int TimerData::getPassedTime() {
    return passedTime;
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

void keyboardASCII(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    ParkingLotManager& plmanager = ParkingLotManager::getInstance();
    if (key >= '0' && key <= '9') {
        const int floor = key - '0' - 1;
        plmanager.setCurrentFloor(floor);
    }
}

void keyboardSpecial(int key, int x, int y) {
    (void)x;
    (void)y;
    ParkingLotManager& plmanager = ParkingLotManager::getInstance();
    if (key == GLUT_KEY_RIGHT) {
        for (int i = 0; i < 20; i++) {
            plmanager.prepareAllFloors();
        }
    }
}

void drawInit() {
    #ifndef NO_GUI
    glBegin(GL_POINTS);
        for (int i = 0; i < 900; ++i) {
            for (int j = 0; j < 700; ++j) {
                glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
                glVertex2i(i, j);
            }
        }
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    const std::string message = "Activating Monitor......";
    PrintString(350, 350, GLUT_BITMAP_TIMES_ROMAN_24, message);
    #endif
}

void drawPL() {
    #ifndef NO_GUI
    ParkingLotManager& PLmanager = ParkingLotManager::getInstance();
    PLmanager.prepareAllFloors();
    PLmanager.getCurrentFloor().drawAll();
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
    const int currentFloor = PLmanager.getFloorNumber();
    std::stringstream ss;
    ss << "Floor " << currentFloor;
    const std::string floorText = ss.str();
    PLmanager.prepareAllFloors();
    glClear(GL_COLOR_BUFFER_BIT);
    PLmanager.getCurrentFloor().drawAll();
    glColor3f(0.0, 0.0, 0.0);
    PrintString(200, 620, GLUT_BITMAP_TIMES_ROMAN_24, floorText);
    glColor3f(0.0, 0.0, 0.0);
    PrintString(320, 620, GLUT_BITMAP_TIMES_ROMAN_24, currentTime);
    #endif
}

void Timer(int value) {
    (void)value;
    #ifndef NO_GUI
    TimerData& data = TimerData::getInstance();
    if (data.updateTime(value)) {
        exit(0);
    }
    if (data.getPassedTime() > 2000) {
        ParkingLotManager& manager = ParkingLotManager::getInstance();
        manager.prepareAllFloors();
    }
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
    #ifndef NO_GUI
    glClear(GL_COLOR_BUFFER_BIT);
    TimerData& data = TimerData::getInstance();
    if (data.getPassedTime() <= 2000) {
        drawInit();
    }
    else
    {
        drawPL();
    }
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
        {"running-time", required_argument, nullptr, 't'},
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
