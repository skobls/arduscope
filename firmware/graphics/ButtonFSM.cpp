/*
 * ButtonFSM.cpp
 *
 * Created: 5/23/2015 8:07:58 PM
 *  Author: skobls
 */ 

// WARNING BUTTON_FSM_LONGPRESS and BUTTON_FSM_REPEATITIONS are not implemented completely!!!!

#include "ButtonFSM.h"

//----------------------------------------------------------------------------------------
enum ButtonFSM_states {
    BtnFSM_released = 0,
    BtnFSM_towardsPress = 1,
    BtnFSM_pressed = 2,
    BtnFSM_towardsReleased = 3
  #ifdef BUTTON_FSM_LONGPRESS
    , BtnFSM_long_pressed
  #endif // BUTTON_FSM_LONGPRESS
};
//----------------------------------------------------------------------------------------
// constructor
ButtonFSM::ButtonFSM(EventHandler _on_press
                    ,EventHandler _on_release
              #ifdef BUTTON_FSM_LONGPRESS
                    ,EventHandler _on_long_press
                #ifdef BUTTON_FSM_REPEATITIONS
                    ,EventHandler _on_repeatition
                #endif // BUTTON_FSM_REPEATITIONS
              #endif // BUTTON_FSM_LONGPRESS
                    ){
    state = BtnFSM_released;
    timer = 0;
    onPress = _on_press;
    onRelease = _on_release;
  #ifdef BUTTON_FSM_LONGPRESS
    onLongPress = _on_long_press;
   #ifdef BUTTON_FSM_REPEATITIONS
    onRepeatition = _on_repeatition;
   #endif // BUTTON_FSM_REPEATITIONS
  #endif // BUTTON_FSM_LONGPRESS
}
//----------------------------------------------------------------------------------------
void ButtonFSM::FSM(uint8_t data,
                    TIMER_T debounce_duration /*= BTN_DEBOUNCE_TIMEOUT*/
                #ifdef BUTTON_FSM_LONGPRESS
                   ,TIMER_T longPress_duration /*= BTN_LONGPRESS_TIMEOUT*/
                 #ifdef BUTTON_FSM_REPEATITIONS
                   ,TIMER_T repeatitions_duraiton /*= BTN_REPEATITIONS_TIMEOUT*/
                 #endif // BUTTON_FSM_REPEATITIONS
                #endif // BUTTON_FSM_LONGPRESS
                    )
{
    switch (state)
    {
        case BtnFSM_released:
            if (data != 0)
            {   state = BtnFSM_towardsPress;
                timer = debounce_duration;   }
            break;
        case BtnFSM_towardsPress:
            if (data !=0)
            {
                if (0 == timer)
                {
                    state = BtnFSM_pressed;
                    if (onPress != EMPTY_EventHandler)
                    {   onPress();  }
                } 
                else
                {   timer--;    }
            } else {
                state = BtnFSM_released;
            }
            break;
        case BtnFSM_pressed:
            if (0 == data) // Master Yoda notation
            {   state = BtnFSM_towardsReleased;
                timer = debounce_duration;   }
            break;
        case BtnFSM_towardsReleased:
            if (0 == data)
            {
                if (0 == timer)
                {
                    state = BtnFSM_released;
                    if (onRelease != EMPTY_EventHandler)
                    {   onRelease();  }
                }
                else
                {   timer--;    }
            } else {
                state = BtnFSM_pressed;
            }
    }
}