/**
 * @file  MiniSumoAuto.ino
 *
 * @brief Virtual version of onix
 *
 *
 * @author Gabriel Kishida <gabriel.kishida@usp.br>
 * @author Henrique Matheus <henriquedamaralhdm@usp.br>
 * @author Lucas Guedes <guedeslucas@usp.br>
 * @author Vanderson Santos <vanderson.santos@thunderatz.org>
 *
 * @date 02/2021
 */

#ifndef Sensor_h
#define Sensor_h

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


class Sensor{

  public:
      Sensor();
      ~Sensor();
      bool getDistSensorL();
      bool getDistSensorR();
    
      bool getLineSensorL();
      bool getLineSensorR();

      bool getMicroST();
      bool isLost();

      bool isInLine_Dumy();
      int isInLine_Smart();
};

#endif