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

// Time Constants
#define rot90Degree  135
#define rot150Degree 180
#define rot180Degree 200
#define reverseTime 120
#define smallReverseTime 80

// Velocity
#define maxVel 255
#define safeVel 150
#define rotateVel 255

/*
    Class Constructer (como vamos usar isso?)
*/
Routine::Routine() {
    motor_p = new motor();
    sensor_p = new sensor();
    coadjuvante_p = new coadjuvante();
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
    rotate(0);
    return true;
}

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
    if(get_timer() < time) {
        motor_p->rotate(rot_vel);
        return false;
    }
    return true;
}

bool Routine::turn_right(int angle_time, int rot_vel) {
    if(get_timer() < time) {
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
    if(get_timer() < turnAngle) {
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
    if(get_timer() < time) {
        motor_p->forward(-vel);
        return false;
    }
    else {
        motor_p->forward(0);
        return true;
    }
}

bool Routine::exit_from_line(int reverse_time, int turn_time) {
    // Mantem ou nao?
}

bool Routine::dodge() {
    if(sensor_p->getDistSensorR() || sensor_p->getDistSensorL()) {
        if(sensor_p->getDistSensorR() && !sensor_p->getDistSensorL()) {
            motor_p->curvedMovement(maxVel,0->3,1->0);
        }
        else if(!sensor_p->getDistSensorR() && sensor_p->getDistSensorL()) {
            motor_p->curvedMovement(maxVel,1->0,0->3);
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
    if(sensor_p->isInLine_dumy()) {
        motor_p->forward(0);
        return true;
    }
    return false;
}