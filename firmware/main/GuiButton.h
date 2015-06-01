/* 
* GuiButton.h
*
* Created: 5/23/2015 9:07:13 PM
* Author: skobls
*/


#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "Widget.h"
#include "ButtonFSM.h"

class GuiButton: public Widget
{
//variables
protected:
    ButtonFSM btn;
    uint16_t bg_color_on,  bg_color_off;
    uint16_t color;
    char* label;
    EventHandler onPress, onRelease; // TODO: onLongPress, onRepeatitions;
  #ifdef BUTTON_FSM_LONGPRESS
    EventHandler onLongPress, onLongRelease, onEnteringReleasedState;
   #ifdef BUTTON_FSM_REPEATITIONS
    EventHandler onRepeatition;
   #endif // BUTTON_FSM_REPEATITIONS
  #endif // BUTTON_FSM_LONGPRESS
//functions
public:
	GuiButton(uint16_t _left
	         ,uint16_t _top
	         ,uint16_t _width
             ,uint16_t _height
	         ,char* _label
             ,EventHandler _on_press = EMPTY_EventHandler
             ,EventHandler _on_release = EMPTY_EventHandler
          #ifdef BUTTON_FSM_LONGPRESS
             ,EventHandler _on_long_press = EMPTY_EventHandler
             ,EventHandler _on_long_release = EMPTY_EventHandler
            #ifdef BUTTON_FSM_REPEATITIONS
             ,EventHandler _on_repeatition = EMPTY_EventHandler
            #endif // BUTTON_FSM_REPEATITIONS
             ,EventHandler _on_entering_released_state = EMPTY_EventHandler
          #endif // BUTTON_FSM_LONGPRESS
             ,uint16_t _color_released = RGB(0,255,0)
             ,uint16_t _color_pressed = RGB(0,0,255)); // TODO: add `#ifdef` stuff
    void refresh();
    void onTouchpanelEvent(touchpanelEvent_t &e);
    void setColor(uint16_t _color);
    void hide(uint16_t fill_color = RGB(255,255,255));
protected:
private:
    //static GuiButton* pBtn;
    //static void wrapOnPress(void);
    //static void wrapOnRelease(void);
}; //GuiButton

#endif //__GUIBUTTON_H__
