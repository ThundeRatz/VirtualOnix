#ifndef coadjuvante
#define coadjuvante

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class coadjuvante {
  coadjuvante(); 
  
  public:
    int readDPI();
    void setup_coadj();
    int random_angle();
    
    int time_ms;
    int turnAngle = 0;
 
}

//defines

#define DIP1 10
#define DIP2 11
#define DIP3 12
#define DIP4 13

#define LED 6

//timer
#define reset_timer() (time_ms = millis())
#define get_timer() (millis() - time_ms)

//PUBLIC FUNCTIONS

coadjuvante(){
};

int coadjuvante::readDPI();

void coadjuvante::setup_coadj();

int coadjuvante::random_angle();






#endif