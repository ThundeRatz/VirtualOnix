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

//constants
#define rot90Degree  135
#define rot150Degree 180
#define rot180Degree 200
#define reverseTime 120
#define smallReverseTime 80

class motor{
  public:
    motor();
    ~motor();

    void rotate(int pwm);
    void curvedMovement();
    void MotorR(int pwm);
    void MotorL(int pwm);
    void forward(int pwm);
    void setup_motors();
}

#endif