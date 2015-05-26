/*
 * ButtonFSM.h
 * 
 * This class implements a Finite State Machine (FSM) of a button, 
 * including debounce and event handlers
 *
 * Created: 5/23/2015 7:23:17 PM
 *  Author: skobls
 */ 
//TODO: add documentation

#ifndef BUTTONFSM_H_
#define BUTTONFSM_H_
#include <stdint.h>

typedef void (*EventHandler)(void);
#define EMPTY_EventHandler ((EventHandler)(0))
#define TIMER_T uint8_t // Type of the .timer field

#define BTN_DEBOUNCE_TIMEOUT 5
#define BTN_LONGPRESS_TIMEOUT 50
#define BTN_REPEATITIONS_TIMEOUT 10

class ButtonFSM {
 private:
        uint8_t state;
        TIMER_T timer;
        EventHandler onPress;
        EventHandler onRelease;
    // to enable the functionality, define the keys below for the whole build
    #ifdef BUTTON_FSM_LONGPRESS 
        EventHandler onLongPress; 
      #ifdef BUTTON_FSM_REPEATITIONS
        EventHandler onRepeatition;
      #endif // BUTTON_FSM_REPEATITIONS
    #endif // BUTTON_FSM_LONGPRESS
 public:
    ButtonFSM(   EventHandler _on_press
                ,EventHandler _on_release = EMPTY_EventHandler
            #ifdef BUTTON_FSM_LONGPRESS
                ,EventHandler _on_long_press = EMPTY_EventHandler
              #ifdef BUTTON_FSM_REPEATITIONS
                ,EventHandler _on_repeatition= EMPTY_EventHandler
              #endif // BUTTON_FSM_REPEATITIONS
            #endif // BUTTON_FSM_LONGPRESS
                );

    //   You call this function and it does any further work:
    // decides if the button's state changes, and generates any necessary events.
    // It is generally recommended to call this function each 2 .. 10 ms // TODO: check the time limits
    void FSM(uint8_t data,
             TIMER_T debounce_duration = BTN_DEBOUNCE_TIMEOUT
        #ifdef BUTTON_FSM_LONGPRESS
            ,TIMER_T longPress_duration = BTN_LONGPRESS_TIMEOUT
          #ifdef BUTTON_FSM_REPEATITIONS
            ,TIMER_T repeatitions_duraiton = BTN_REPEATITIONS_TIMEOUT
          #endif // BUTTON_FSM_REPEATITIONS
        #endif // BUTTON_FSM_LONGPRESS
        ); 
};



#endif /* BUTTONFSM_H_ */