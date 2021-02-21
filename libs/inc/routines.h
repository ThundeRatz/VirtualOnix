#ifndef NodeMotorDriver_h
#define NodeMotorDriver_h

#include "motores.h"
#include "coadjuvante.h"
 class Routines {
  public:
    Routine();
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
    motores.rotate();

    motores* motores_p;
    coadjuvante* coadjuvante_p;
}
#endif