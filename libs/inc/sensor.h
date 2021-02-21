#ifndef Sensor_h
#define Sensor_h

class Sensor{

public:
    Sensor();
    bool getDistSensorL();
    bool getDistSensorR();
    
    bool getLineSensorL();
    bool getLineSensorR();

    bool getMicroST();
    bool isLost();

    bool isInLine_Dumy();
    int isInLine_Smart();
};

/** PINS DEFINITIONS */

#define distL A2
#define distR A3

#define lineL A0
#define lineR A1

#define noDetection 0
#define DetectLeft 1
#define DetectRight 2
#define DetectBoth 3

#define MicroST 2

#define upperLightLimit 700

#endif