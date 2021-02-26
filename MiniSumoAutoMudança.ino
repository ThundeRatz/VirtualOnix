/**
 * @file  MiniSumoAuto.ino
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

//******************** CALMA E PARCIMONIA *******************//

//*********** Libs ***************//
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/*******PINOUT DEFINES*********/
// it is not recommended to make changes

// Constants
#define rot90Degree  135
#define rot150Degree 180
#define rot180Degree 200
#define reverseTime 120
#define smallReverseTime 80

// Velocity
#define maxVel 255
#define safeVel 150
#define rotateVel 255

// Line Detector
#define noDetection 0
#define DetectLeft  1
#define DetectRight 2
#define DetectBoth  3
 
// LED
#define LED 6 //
 
// left motor
#define pwmL 9
#define leftMotor1 7
#define leftMotor2 8
 
// right motor
#define pwmR 3
#define rightMotor1 5
#define rightMotor2 4

// DIP switch
#define DIP1 10 //
#define DIP2 11 // 
#define DIP3 12 //
#define DIP4 13 //
 
// Robocore's line sensor
#define lineL A0
#define lineR A1
#define upperLightLimit 700  //limite de 10 bits (até 1023)


// Jsumo's distance sensor
#define distL A2
#define distR A3
 
// Jsumo's micro-start
#define microST 2

//timer
#define reset_timer() (time_ms = millis())
#define get_timer() (millis() - time_ms)

/******* ENUM DEFINES *********/

// States
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

/*******PINOUT DEFINES - END*********/


/*******PUBLIC VARIABLES*******/

bool end;
int time_ms;
strategies_fsm_state_t State;
strategies_fsm_state_t lastState;
bool flagStart = false;
int turnAngle = 0;
int turnSide;
/*******PUBLIC VARIABLES - END*******/

/*******FUNCTIONS*******/
void MotorL(int pwm); // left motor
void MotorR(int pwm); // right motor
int readDIP(); // read DIP switch
bool getDistSensorL();
bool getDistSensorR();
bool getLineSensorL();
bool getlinesensorR();
void forward(int pwm);

void estrategia0();
void estrategia1();
void estrategia2();
void estrategia3();
void estrategia4();
void estrategia5();
void estrategia6();
void estrategia7();
void estrategia8();
void estrategia9();
void estrategia10();

bool IsInLine();
bool dodge();
bool search_enemy();
bool reverse();
bool IsLost();

/*******FUNCTIONS - END*******/
 
void setup() {
  
  srand (time(NULL)); // setting random seed


  /****************PINOUT CONFIG****************/
  // OUTPUTS
  pinMode(LED, OUTPUT);         // led
 
  // right motor
  pinMode(pwmR, OUTPUT);        // right motor power
  pinMode(rightMotor1, OUTPUT); // right motor dir.
  pinMode(rightMotor2, OUTPUT); // right motor dir.
 
  // left motor
  pinMode(pwmL, OUTPUT);        // left motor power
  pinMode(leftMotor1, OUTPUT);  // left motor dir.
  pinMode(leftMotor2, OUTPUT);  // left motor dir.
 
 
  // INPUTS: DO NOT CHANGE
  // DIP switch
  pinMode(DIP1, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP2, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP3, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP4, INPUT_PULLUP);  // DO NOT CHANGE
  
  // line sensor
  pinMode(lineL, INPUT); // DO NOT CHANGE
  pinMode(lineR, INPUT); // DO NOT CHANGE
 
  // distance sensor
  pinMode(distR, INPUT); // DO NOT CHANGE
  pinMode(distL, INPUT); // DO NOT CHANGE
 
  // micro-start
  pinMode(microST, INPUT); // DO NOT CHANGE
  /****************PINOUT CONFIG - END***************/
 
  /***************INITIAL CONDITIONS*****************/
  digitalWrite(LED, LOW); // LED off
  MotorL(0); // left motor stopped
  MotorR(0); // right motor stopped
  flagStart = false;
  State = INITIAL;
  lastState = INITIAL;
  
  /*************INITIAL CONDITIONS - END*************/
  
  end = false;
}

