/*******PINOUT DEFINES*********/
// it is not recommended to make changes
// nao e recomendado que se faca alteracoes
// no se recomienda hacer cambios

//******************** CALMA E PARCIMONIA *******************//

// Constants
#define rot90Degree  70
#define rot150Degree 116
#define rot180Degree 140
#define reverseTime 100

// Velocity
#define maxVel 255
#define safeVel 150
#define rotateVel 40

// Line Detector
#define noDetection 0
#define DetectLeft  1
#define DetectRight 2
#define DetectBoth  3
 
// LED
#define LED 6
 
// left motor
#define pwmL 9
#define leftMotor1 7
#define leftMotor2 8
 
// right motor
#define pwmR 3
#define rightMotor1 5
#define rightMotor2 4
 
// DIP switch
#define DIP1 10
#define DIP2 11
#define DIP3 12
#define DIP4 13
 
// Robocore's line sensor
#define lineL A0
#define lineR A1
#define upperLightLimit 600  //limite de 10 bits (até 1023)


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
/*******PUBLIC VARIABLES - END*******/

/*******FUNCTIONS*******/
void MotorL(int pwm); // left motor / motor esquerdo / motor izquierdo
void MotorR(int pwm); // right motor / motor direito / motor derecho
int readDIP(); // read DIP switch / ler chave DIP / leer el interruptor DIP
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


bool rotine_IsInLine();
bool rotine_dodge();
bool rotine_search_enemy();
bool rotine_reverse();
bool IsLost();
/*******FUNCTIONS - END*******/
 
void setup() {
 
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
 
 
  // INPUTS: DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  // DIP switch
  pinMode(DIP1, INPUT_PULLUP);  // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  pinMode(DIP2, INPUT_PULLUP);  // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  pinMode(DIP3, INPUT_PULLUP);  // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  pinMode(DIP4, INPUT_PULLUP);  // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  
  // line sensor
  pinMode(lineL, INPUT); // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  pinMode(lineR, INPUT); // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
 
  // distance sensor
  pinMode(distR, INPUT); // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  pinMode(distL, INPUT); // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
 
  // micro-start
  pinMode(microST, INPUT); // DO NOT CHANGE / NAO MUDAR / NO CAMBIAR
  /****************PINOUT CONFIG - END***************/
 
  /***************INITIAL CONDITIONS*****************/
  digitalWrite(LED, LOW); // LED off / LED desligado / LED apagado 
  MotorL(0); // left motor stopped / motor esquerdo parado / motor izquierdo parado 
  MotorR(0); // right motor stopped / motor direito parado / motor derecho parado
  /*************INITIAL CONDITIONS - END*************/

  end = false;
}
 
void loop() {

  while (digitalRead(microST) == LOW || end) {
    Serial.print("Stop running");
  }
  
  Serial.print("Start running");

  int estrategia = readDIP();
  Serial.println("estrategia: ");
  Serial.println(estrategia);
  

  switch (estrategia) {
    case 0:
      estrategia0();
      break;
    case 1:
      estrategia1();
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
    case 8:
      estrategia8();
      // aqui a gente coloca mais estrategias conforme formos desenvolvendo
    default:
      estrategia0();
  }

}
 
/**LEFT MOTOR CONTROL / CONTROLE DO MOTOR ESQUERDO / CONTROL DEL MOTOR IZQUIERDO**/
// pwm = 0 -> stopped / parado / parado
// 0<pwm<=255 -> forward / para frente / seguir adelante
// -255<=pwm<0 -> backward / para tras / seguir espalda

void MotorL(int pwm){
  // leftMotor1=0 and leftMotor2=0 -> stopped / parado / parado 
  // leftMotor1=0 and leftMotor2=1 -> moves forward / avanca / avanzar
  // leftMotor1=1 and leftMotor2=0 -> moves back / recua / retrocede
  // leftMotor1=1 and leftMotor2=1 -> stopped (braked) / parado (travado) / parado (frenado)
 
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
 
 
/**RIGHT MOTOR CONTROL / CONTROLE DO MOTOR DIREITO / CONTROL DEL MOTOR DERECHO**/
// pwm = 0 -> stopped / parado / parado
// 0<pwm<=255 -> forward / frente / adelante
// -255<=pwm<0 -> backward / tras / espalda
void MotorR(int pwm){
  // rightMotor1=0 and rightMotor2=0 -> stopped / parado / parado 
  // rightMotor1=0 and rightMotor2=1 -> moves forward / avanca / avanzar
  // rightMotor1=1 and rightMotor2=0 -> moves back / recua / retrocede
  // rightMotor1=1 and rightMotor2=1 -> stopped (braked) / parado (travado) / parado (frenado)

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
 
/** read DIP switch / ler chave DIP / leer el interruptor DIP **/
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
  return (analogRead(lineL) >= upperLightLimit) ? true : false;
}

bool getLineSensorR(){
  return (analogRead(lineR) >= upperLightLimit) ? true : false;
}

/**estrategias**/
//virar 90 graus para a direita, e depois andar reto
void estrategia0(){
  int time_curve_1 = rot90Degree;
  int time_straight = time_curve_1 + 250;
  int time_curve_2 = time_straight + rot90Degree;

  if (get_timer() < time_curve_1) {
    rotate(-safeVel);
  } else if (get_timer() <  time_straight) {
    forward(safeVel);
  } else if (get_timer() < time_curve_2) {
    rotate(safeVel);
  } else {
    end = true;
  }
}

// Estrategia para testar o sensor de linha. Seguir reto ate encontrar a linha limite do dojo e para
void estrategia1(){
  (getLineSensorL() || getLineSensorR()) ? forward(0) : forward(safeVel); 
}

// Estrategia para testar o sensor de distancia
void estrategia2(){
  MotorL(0);
  MotorR(0);
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
    rotate(0);
    digitalWrite(LED,LOW);
  }

}

