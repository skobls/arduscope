/*
 * ButtonFSM.h
 * 
 * This class implements a Finite State Machine (FSM) of a button, 
 * including debounce and event handlers
 * 
 * Conditional compilation is provided: 
 * -- the `BUTTON_FSM_LONGPRESS` symbol, if defined, enables the events 
 *    `onLongPress`, `onLongRelease` and `onEnteringReleasedState`
 * -- the `BUTTON_FSM_REPEATITIONS` symbol, if defined, enables the event
 *    `onRepeatition`
 * -- timings may be either hard-coded (and code size respectively reduced)
 *    or be passed as parameters into the `FSM` method for the sake of higher flexibility, 
 *    everything depends on whether the symbol `BUTTON_SOFTWARE_TIMINGS` is defined
 *
 * More detailed description will be hopefully provided at the wiki:
 * https://github.com/skobls/arduscope/wiki
 *
 * Created: 5/23/2015 7:23:17 PM
 *  Author: skobls
 */ 
//TODO: add documentation

#ifndef BUTTONFSM_H_
#define BUTTONFSM_H_
#include <stdint.h>

//#define BUTTON_FSM_LONGPRESS
//#define BUTTON_FSM_REPEATITIONS
//#define BUTTON_SOFTWARE_TIMINGS

typedef void (*EventHandler)(void); // Pointer to a function with no arguments and no returned value
#define EMPTY_EventHandler ((EventHandler)(0)) // If you want to tell that an event doesn't require any action, use this macro
#define CALL_IF_NONEMPTY(x) do {if (x != EMPTY_EventHandler) {x();}} while(0)
#ifndef TIMER_T 
  #define TIMER_T uint8_t // Type of the .timer field; you can redefine it by a global preprocessor symbol
#endif // TIMER_T

#define BTN_DEBOUNCE_TIMEOUT 5
#define BTN_LONGPRESS_TIMEOUT 50
#define BTN_REPEATITIONS_TIMEOUT 10



class ButtonFSM {
 private:
        uint8_t state;
        TIMER_T timer;
        EventHandler onPress;
        EventHandler onRelease;
    // to enable the functionality, define the keys mentioned below (in this header or for the whole build)
    #ifdef BUTTON_FSM_LONGPRESS 
        EventHandler onLongPress; 
        EventHandler onLongRelease;
        // This handler will be useful if there are some identical operations to be done for both `Release` and `LongRelease` events
        EventHandler onEnteringReleasedState; 
      #ifdef BUTTON_FSM_REPEATITIONS
        EventHandler onRepeatition;
      #endif // BUTTON_FSM_REPEATITIONS
    #endif // BUTTON_FSM_LONGPRESS
 public:
    ButtonFSM(   EventHandler _on_press
                ,EventHandler _on_release = EMPTY_EventHandler
            #ifdef BUTTON_FSM_LONGPRESS
                ,EventHandler _on_long_press = EMPTY_EventHandler
                ,EventHandler _on_long_release = EMPTY_EventHandler
                ,EventHandler _on_entering_released_state = EMPTY_EventHandler
              #ifdef BUTTON_FSM_REPEATITIONS
                ,EventHandler _on_repeatition = EMPTY_EventHandler
              #endif // BUTTON_FSM_REPEATITIONS
            #endif // BUTTON_FSM_LONGPRESS
                );

    //   You call this function and it does any further work:
    // decides if the button's state changes, and generates any necessary events.
    // It is generally recommended to call this function each 2 .. 10 ms // TODO: check the time limits
    void FSM(uint8_t data
        #ifdef BUTTON_SOFTWARE_TIMINGS
            ,TIMER_T debounce_duration = BTN_DEBOUNCE_TIMEOUT
         #ifdef BUTTON_FSM_LONGPRESS
            ,TIMER_T longPress_duration = BTN_LONGPRESS_TIMEOUT
          #ifdef BUTTON_FSM_REPEATITIONS
            ,TIMER_T repeatitions_duraiton = BTN_REPEATITIONS_TIMEOUT
          #endif // BUTTON_FSM_REPEATITIONS
         #endif // BUTTON_FSM_LONGPRESS
        #endif // BUTTON_SOFTWARE_TIMINGS
        ); 
};

enum AIN_flags : uint8_t {
	ain_ch0 = 1,
	ain_ch1 = 2,
	ain_ch2 = 4
};

#endif /* BUTTONFSM_H_ */