void loop() {

  while (digitalRead(microST) == LOW || end) {
    Serial.print("Stop running");
    forward(0);
  }
  if(!flagStart) {
    flagStart = true; 
    reset_timer();
  }
  
  Serial.print("Start running");

  int estrategia = readDIP();
  Serial.println("estrategia: ");
  Serial.println(estrategia);
  

  switch (estrategia) {
    case 0:
      estrategia8(); 
      break;
    case 1:
      estrategia10();
      break;
    case 2:
      estrategia2();
      break;
    case 3:
      estrategia3();
      break;
    case 4:
      estrategia4();
      break;
    case 5:
      estrategia5();
      break;
    case 6:
      estrategia6();
      break;
    case 7:
      estrategia7();
      break;
    case 8:
      estrategia8();
      break;
    case 10:
      estrategia10();
      break;
      // aqui a gente coloca mais estrategias conforme formos desenvolvendo
    default:
      estrategia8();
      break;
  }

}
 
/**LEFT MOTOR CONTROL / CONTROLE DO MOTOR ESQUERDO / CONTROL DEL MOTOR IZQUIERDO**/
// pwm = 0 -> stopped
// 0<pwm<=255 -> forward
// -255<=pwm<0 -> backward

void MotorL(int pwm){
  // leftMotor1=0 and leftMotor2=0 -> stopped
  // leftMotor1=0 and leftMotor2=1 -> moves forward
  // leftMotor1=1 and leftMotor2=0 -> moves back
  // leftMotor1=1 and leftMotor2=1 -> stopped (braked)
 
  if(pwm==0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, HIGH);
  }
  else if(pwm<0)
  {
    analogWrite(pwmL, -pwm);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
  }
  else
  {
    analogWrite(pwmL, pwm);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
  }
}
 
 
/**RIGHT MOTOR CONTROL**/
// pwm = 0 -> stopped
// 0<pwm<=255 -> forward
// -255<=pwm<0 -> backward
void MotorR(int pwm){
  // rightMotor1=0 and rightMotor2=0 -> stopped 
  // rightMotor1=0 and rightMotor2=1 -> moves forward
  // rightMotor1=1 and rightMotor2=0 -> moves back
  // rightMotor1=1 and rightMotor2=1 -> stopped (braked)

  if(pwm==0){
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, HIGH);
  }
  else if(pwm<0)
  {
    analogWrite(pwmR, -pwm);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }
  else
  {
    analogWrite(pwmR, pwm);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }
}
 
/** read DIP switch**/
// returns a value between 0 and 15
// retorna um valor entre 0 e 15
// devuelve un valor entre 0 y 15
int readDIP(){
  int n=0;
  if(digitalRead(DIP4)==HIGH){
    n=1;}
  if(digitalRead(DIP3)==HIGH){
    n|= (1<<1);}
  if(digitalRead(DIP2)==HIGH){
    n|= (1<<2);}
  if(digitalRead(DIP1)==HIGH){
    n|= (1<<3);}
  return n;
}

/** Controle dos motores **/
// Para valores positivos de "pwm", o robô rotaciona para a esquerda, Para negativos,
// ele rotaciona para a direita.
void rotate(int pwm){
  MotorR(pwm);
  MotorL(-pwm);
}

// pwm define a potência dos motores, ratioR define quanto dessa potência será transmitida
// para a roda da direita, e ratioL define quanto será transmitido para a roda da esquerda,
// fazendo assim um movimento curvilíneo.
void curvedMovement(int pwm, float ratioR, float ratioL){
  int rightMovement = int(float(pwm)*ratioR);
  int leftMovement = int(float(pwm)*ratioL);
  MotorR(rightMovement);
  MotorL(leftMovement);
}

// Para valores positivos do "pwm", o robo seguira pra frente,
// Para valores negativos, o robo seguira de re
void forward(int pwm){
  MotorR(pwm);
  MotorL(pwm);
}

/** getters dos sensores **/
bool getDistSensorR(){
  return (digitalRead(distR) == HIGH) ? true : false;
}

bool getDistSensorL(){
  return (digitalRead(distL) == HIGH) ? true : false;
}

bool getLineSensorL(){
  return (analogRead(lineL) <= upperLightLimit) ? true : false;
}

