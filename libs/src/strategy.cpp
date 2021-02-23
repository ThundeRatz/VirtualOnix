#include "strategy.h"

// Teste da maquina de estados
// Nessa estrategia o robo gira em seu eixo ate encontrar o inimigo e o ataca

Strategy::Strategy() {
    routine_p = new Routine();
    turnSide = noDetection;
}

void Strategy::standby() {
  routine_p->stop();
}

void Strategy::bayblade(){

  switch(State){
    case INITIAL:
      State = SEARCH;
      break;
    case SEARCH:
      if(routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if(routine_p->search_enemy_spin()){
        State = PURSUE;
      }
      break;
    case PURSUE:
      routine_p->motor_p->forward(maxVel);
      if(routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if(routine_p->sensor_p->isLost()){
        State = SEARCH;
      }
      break;
    case ON_LINE:
      State = REVERSE;
      break;
    case REVERSE:
      if(routine_p->reverse(reverseTime, safeVel)){
        State = TURN;
      }
      break;

    case TURN:
      if (routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if (routine_p->turn_right(rot90Degree,rotateVel)){
        State = SEARCH;
      }
      break;
        
    default:
      break;
  }
  if (State != lastState) {
    routine_p->coadjuvante_p->reset_timer();
    lastState = State;
  }


}


// Nessa estrategia o robo andara pelo campo ate encontrar o inimigo e o ataca girando quando encontra a borda do dojo
void Strategy::flash_gordo(){
    switch(State){
      case INITIAL:
        State = SEARCH;
        break;
      case SEARCH:
        routine_p->motor_p->forward(safeVel);
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if(!(routine_p->sensor_p->isLost())) {
          State = PURSUE;
        }
        break;
      case PURSUE:
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if(routine_p->pursue()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        if(routine_p->sensor_p->isInLine_Smart()!= DetectBoth){
          State = TURN;
          }
        else{
          State = REVERSE;
          }
        break;
      case REVERSE:
        if(routine_p->reverse(reverseTime,safeVel)){
          State = TURN;
        }
        break;
      case TURN:
        if(turnSide == DetectBoth){
          State = REVERSE;
        }
        else if(routine_p->turn_random_angle(turnSide)){
          State = SEARCH;
        }
        break;
        
      default:
        break;
    }
    if (State != lastState) {
      if (State == TURN) {
        routine_p->turn_angle = routine_p->coadjuvante_p->random_angle();
        turnSide = routine_p->sensor_p->isInLine_Smart();
      }
      lastState = State;
      routine_p->coadjuvante_p->reset_timer();
    }
}