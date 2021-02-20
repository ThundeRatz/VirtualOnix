 /**
 * @file  routines.h
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

}

bool Routine::search_enemy_forward() {
    if ( !(sensor.getDistSensorR() && sensor.getDistSensorL()) ) {
        if( (sensor.getDistSensorR()) && (!sensor.getDistSensorL()) ) {
            motor.rotate(-rotateVel);
        }
        else if( (!sensor.getDistSensorR()) && (sensor.getDistSensorL()) ){
            motor.rotate(rotateVel);
        }
        else { 
            motor.forward(maxVel);
        }
        return false;
    }
    rotate(0);
    return true;
}

bool Routine::search_enemy_spin() {
    if ( !(sensor.getDistSensorR() && sensor.getDistSensorL()) ) {
        if( (sensor.getDistSensorR()) && (!sensor.getDistSensorL()) ) {
            motor.rotate(-rotateVel);
        }
        else if( (!sensor.getDistSensorR()) && (sensor.getDistSensorL()) ) {
            motor.rotate(rotateVel);
        }
        else { 
            motor.rotate(rotateVel);
        }
        return false;
    }
    motor.rotate(0);
    return true;
}

bool Routine::turn_left(int angle_time, int rot_vel) {
    if(get_timer() < time) {
        motor.rotate(rot_vel);
        return false;
    }
    return true;
}

bool Routine::turn_right(int angle_time, int rot_vel) {
    if(get_timer() < time) {
        motor.rotate(-rot_vel);
        return false;
    }
    return true;
}

bool Routine::pursue() {
    if(!sensor.getDistSensorL() && sensor.getDistSensorR()) {
        motor.curvedMovement(maxVel,0.5,1.0);
        return false;
    } else if (sensor.getDistSensorL() && !sensor.getDistSensorR()) {
        motor.curvedMovement(maxVel,1.0,0.5);
        return false;
    } else if (sensor.getDistSensorL() && sensor.getDistSensorR()) {
        motor.forward(maxVel);
        return false;
    } else {
        return true;
    }
}

bool Routine::turn_random_angle(int side) {
    if(get_timer() < turnAngle) {
        if(side == DetectLeft) {
            motor.rotate(-rotateVel);
        }
        else {
            motor.rotate(rotateVel);
        }
        return false;
    }
    return true;
}

bool Routine::reverse(int time, int vel) {
    if(get_timer() < time) {
        motor.forward(-vel);
        return false;
    }
    else {
        motor.forward(0);
        return true;
    }
}

bool Routine::exit_from_line(int reverse_time, int turn_time) {
    // Mantem ou nao?
}

bool Routine::dodge() {
    if(sensor.getDistSensorR() || sensor.getDistSensorL()) {
        if(sensor.getDistSensorR() && !sensor.getDistSensorL()) {
            motor.curvedMovement(maxVel,0.3,1.0);
        }
        else if(!sensor.getDistSensorR() && sensor.getDistSensorL()) {
            motor.curvedMovement(maxVel,1.0,0.3);
        }
        else {
            motor.forward(maxVel);
        }
        return false;
    } else {
        return true;
    }
}

bool Routine::stop_in_line() {
    if(sensor.isInLine_dumy()) {
        motor.forward(0);
        return true;
    }
    return false;
}

bool Routine::setup_routine() {
    sensor.setup_sensor();
    motor.setup_motor();
    coadjuvante.setup_coad();

}