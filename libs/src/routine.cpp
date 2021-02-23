 /**
 * @file  routines->h
 *
 * @brief Source file for the routines executed by the robot during each strategy
 *
 * @author Gabriel Kishida <gabriel.kishida@usp.br>
 * @author Henrique Matheus <henriquedamaralhdm@usp.br>
 * @author Lucas Guedes <guedeslucas@usp.br>
 * @author Vanderson Santos <vanderson.santos@thunderatz.org>
 *
 * @date 02/2021
 * Thunderatz Equipe de Robótica - POLI-USP
 */

#include "routine.h"

/*
    Class Constructer (como vamos usar isso?)
*/
Routine::Routine() {
    motor_p = new Motor();
    sensor_p = new Sensor();
    coadjuvante_p = new Coadjuvante();
}

Routine::~Routine(){
    delete motor_p;
    delete sensor_p;
    delete coadjuvante_p;
}

bool Routine::search_enemy_forward() {
    if ( !(sensor_p->getDistSensorR() && sensor_p->getDistSensorL()) ) {
        if( (sensor_p->getDistSensorR()) && (!sensor_p->getDistSensorL()) ) {
            motor_p->rotate(-rotateVel);
        }
        else if( (!sensor_p->getDistSensorR()) && (sensor_p->getDistSensorL()) ){
            motor_p->rotate(rotateVel);
        }
        else { 
            motor_p->forward(maxVel);
        }
        return false;
    }
    motor_p->rotate(0);
    return true;
}
// *El tê*
// t
bool Routine::search_enemy_spin() {
    if ( !(sensor_p->getDistSensorR() && sensor_p->getDistSensorL()) ) {
        if( (sensor_p->getDistSensorR()) && (!sensor_p->getDistSensorL()) ) {
            motor_p->rotate(-rotateVel);
        }
        else if( (!sensor_p->getDistSensorR()) && (sensor_p->getDistSensorL()) ) {
            motor_p->rotate(rotateVel);
        }
        else { 
            motor_p->rotate(rotateVel);
        }
        return false;
    }
    motor_p->rotate(0);
    return true;
}

bool Routine::turn_left(int angle_time, int rot_vel) {
    if(coadjuvante_p->get_timer() < angle_time) {
        motor_p->rotate(rot_vel);
        return false;
    }
    return true;
}

bool Routine::turn_right(int angle_time, int rot_vel) {
    if(coadjuvante_p->get_timer() < angle_time) {
        motor_p->rotate(-rot_vel);
        return false;
    }
    return true;
}

bool Routine::pursue() {
    if(!sensor_p->getDistSensorL() && sensor_p->getDistSensorR()) {
        motor_p->curvedMovement(maxVel,0.5,1.0);
        return false;
    } else if (sensor_p->getDistSensorL() && !sensor_p->getDistSensorR()) {
        motor_p->curvedMovement(maxVel,1.0,0.5);
        return false;
    } else if (sensor_p->getDistSensorL() && sensor_p->getDistSensorR()) {
        motor_p->forward(maxVel);
        return false;
    } else {
        return true;
    }
}

bool Routine::turn_random_angle(int side) {
    if(coadjuvante_p->get_timer() < turn_angle) {
        if(side == DetectLeft) {
            motor_p->rotate(-rotateVel);
        }
        else {
            motor_p->rotate(rotateVel);
        }
        return false;
    }
    return true;
}

bool Routine::reverse(int time, int vel) {
    if(coadjuvante_p->get_timer() < time) {
        motor_p->forward(-vel);
        return false;
    }
    else {
        motor_p->forward(0);
        return true;
    }
}

bool Routine::dodge() {
    if(sensor_p->getDistSensorR() || sensor_p->getDistSensorL()) {
        if(sensor_p->getDistSensorR() && !sensor_p->getDistSensorL()) {
            motor_p->curvedMovement(maxVel,0.3,1.0);
        }
        else if(!sensor_p->getDistSensorR() && sensor_p->getDistSensorL()) {
            motor_p->curvedMovement(maxVel,1.0,0.3);
        }
        else {
            motor_p->forward(maxVel);
        }
        return false;
    } else {
        return true;
    }
}

bool Routine::stop_in_line() {
    if(sensor_p->isInLine_Dumy()) {
        motor_p->forward(0);
        return true;
    }
    return false;
}

void Routine::stop() {
  motor_p->forward(0);
}