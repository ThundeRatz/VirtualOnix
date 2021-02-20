#ifndef nodeStrategy_h
#define nodeStrategy_h

class nodeStrategy {
  Strategy(); 
  
  public:
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

    strategies_fsm_state_t State;
    strategies_fsm_state_t lastState;

    void bayblade();
    void flash_gordo();
 
}

//PUBLIC FUNCTIONS

Strategy(){
};


#endif