// Estrategia para testar o sensor de linha. Seguir reto ate encontrar a linha limite do dojo e gira para sair da borda
void estrategia4(){
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
  }
  else {
    rotate(0);
    forward(maxVel);
  }
}

// Essa estrategia procura um oponente, e avanca na direcao deste. Caso pise em uma linha,
// gira 90 graus e sai.
void estrategia5() {
  static int lastRot;
  if (getLineSensorL() || getDistSensorR() || get_timer() < rot90Degree) {
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
      forward(safeVel);
    }
    else {
      curvedMovement(safeVel, 1.0, 0.4);
      digitalWrite(LED,LOW);
    }
  } 
}

//teste de tempo de rotação
void estrategia6(){
  int intervalo = 5000; //segundos entre as rotações
  int tempo1 = 20;
  int tempo2 = 50;
  int tempo3 = 70;
  int tempo4 = 100;
  int tempo5 = 130;




  if(get_timer() < tempo1) {
    rotate(safeVel);
  }else if (get_timer() < tempo1 + intervalo) {
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + intervalo){
    rotate(safeVel);
  }else if (get_timer() < tempo1 + tempo2 + 2*intervalo) {
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + 2*intervalo){
    rotate(safeVel);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + 3*intervalo){
    rotate(0);
  }else if (get_timer() < tempo1 + tempo2 + tempo3 + tempo4 + 3*intervalo) {
    rotate(safeVel);
  }else {
    rotate(0);
    end = true;
  } 
}

void estrategia7(){
    curvedMovement(-safeVel, 0.5, 0.25);
}

// Teste da maquina de estados
void estrategia8(){
    switch(State){
      case INITIAL:
        delay(5000); // Espera 5 seg apos o inicio
        State = SEARCH;
        break;
      case SEARCH:
        if(rotine_IsInLine()){
          State = ON_LINE;
        } else if(rotine_search_enemy()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        forward(maxVel);
        if(rotine_IsInLine()){
          State = ON_LINE;
        } else if(IsLost()){
          State = SEARCH;
        }
        break;
      case ON_LINE:
        State = REVERSE;
        break;
      case REVERSE:
        if(rotine_reverse()){
          State = TURN;
        }
        break;

      case TURN:
        if (rotine_IsInLine()){
          State = ON_LINE;
        } else if (rotine_turn()){
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
        delay(5000); // Espera 5 seg apos o inicio
        State = SEARCH;
        break;
      case SEARCH:
        forward(safeVel);
        if(rotine_IsInLine()){
          State = ON_LINE;
        } else if(rotine_search_enemy()){
          State = PURSUE;
        }
        break;
      case PURSUE:
        forward(maxVel);
        if(rotine_IsInLine()){
          State = ON_LINE;
        } else if(IsLost()){
          State = LOST;
        }
        break;
        
      case LOST:
        if(rotine_IsInLine()){
          forward(0);
          State = ON_LINE;
        } else if(rotine_search_enemy()){
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
        } else if(rotine_search_enemy()){
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
//procurar inimigo
bool rotine_search_enemy(){
  if (!getDistSensorR() || !getDistSensorL()){
      rotate(maxVel);
      if( (getDistSensorR()) && (!getDistSensorL()) ){
        rotate(safeVel);
      }
      if( (!getDistSensorR()) && (getDistSensorL()) ){
        rotate(-safeVel);
      }
      return false;
  }
  rotate(0);
  return true;
}

bool rotine_turn() {
  if(get_timer() < rot180Degree) {
    rotate(safeVel);
    return false;
  }
  return true;
}



bool rotine_reverse() {
  if(get_timer() < reverseTime) {
    forward(-safeVel);
    return false;
  }
  else {
    forward(0);
    return true;
  }
}


bool rotine_dodge(){
  int time_curve_1 = rot90Degree;
  int time_straight = time_curve_1 + 250;
  int time_curve_2 = time_straight + rot90Degree;

    if (get_timer() < time_curve_1) {
      rotate(-maxVel);
    } else if (get_timer() <  time_straight) {
      forward(maxVel);
    } else if (get_timer() < time_curve_2) {
      rotate(maxVel);
    } else {
      return true;
    }
    return false;
}

bool rotine_IsInLine(){
  if (getLineSensorL() || getLineSensorR()){
    forward(0);
  } 
  return (getLineSensorL() || getLineSensorR());
}

bool IsLost(){
  return !(getDistSensorL() || getDistSensorR());
}

/**
bool routine_exitFromLine(){
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
int rotine_IsInLine2(){
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
    return DetectBoth;
  }
}