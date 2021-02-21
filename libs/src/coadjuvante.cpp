/**
 * @file  coadjuvante.cpp
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

#include "coadjuvante.h"

//construtor do coadjuvante
coadjuvante::coadjuvante(){

}

//destrutor do coadjuvante
coadjuvante::~coadjuvante(){

}

/** read DIP switch**/
// returns a value between 0 and 15
// retorna um valor entre 0 e 15
// devuelve un valor entre 0 y 15
int coadjuvante::readDPI(){
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

/** Random number generator **/
int coadjuvante::random_angle(){
   return rand() % (rot180Degree-rot90Degree) + rot90Degree;
}


/** setup da função coadjuvante**/
void coadjuvante::setup_coadj(){
  srand (time(NULL)); // setting random seed

    // DIP switch
  pinMode(DIP1, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP2, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP3, INPUT_PULLUP);  // DO NOT CHANGE
  pinMode(DIP4, INPUT_PULLUP);  // DO NOT CHANGE

  // OUTPUTS
  pinMode(LED, OUTPUT);         // led

}



