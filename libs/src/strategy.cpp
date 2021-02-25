#include "strategy.h"

// Teste da maquina de estados
// Nessa estrategia o robo gira em seu eixo ate encontrar o inimigo e o ataca

Strategy::Strategy() {
    routine_p = new Routine();
    turnSide = noDetection;
    State = INITIAL;
    lastState = INITIAL;
}

Strategy::~Strategy() {
    delete routine_p;
}

void Strategy::standby() {
  routine_p->stop();
}

void Strategy::bayblade(){
  //Serial.println("dentro do bayblade");
  switch(State){
    case INITIAL:
      State = SEARCH;
      //Serial.println("INITIAL");
      break;
    case SEARCH:
      //Serial.println("SEARCH");
      if(routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if(routine_p->search_enemy_spin()){
        State = PURSUE;
      }
      break;
    case PURSUE:
      //Serial.println("PURSUE");
      if(routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if(routine_p->sensor_p->isLost()){
        State = SEARCH;
      }
      routine_p->motor_p->forward(maxVel);
      break;
    case ON_LINE:
      State = REVERSE;
      //Serial.println("ON_LINE");
      break;
    case REVERSE:
      //Serial.println("REVERSE");
      if(routine_p->reverse(reverseTime, safeVel)){
        State = TURN;
      }
      break;

    case TURN:
      //Serial.println("TURN");
      if (routine_p->sensor_p->isInLine_Dumy()){
        State = ON_LINE;
      } else if (routine_p->turn_right(rot90Degree,rotateVel)){
        State = SEARCH;
      }
      break;
        
    default:
      //Serial.println("default");
      break;
  }
  if (State != lastState) {
    routine_p->coadjuvante_p->reset_timer();
    lastState = State;
  }


}

void Strategy::flash_gordo(){
  //Serial.println("dentro do flash gordo");
    switch(State){
      case INITIAL:
        //Serial.println("INITIAL");
        State = SEARCH;
        break;
      case SEARCH:
        //Serial.println("SEARCH");
        routine_p->motor_p->forward(safeVel);
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if(!(routine_p->sensor_p->isLost())) {
          State = PURSUE;
        }
        break;
      case PURSUE:
        //Serial.println("PURSUE");
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if(routine_p->pursue()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        //Serial.println("ON_LINE");
        routine_p->stop();
        State = REVERSE;
        break;
      case REVERSE:
        //Serial.println("REVERSE");
        if(routine_p->reverse(reverseTime,safeVel)){
          State = TURN;
        }
        break;
      case TURN: 
        //Serial.println("TURN");
        if(turnSide == DetectBoth){
          State = REVERSE;
        }
        else if(routine_p->turn_random_angle(turnSide)){
          State = SEARCH;
        }
        break;
        
      default:
        //Serial.println("DEFAULT");
        State = INITIAL;
        break;
    }
    if (State != lastState) {
      routine_p->turn_angle = routine_p->coadjuvante_p->random_angle();
      turnSide = routine_p->sensor_p->isInLine_Smart();
      lastState = State;
      routine_p->coadjuvante_p->reset_timer();
    }
}

void Strategy::toquinho(){
  //Serial.println("dentro do flash gordo");
    switch(State){
      case INITIAL:
        //Serial.println("INITIAL");
        State = SEARCH;
        break;
      case SEARCH:
        //Serial.println("SEARCH");
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if( (!(routine_p->sensor_p->isLost()))  ) {
          State = PURSUE;
        } else if(routine_p->wait(waitTime)) {
          State = ATTACK;
        } 
        break;
      case ATTACK:
        //Serial.println("SEARCH");
        if(routine_p->sensor_p->isInLine_Smart()){
          State = ON_LINE;
        } else if(!(routine_p->sensor_p->isLost())) {
          State = PURSUE;
        } else if(routine_p->advance(advanceTime,maxVel)) {
          State = SEARCH;
        } 
        break;
      case PURSUE:
        //Serial.println("PURSUE");
        if(routine_p->sensor_p->isInLine_Smart()) {
          State = ON_LINE;
        } else if(routine_p->sensor_p->isLost()) {
          State = SEARCH;
        } else if(routine_p->center_enemy()) {
          routine_p->motor_p->forward(maxVel);
        }
        break;
      case ON_LINE:
        //Serial.println("ON_LINE");
        routine_p->stop();
        State = REVERSE;
        break;
      case REVERSE:
        //Serial.println("REVERSE");
        if(routine_p->reverse(reverseTime,safeVel)) {
          State = TURN;
        }
        break;
      case TURN:
        //Serial.println("TURN");
        if(turnSide == DetectBoth){
          State = REVERSE;
        }
        else if(routine_p->turn_random_angle(turnSide)) {
          State = SEARCH;
        }
        break;
        
      default:
        //Serial.println("DEFAULT");
        State = INITIAL;
        break;
    }
    if (State != lastState) {
      routine_p->turn_angle = routine_p->coadjuvante_p->random_angle();
      turnSide = routine_p->sensor_p->isInLine_Smart();
      lastState = State;
      routine_p->coadjuvante_p->reset_timer();
    }
}