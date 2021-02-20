#include "../inc/strategy.h"

#include "../inc/routines.h"

// Teste da maquina de estados
// Nessa estrategia o robo gira em seu eixo ate encontrar o inimigo e o ataca

void nodeStrategy::bayblade(){
  switch(State){
    case INITIAL:
      State = SEARCH;
      break;
    case SEARCH:
      if(IsInLine_dumy()){
        State = ON_LINE;
      } else if(search_enemy_spin()){
        State = PURSUE;
      }
      break;
    case PURSUE:
      forward(maxVel);
      if(IsInLine_dumy()){
        State = ON_LINE;
      } else if(IsLost()){
        State = SEARCH;
      }
      break;
    case ON_LINE:
      State = REVERSE;
      break;
    case REVERSE:
      if(reverse()){
        State = TURN;
      }
      break;

    case TURN:
      if (IsInLine_dumy()){
        State = ON_LINE;
      } else if (turn_right()){
        State = SEARCH;
      }
      break;
        
    default:
      break;
  }
  if (State != lastState) {
    reset_timer();
    lastState = State;
  }
}


// Nessa estrategia o robo andara pelo campo ate encontrar o inimigo e o ataca girando quando encontra a borda do dojo
void nodeStrategy::flash_gordo(){
    switch(State){
      case INITIAL:
        State = SEARCH;
        break;
      case SEARCH:
        forward(safeVel);
        if(IsInLine_smart()){
          State = ON_LINE;
        } else if(!IsLost()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        if(IsInLine_smart()){
          State = ON_LINE;
        } else if(pursue()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        if(IsInLine_smart()!= DetectBoth){
          State = TURN;
          }
        else{
          State = REVERSE;
          }
        break;
      case REVERSE:
        if(reverse()){
          State = TURN;
        }
        break;
      case TURN:
        if(turnSide == DetectBoth){
          State = REVERSE;
        }
        else if(turn_random_angle(turnSide)){
          State = SEARCH;
        }
        break;
        
      default:
        break;
    }
    if (State != lastState) {
      if (State == TURN) {
        turnAngle = randomAngle();
        turnSide = IsInLine_smart();
      }
      lastState = State;
      reset_timer();
    }
}