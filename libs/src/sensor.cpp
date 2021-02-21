#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor(){
    pinMode(lineL, INPUT);
    pinMode(lineR, INPUT);

    pinMode(distR, INPUT);
    pinMode(distL, INPUT);
}

//getters
bool Sensor::getDistSensorL(){
    return (digitalRead(distL) == HIGH) ? true : false;
}

bool Sensor::getDistSensorR(){
    return (digitalRead(distR) == HIGH) ? true : false;
}

bool Sensor::getLineSensorL(){
  return (analogRead(lineL) <= upperLightLimit) ? true : false;
}

bool Sensor::getLineSensorR(){
  return (analogRead(lineR) <= upperLightLimit) ? true : false;
}

bool Sensor::getMicroST(){
    return (digitalRead(microST) == HIGH) ? true: false;
}

//true se nenhum dos sensores de distância acham simultaneamente
bool Sensor::isLost() {
    return !(this->getDistSensorL() || this->getDistSensorR());
}

//true se algum sensor detecta a linha
bool Sensor::isInLine_Dumy(){
    if (this->getLineSensorL() || this->getLineSensorR()){
    //forward(0);
        return true;
    } 
    return false;
}

//retorna o lado que o(s) sensor(es) detecta(m) a linha
int Sensor::isInLine_Smart(){
    if (this->getLineSensorL() && this->getLineSensorR()){
        forward(0);
        return DetectBoth;
    } else if(this->getLineSensorL()){
        forward(0);
        return DetectLeft;
    } else if(this->getLineSensorR()){
        forward(0);
        return DetectRight;
    } else{
        return noDetection;
    }
};
