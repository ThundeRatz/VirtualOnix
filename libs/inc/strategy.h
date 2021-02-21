/**
 * @file  strategy.h
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

#ifndef strategy
#define strategy

#include <sensor.h>
#include <routine.h>
#include <coadjuvante.h>

class strategy {
  Strategy(); 
  
  public:
    typedef enum strategies_fsm_state {
      INITIAL,
      SEARCH,
      PURSUE,
      LOST,
      STUCK,
      ATTACK,
      ON_LINE,
      REVERSE,
      TURN,
    } strategies_fsm_state_t;

    strategies_fsm_state_t State;
    strategies_fsm_state_t lastState;

    void bayblade();
    void flash_gordo();

    routine* routine_p;
    sensor* sensor_p;
    coadjuvante* coadjuvante_p;
 
}

//PUBLIC FUNCTIONS

Strategy(){
};


#endif'