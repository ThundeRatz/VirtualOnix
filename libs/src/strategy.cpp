#include "../inc/strategy.h"

// Teste da maquina de estados
// Nessa estrategia o robo gira em seu eixo ate encontrar o inimigo e o ataca

void Strategy::bayblade(){
  switch(State){
    case INITIAL:
      State = SEARCH;
      break;
    case SEARCH:
      if(sensor_p->IsInLine_dumy()){
        State = ON_LINE;
      } else if(routine_p->search_enemy_spin()){
        State = PURSUE;
      }
      break;
    case PURSUE:
      routine_p->forward(maxVel);
      if(sensor_p->IsInLine_dumy()){
        State = ON_LINE;
      } else if(sensor_p->IsLost()){
        State = SEARCH;
      }
      break;
    case ON_LINE:
      State = REVERSE;
      break;
    case REVERSE:
      if(routine_p->reverse()){
        State = TURN;
      }
      break;

    case TURN:
      if (sensor_p->IsInLine_dumy()){
        State = ON_LINE;
      } else if (routine_p->turn_right()){
        State = SEARCH;
      }
      break;
        
    default:
      break;
  }
  if (State != lastState) {
    coadjuvante_p->reset_timer();
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
        routine_p->forward(safeVel);
        if(routine_p->IsInLine_smart()){
          State = ON_LINE;
        } else if(!(routine_p->IsLost()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        if(sensor_p->IsInLine_smart()){
          State = ON_LINE;
        } else if(routine_p->pursue()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        if(sensor_p->IsInLine_smart()!= DetectBoth){
          State = TURN;
          }
        else{
          State = REVERSE;
          }
        break;
      case REVERSE:
        if(routines_p->reverse()){
          State = TURN;
        }
        break;
      case TURN:
        if(routine_p->turnSide == DetectBoth){
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
        routine_p->turnAngle = coadjuvante_p->randomAngle();
        routine_p->turnSide = sensor_p->IsInLine_smart();
      }
      lastState = State;
      coadjuvante_p->reset_timer();
    }
}