#include "strategy.h"

Strategy* s;

bool flagstart;
int DIP;

void setup() {
  s = new Strategy();
  flagstart = true;
}

void loop() {
  DIP = s->routine_p->coadjuvante_p->readDIP();

  while (!(s->routine_p->sensor_p->getMicroST()) ) {
    //Serial.println("Stop running");
    s->routine_p->motor_p->forward(0);
  }
  if(!flagstart) {
    flagstart = true; 
    s->routine_p->coadjuvante_p->reset_timer();
  }

  //Serial.print("case: ");
  //Serial.println(DIP);

 switch (DIP) {
    case 0:
      s->bayblade(); 
      //Serial.println("bayblade");
      break;
    case 1:
      s->flash_gordo();
      //Serial.println("flash");
      break;
    case 2:
      s->toquinho();
      break;
    default:
      s->bayblade();
      //Serial.println("flash");
      break;
  }
}