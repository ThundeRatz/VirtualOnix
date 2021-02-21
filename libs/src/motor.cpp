/**
 * @file  motor.cpp
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

#include "motor.h"

//construtor dos motor
motor::motor(){

}

//destrutor dos motor
motor::~motor(){
  
}

/**RIGHT MOTOR CONTROL**/
// pwm = 0 -> stopped
// 0<pwm<=255 -> forward
// -255<=pwm<0 -> backward
// rightMotor1=0 and rightMotor2=0 -> stopped 
// rightMotor1=0 and rightMotor2=1 -> moves forward
// rightMotor1=1 and rightMotor2=0 -> moves back
// rightMotor1=1 and rightMotor2=1 -> stopped (braked)
void motor::MotorR(int pwm){
  if(pwm==0){
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, HIGH);
  }
  else if(pwm<0)
  {
    analogWrite(pwmR, -pwm);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }
  else
  {
    analogWrite(pwmR, pwm);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }
}

/**LEFT MOTOR CONTROL / CONTROLE DO MOTOR ESQUERDO / CONTROL DEL MOTOR IZQUIERDO**/
// pwm = 0 -> stopped
// 0<pwm<=255 -> forward
// -255<=pwm<0 -> backward
// leftMotor1=0 and leftMotor2=0 -> stopped
// leftMotor1=0 and leftMotor2=1 -> moves forward
// leftMotor1=1 and leftMotor2=0 -> moves back
// leftMotor1=1 and leftMotor2=1 -> stopped (braked)
void motor::MotorL(int pwm){
  if(pwm==0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, HIGH);
  }
  else if(pwm<0)
  {
    analogWrite(pwmL, -pwm);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
  }
  else
  {
    analogWrite(pwmL, pwm);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
  }
}

// Para valores positivos do "pwm", o robo seguira pra frente,
// Para valores negativos, o robo seguira de re
void motor::forward(int pwm){
  MotorR(pwm);
  MotorL(pwm);
}

// pwm define a potência dos motor, ratioR define quanto dessa potência será transmitida
// para a roda da direita, e ratioL define quanto será transmitido para a roda da esquerda,
// fazendo assim um movimento curvilíneo.
void motor::curvedMovement(int pwm, float ratioR, float ratioL){
  MotorR( int(float(pwm)*ratioR) );
  MotorL( int(float(pwm)*ratioL) );
}

// Para valores positivos de "pwm", o robô rotaciona para a esquerda, Para negativos, ele rotaciona para a direita.
void motor::rotate(int pwm){
  MotorR(pwm);
  MotorL(-pwm);
}

//setup dos motor
void motor::setup_motors(){
  /****************PINOUT CONFIG****************/
  // right motor
  pinMode(pwmR, OUTPUT);        // right motor power
  pinMode(rightMotor1, OUTPUT); // right motor dir.
  pinMode(rightMotor2, OUTPUT); // right motor dir.
 
  // left motor
  pinMode(pwmL, OUTPUT);        // left motor power
  pinMode(leftMotor1, OUTPUT);  // left motor dir.
  pinMode(leftMotor2, OUTPUT);  // left motor dir.
  
  /****************PINOUT CONFIG - END***************/

  /***************INITIAL CONDITIONS*****************/
  MotorL(0); // left motor stopped
  MotorR(0); // right motor stopped
  /*************INITIAL CONDITIONS - END*************/
}