bool getLineSensorR(){
  return (analogRead(lineR) <= upperLightLimit) ? true : false;
}

/** Random number generator **/
int randomAngle(){
  return rand() % (rot180Degree-rot90Degree) + rot90Degree;
}

/**estrategias**/
//virar 90 graus para a direita, depois andar reto e virar 90 graus para esquerda
void estrategia0(){
  int time_curve_1 = rot90Degree;
  int time_straight = time_curve_1 + 100;
  int time_curve_2 = time_straight + rot90Degree;

  if (get_timer() < time_curve_1) {
    rotate(-rotateVel);
  } else if (get_timer() <  time_straight) {
    forward(maxVel);
  } else if (get_timer() < time_curve_2) {
    rotate(rotateVel);
  } else {
    end = true;
  }
}

// Estrategia para testar o sensor de linha. Seguir reto ate encontrar a linha limite do dojo e para
void estrategia1(){
  if((!getLineSensorL() && !getLineSensorR())){
    forward(maxVel);
  }
  else{
    forward(0);
  }
  
}

// Estrategia para testar o sensor de distancia
void estrategia2(){
  forward(0);
  if(getDistSensorL() && getDistSensorR()){
    digitalWrite(LED,HIGH);
  }
  else {
    digitalWrite(LED,LOW);
  }
}

// Estrategia que busca centralizar a "mira" do robô no obstáculo. Gira para o lado até 
// centralizar, Se nao encontrar nenhum lado para girar, fica parado. Ao centralizar, acende o LED
void estrategia3(){

  if(getDistSensorL() && !getDistSensorR()){
    rotate(-rotateVel);
    digitalWrite(LED,LOW);
  }
  else if(!getDistSensorL() && getDistSensorR() ){
    rotate(rotateVel);
    digitalWrite(LED,LOW);
  }
  else if(getDistSensorL() && getDistSensorR()){
    rotate(0);
    digitalWrite(LED,HIGH);
  }
  else {
    rotate(rotateVel/2);
    digitalWrite(LED,LOW);
  }

}

// Estrategia para testar o sensor de linha. Seguir reto ate encontrar a linha limite do dojo e gira para sair da borda
void estrategia4(){
  static int lastRot;
  if( getLineSensorL() && get_timer() > rot90Degree){
    forward(0);
    lastRot = rotateVel;
    reset_timer();
    digitalWrite(LED,HIGH);
  }
  else if( getLineSensorR() && get_timer() > rot90Degree){
    forward(0);
    lastRot = -rotateVel;
    reset_timer();
    digitalWrite(LED,HIGH);
  } 
  if(get_timer() < rot90Degree ){
    rotate(lastRot);
  }
  else {
    forward(maxVel);
    digitalWrite(LED,LOW);
  }
}

// Essa estrategia procura um oponente, e avanca na direcao deste. Caso pise em uma linha,
// gira 90 graus e sai.
void estrategia5() {
  static int lastRot;
  if (getLineSensorL() || getLineSensorR() || get_timer() < rot90Degree) {
    if( getLineSensorL() && get_timer() > rot90Degree){
      lastRot = rotateVel;
      reset_timer();
    }
   else if( getLineSensorR() && get_timer() > rot90Degree){
      lastRot = -rotateVel;
      reset_timer();
    } 
    if(get_timer() < rot90Degree ){
      rotate(lastRot);
    }
  }

  
  else {
    if(getDistSensorL() && !getDistSensorR()){
      rotate(-rotateVel);
      digitalWrite(LED,LOW);
    }
    else if(!getDistSensorL() && getDistSensorR() ){
      rotate(rotateVel);
      digitalWrite(LED,LOW);
    }
    else if(getDistSensorL() && getDistSensorR()){
      rotate(0);
      digitalWrite(LED,HIGH);
      forward(maxVel);
    }
    else {
      curvedMovement(safeVel, 1.0, 0.5);
      digitalWrite(LED,LOW);
    }
  }
}

