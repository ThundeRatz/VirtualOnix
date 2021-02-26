/**
 * @file  motor.h
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


#include <Arduino.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifndef motor
#define motor


// right motor
#define pwmR 3
#define rightMotor1 5
#define rightMotor2 4

// left motor
#define pwmL 9
#define leftMotor1 7
#define leftMotor2 8

class Motor{
  public:
    Motor();
    ~Motor();

    void rotate(int pwm);
    void curvedMovement(int pwm, float ratioR, float ratioL);
    void MotorR(int pwm);
    void MotorL(int pwm);
    void forward(int pwm);
};

#endif