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

//constants
#define rot90Degree  135
#define rot150Degree 180
#define rot180Degree 200
#define reverseTime 120
#define smallReverseTime 80

//defines
#define DIP1 10
#define DIP2 11
#define DIP3 12
#define DIP4 13
#define LED 6

//variaveis globais
//timer
//#define reset_timer() ( time_ms = millis())
//#define get_timer() (millis() - time_ms) 




class Coadjuvante {
  
  public:
    //funções
    Coadjuvante();
    ~Coadjuvante(); 
    int readDIP();
    int random_angle();
    void reset_timer();
    int get_timer();
    int time_ms;
    
};


#endif