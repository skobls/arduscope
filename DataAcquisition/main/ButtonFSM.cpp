/*
 * ButtonFSM.cpp
 *
 * Created: 5/23/2015 8:07:58 PM
 *  Author: skobls
 */ 
 
#include "ButtonFSM.h"



//----------------------------------------------------------------------------------------
enum ButtonFSM_states {
  #ifdef BUTTON_FSM_LONGPRESS
    BtnFSM_EnteringReleasedState,
  #endif // BUTTON_FSM_LONGPRESS
    BtnFSM_Released,
    BtnFSM_Released_towards_Pressed,
    BtnFSM_Pressed,
    BtnFSM_Pressed_towards_Released
  #ifdef BUTTON_FSM_LONGPRESS
    , BtnFSM_LongPressed
    , BtnFSM_LongPressed_towards_Released
  #endif // BUTTON_FSM_LONGPRESS
};
//----------------------------------------------------------------------------------------
// constructor
ButtonFSM::ButtonFSM(EventHandler _on_press 
                    ,EventHandler _on_release /*= EMPTY_EventHandler*/
              #ifdef BUTTON_FSM_LONGPRESS
                    ,EventHandler _on_long_press /*= EMPTY_EventHandler*/
                    ,EventHandler _on_long_release /*= EMPTY_EventHandler*/
                    ,EventHandler _on_entering_released_state /*= EMPTY_EventHandler*/
                #ifdef BUTTON_FSM_REPEATITIONS
                    ,EventHandler _on_repeatition /*= EMPTY_EventHandler*/
                #endif // BUTTON_FSM_REPEATITIONS
              #endif // BUTTON_FSM_LONGPRESS
                    ){
    state = BtnFSM_Released;
    timer = 0;
    onPress = _on_press;
    onRelease = _on_release;
  #ifdef BUTTON_FSM_LONGPRESS
    onLongPress = _on_long_press;
    onLongRelease = _on_long_release;
    onEnteringReleasedState = _on_entering_released_state;
   #ifdef BUTTON_FSM_REPEATITIONS
    onRepeatition = _on_repeatition;
   #endif // BUTTON_FSM_REPEATITIONS
  #endif // BUTTON_FSM_LONGPRESS
}
//----------------------------------------------------------------------------------------
void ButtonFSM::FSM(uint8_t data
                #ifdef BUTTON_SOFTWARE_TIMINGS
                   ,TIMER_T debounce_duration /*= BTN_DEBOUNCE_TIMEOUT*/
                 #ifdef BUTTON_FSM_LONGPRESS
                   ,TIMER_T longPress_duration /*= BTN_LONGPRESS_TIMEOUT*/
                  #ifdef BUTTON_FSM_REPEATITIONS
                   ,TIMER_T repeatitions_duraiton /*= BTN_REPEATITIONS_TIMEOUT*/
                  #endif // BUTTON_FSM_REPEATITIONS
                 #endif // BUTTON_FSM_LONGPRESS
                #endif // BUTTON_SOFTWARE_TIMINGS
                    )
{
    switch (state)
    {
      #ifdef BUTTON_FSM_LONGPRESS
        case BtnFSM_EnteringReleasedState:
            //if (onEnteringReleasedState != EMPTY_EventHandler)
            //{   onEnteringReleasedState();  }
            CALL_IF_NONEMPTY(onEnteringReleasedState);
            state = BtnFSM_Released;
            // NOTE: the `break;` statement is omitted intentionally
      #endif // BUTTON_FSM_LONGPRESS
        //------------------------------------------------------
        case BtnFSM_Released:
            if (data != 0)
            {   state = BtnFSM_Released_towards_Pressed;
                timer = 
                    #ifdef BUTTON_SOFTWARE_TIMINGS
                        debounce_duration;   
                    #else
                        BTN_DEBOUNCE_TIMEOUT;
                    #endif // BUTTON_SOFTWARE_TIMINGS
            }
            break;
        //------------------------------------------------------
        case BtnFSM_Released_towards_Pressed:
            if (data !=0)
            {
                if (0 == timer)
                {
                    state = BtnFSM_Pressed;
                    //if (onPress != EMPTY_EventHandler)
                    //{   onPress();  }
                    CALL_IF_NONEMPTY(onPress);
                  #ifdef BUTTON_FSM_LONGPRESS
                    timer = 
                        #ifdef BUTTON_SOFTWARE_TIMINGS
                            longPress_duration;
                        #else
                            BTN_LONGPRESS_TIMEOUT;
                        #endif // BUTTON_SOFTWARE_TIMINGS
                  #endif // BUTTON_FSM_LONGPRESS
                } 
                else
                {   timer--;    }
            } else {
                state = BtnFSM_Released;
            }
            break;
        //-----------------------------------------------------
        case BtnFSM_Pressed:
            if (0 == data) // Master Yoda notation
            {   state = BtnFSM_Pressed_towards_Released;
                timer =
                    #ifdef BUTTON_SOFTWARE_TIMINGS
                        debounce_duration;
                    #else
                        BTN_DEBOUNCE_TIMEOUT;
                    #endif // BUTTON_SOFTWARE_TIMINGS     
            }
          #ifdef BUTTON_FSM_LONGPRESS
            else{
                if (0 == timer)
                {
                    state = BtnFSM_LongPressed;
                    //if (onLongPress != EMPTY_EventHandler)
                    //{   onLongPress();  }
                    CALL_IF_NONEMPTY(onLongPress);
                    timer = 
                        #ifdef BUTTON_SOFTWARE_TIMINGS
                            longPress_duration;
                        #else
                            BTN_LONGPRESS_TIMEOUT;
                        #endif // BUTTON_SOFTWARE_TIMINGS
                }
                else
                {   timer--;    }
            }
          #endif // BUTTON_FSM_LONGPRESS
            break;
        //----------------------------------------------------
        case BtnFSM_Pressed_towards_Released:
            if (0 == data)
            {
                if (0 == timer)
                {
                    state = 
                        #ifdef BUTTON_FSM_LONGPRESS
                            BtnFSM_EnteringReleasedState;
                        #else
                            BtnFSM_Released;
                        #endif // BUTTON_FSM_LONGPRESS
                    //if (onRelease != EMPTY_EventHandler)
                    //{   onRelease();  }
                    CALL_IF_NONEMPTY(onRelease);
                }
                else
                {   timer--;    }
            } else {
                state = BtnFSM_Pressed;
            }
            break;
      #ifdef BUTTON_FSM_LONGPRESS
        //------------------------------------------------------
        case BtnFSM_LongPressed:
            if (0 == data) // Master Yoda notation
            {   state = BtnFSM_LongPressed_towards_Released;
                timer =
                    #ifdef BUTTON_SOFTWARE_TIMINGS
                        debounce_duration;
                    #else
                        BTN_DEBOUNCE_TIMEOUT;
                    #endif // BUTTON_SOFTWARE_TIMINGS

            }
          #ifdef BUTTON_FSM_REPEATITIONS
            else{
                if (0 == timer)
                {
                    //if (onLongPress != EMPTY_EventHandler)
                    //{   onLongPress();  }
                    CALL_IF_NONEMPTY(onLongPress); // TODO: `onRepeatitions`???
                    timer =
                        #ifdef BUTTON_SOFTWARE_TIMINGS
                            longPress_duration;
                        #else
                            BTN_LONGPRESS_TIMEOUT;
                        #endif // BUTTON_SOFTWARE_TIMINGS
                }
                else
                {   timer--;    }
            }
          #endif // BUTTON_FSM_REPEATITIONS
            break;
        //------------------------------------------------------------------------------
        case BtnFSM_LongPressed_towards_Released:
            if (0 == data)
            {
                if (0 == timer)
                {
                    state = 
                        #ifdef BUTTON_FSM_LONGPRESS
                            BtnFSM_EnteringReleasedState;
                        #else
                            BtnFSM_Released;
                        #endif // BUTTON_FSM_LONGPRESS
                    //if (onRelease != EMPTY_EventHandler)
                    //{   onRelease();  }
                    CALL_IF_NONEMPTY(onLongRelease);
                }
                else
                {   timer--;    }
            } else {
                state = BtnFSM_LongPressed;
            }
            break;
      #endif // BUTTON_FSM_LONGPRESS
    }
}