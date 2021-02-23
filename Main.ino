#include "strategy.h"

Strategy* s;

bool flagstart;
int DIP;

void setup() {
  s = new Strategy();
  Serial.begin(9600);
  flagstart = true;
}

void loop() {
  DIP = s->routine_p->coadjuvante_p->readDIP();

  while (!(s->routine_p->sensor_p->getMicroST()) ) {
    Serial.print("Stop running");
    s->routine_p->motor_p->forward(0);
  }
  if(!flagstart) {
    flagstart = true; 
    s->routine_p->coadjuvante_p->reset_timer();
  }


  Serial.println(DIP);
  
  switch (DIP) {
    case 0:
      s->bayblade(); 
      break;
    case 2:
      s->flash_gordo();
      break;
    default:
      s->flash_gordo();
      break;
  }
}