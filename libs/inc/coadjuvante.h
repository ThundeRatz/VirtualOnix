/**
 * @file  coadjuvante.h
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

#include <Arduino.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifndef coadjuvante
#define coadjuvante


//defines
#define DIP1 10
#define DIP2 11
#define DIP3 12
#define DIP4 13
#define LED 6

//timer
#define reset_timer() (time_ms = millis())
#define get_timer() (millis() - time_ms)


class Coadjuvante {
  
  public:
    //variaveis
    int time_ms;
    int turnAngle = 0;
    
    //funções
    Coadjuvante();
    ~Coadjuvante(); 
    int readDPI();
    int random_angle();
    
}


#endif