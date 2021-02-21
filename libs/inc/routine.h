/**
 * @file  Routine.h
 *
 * @brief Header file for the routines executed by the robot during each strategy
 *
 * @author Gabriel Kishida <gabriel.kishida@usp.br>
 * @author Henrique Matheus <henriquedamaralhdm@usp.br>
 * @author Lucas Guedes <guedeslucas@usp.br>
 * @author Vanderson Santos <vanderson.santos@thunderatz.org>
 *
 * @date 02/2021
 * Thunderatz Equipe de Robótica - POLI-USP
 */

#ifndef Routine_h
#define Routine_h

#include <Arduino.h>
#include <sensor.h>
#include <coadjuvante.h>
#include <motor.h>

 class Routine {
  public:
  
    Routine();

    int  turn_time;
    int  turn_angle;
    bool search_enemy_forward();
    bool search_enemy_spin();
    bool turn_left(int angle_time, int rot_vel);
    bool turn_right(int angle_time, int rot_vel);
    bool pursue();
    bool turn_random_angle(int side);
    bool reverse(int time, int vel);
    bool exit_from_line();
    bool dodge();
    bool stop_in_line();
    bool setup_routine();


    motor* motor_p;
    coadjuvante* coadjuvante_p;
 }
    
#endif