//teste de tempo de rotação
void estrategia6(){
  int intervalo = 5000; //segundos entre as rotações
  int tempo1 = rot90Degree/2;
  int tempo2 = rot90Degree;
  int tempo3 = rot150Degree;
  int tempo4 = rot180Degree;
  int tempo5 = 2*rot180Degree;

  if(get_timer() < tempo1) {
    rotate(rotateVel);
  }else if (get_timer() < tempo1 + intervalo) {
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + intervalo){
    rotate(rotateVel);
  }else if (get_timer() < tempo1 + tempo2 + 2*intervalo) {
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + 2*intervalo){
    rotate(rotateVel);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + 3*intervalo){
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + tempo4 + 3*intervalo) {
    rotate(rotateVel);
  }else {
    rotate(0);
    end = true;
  } 
}

void estrategia7(){
    curvedMovement(-safeVel, 0.5, 0.25);
}

// Teste da maquina de estados
// Nessa estrategia o robo gira em seu eixo ate encontrar o inimigo e o ataca

void estrategia8(){
  switch(State){
    case INITIAL:
      State = SEARCH;
      break;
    case SEARCH:
      if(IsInLine()){
        State = ON_LINE;
      } else if(search_enemy()){
        State = PURSUE;
      }
      break;
    case PURSUE:
      forward(maxVel);
      if(IsInLine()){
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
      if (IsInLine()){
        State = ON_LINE;
      } else if (turn()){
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

/**
void estrategia9(){
    
    switch(State){
      case INITIAL:
        State = SEARCH;
        break;
      case SEARCH:
        forward(safeVel);
        if(IsInLine()){
          State = ON_LINE;
        } else if(search_enemy()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        forward(maxVel);
        if(IsInLine()){
          State = ON_LINE;
        } else if(IsLost()){
          State = LOST;
        }
        break;
        
      case LOST:
        if(IsInLine()){
          forward(0);
          State = ON_LINE;
        } else if(search_enemy()){
          State = PURSUE;
        }
        break;

      case STUCK:
        
        break;
      case ATTACK:

        break;
      case ON_LINE:
        if(routine_exitFromLine()){
          State = Search;
        } else if(search_enemy()){
          State = PURSUE;
        }
        break;
      case REVERSE:
        if (IsInLine()){
          State = ON_LINE;
        } else {
          STATE = TURN;
        }
        break;
      case TURN:
        if (IsInLine()){
          State = ON_LINE;
        } else {
          STATE = SEARCH;
        }
        break;
      default:

        break;
    }
}
**/

// Nessa estrategia o robo andara pelo campo ate encontrar o inimigo e o ataca girando quando encontra a borda do dojo
void estrategia10(){
    switch(State){
      case INITIAL:
        State = SEARCH;
        break;
      case SEARCH:
        forward(safeVel);
        if(IsInLine()){
          State = ON_LINE;
        } else if(!IsLost()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        if(IsInLine()){
          State = ON_LINE;
        } else if(routine_pursue10()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        if(IsInLine2()!= DetectBoth){
          State = TURN;
          }
        else{
          State = REVERSE;
          }
        break;
      case REVERSE:
        if(reverse10()){
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
        turnSide = IsInLine2();
      }
      lastState = State;
      reset_timer();
    }
}



// procurar inimigo
// Caso veja o inimigo com os dois sensores, ele retorna true
// Caso veja o inimigo com um dos sensores ele gira pra essa direcao
// Caso nao veja o robo ele gira pra esquerda
bool search_enemy_spin(){
  if ( !(getDistSensorR() && getDistSensorL()) ){
      if( (getDistSensorR()) && (!getDistSensorL()) ){
        rotate(-rotateVel);
      }
      else if( (!getDistSensorR()) && (getDistSensorL()) ){
        rotate(rotateVel);
      }
      else{ 
        rotate(rotateVel);
      }
      return false;
  }
  rotate(0);
  return true;
}

//procurar inimigo para a estrategia 10
// Caso veja o inimigo com os dois sensores, ele retorna true
// Caso veja o inimigo com um dos sensores ele gira pra essa direcao
// Caso nao veja o robo ele segue reto
bool search_enemy_forward(){
  if ( !(getDistSensorR() && getDistSensorL()) ){
      if( (getDistSensorR()) && (!getDistSensorL()) ){
        rotate(-rotateVel);
      }
      else if( (!getDistSensorR()) && (getDistSensorL()) ){
        rotate(rotateVel);
      }
      else{ 
        forward(maxVel);
      }
      return false;
  }
  rotate(0);
  return true;
}

// Gira o robo 180 graus para a esquerda
// O robo gira pra esquerda durante "rot180Degree" ms
// Ao terminar o giro a funcao retorna true
bool turn_left(int time, int rot_vel) {
  if(get_timer() < time) {
    rotate(rot_vel);
    return false;
  }
  return true;
}

bool turn_right(int time, int rot_vel) {
  if(get_timer() < time) {
    rotate(-rot_vel);
    return false;
  }
  return true;
}

// Gira o robo 180 graus para a esquerda (Estrategia 10)
// O robo gira pra o lado selecionado (side) durante "turnAngle" ms
// Ao terminar o giro a funcao retorna true
bool turn_random_angle(int side) {
  if(get_timer() < turnAngle) {
    if(side == DetectLeft){
      rotate(-rotateVel);
    }
    else {
      rotate(rotateVel);
    }
    return false;
  }
  return true;
}

// Rotina de perseguicao do oponente (Estrategia 10)
// Caso veja o inimigo com os dois sensores, ele segue reto
// Caso veja o inimigo com um dos sensores ele faz uma curva pra essa direcao
// Caso nao veja o robo ele retorna true
bool pursue() {
  if(!getDistSensorL() && getDistSensorR()) {
    curvedMovement(maxVel,0.5,1.0);
    return false;
  } else if (getDistSensorL() && !getDistSensorR()) {
    curvedMovement(maxVel,1.0,0.5);
    return false;
  } else if (getDistSensorL() && getDistSensorR()) {
    forward(maxVel);
    return false;
  } else {
    return true;
  }
}

// Robo anda de ré
// O robo retorna durante "reverseTime" ms na safeVel
// Ao terminar o retorno a funcao retorna true
bool reverse() {
  if(get_timer() < reverseTime) {
    forward(-safeVel);
    return false;
  }
  else {
    forward(0);
    return true;
  }
}

// Robo anda de re
// O robo retorna durante "reverseTime" ms na maxVel
// Ao terminar o retorno a funcao retorna true
bool reverse10() {
  if(get_timer() < smallReverseTime) {
    forward(-maxVel);
    return false;
  }
  else {
    forward(0);
    return true;
  }
}

// Detecta se o robo esta sobre as linhas laterais do robo
// Caso algum sensor detecte a linha, o robo para e a funcao retorna true
// Se nenhum sensor detectar a linha, retorna false
bool IsInLine_dumy(){
  if (getLineSensorL() || getLineSensorR()){
    //forward(0);
    return true;
  } 
  return false;
}

// Detecta se o robo perdeu o inimigo de vista
// Caso algum sensor detecte o oponente, a funcao retorna false
// Se nenhum sensor detectar o oponente, retorna true
bool IsLost(){
  return !(getDistSensorL() || getDistSensorR());
}

/**
bool exitFromLine(){
  static int lastRot;
  if( getLineSensorL() && get_timer() > 1000){
    lastRot = rotateVel;
    reset_timer();
  }
  else if( getLineSensorR() && get_timer() > 1000){
    lastRot = -rotateVel;
    reset_timer();
  } 
  if(get_timer() < 1000 ){
    rotate(lastRot);
    return false;
  }
  else {
    return true;
  }
}
**/
//**************** FUNCOES EXTRAS **************//

int IsInLine_smart(){
  if (getLineSensorL() && getLineSensorR()){
    forward(0);
    return DetectBoth;
  } else if(getLineSensorL()){
    forward(0);
    return DetectLeft;
  } else if(getLineSensorR()){
    forward(0);
    return DetectRight;
  } else{
    return noDetection;
  }
}

bool dodge(){
  int time_curve_1 = rot90Degree;
  int time_straight = time_curve_1 + 250;
  int time_curve_2 = time_straight + rot90Degree;

    if (get_timer() < time_curve_1) {
      rotate(-rotateVel);
    } else if (get_timer() <  time_straight) {
      forward(maxVel);
    } else if (get_timer() < time_curve_2) {
      rotate(rotateVel);
    } else {
      return true;
    }
    return false;
}