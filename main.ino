/*******PINOUT DEFINES*********/
// it is not recommended to make changes
// nao e recomendado que se faca alteracoes
// no se recomienda hacer cambios
 
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
 
// Jsumo's distance sensor
#define distL A2
#define distR A3
 
// Jsumo's micro-start
#define microST 2


/*******PINOUT DEFINES - END*********/
 
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

}
 
void loop() {

  while (digitalRead(microST) == LOW) {
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
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
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
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
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
  return (digitalRead(getDistSensorR) == HIGH) ? true : false;
}

bool getDistSensorL(){
  return (digitalRead(getDistSensorL) == HIGH) ? true : false;
}

bool getLineSensorL(){
  return (digitalRead(lineL) == HIGH) ? false : true;
}

bool getLineSensorR(){
  return (digitalRead(lineR) == HIGH) ? false : true;
}



/**estrategias**/
void estrategia0(){
  //virar 90 graus para a direita, e depois andar reto
  static bool jaGirei = false;
  delay(1000); //delay em microsegundos
   
}

// Estrategia para testar o sensor de linha. Seguir reto ate encontrar a linha limite do dojo e para
void estrategia1(){
  
  return (getLineSensorL() || getLineSensorR()) ? forward(0) : forward(255); 
  
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
    rotate(-40);
    digitalWrite(LED,LOW);
  }
  else if(!getDistSensorL() && getDistSensorR() ){
    rotate(40);
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
  int pwm = 225;
  if( getLineSensorL() ){
    rotate(pwm);
    delay(1000);
  }
  else if( getLineSensorR() ){
    rotate(-pwm);
    delay(1000);
  } 
  else{
    forward(pwm);
  }
  
}