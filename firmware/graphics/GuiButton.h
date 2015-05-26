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

class GuiButton:Widget
{
//variables
protected:
    ButtonFSM btn;
    uint16_t bg_color_on,  bg_color_off;
    uint16_t color;
    char* label;
    EventHandler onPress, onRelease; // TODO: onLongPress, onRepeatitions;
//functions
public:
	GuiButton(uint16_t _top,
	          uint16_t _left,
	          uint16_t _height,
	          uint16_t _width,
              char* _label,
              EventHandler _on_press = EMPTY_EventHandler,
              EventHandler _on_release = EMPTY_EventHandler,
              uint16_t _color_released = RGB(0,255,0),
              uint16_t _color_pressed = RGB(0,0,255)); // TODO: add `#ifdef` stuff
    void refresh();
    void onTouchpanelEvent(touchpanelEvent_t e);
    void setColor(uint16_t _color);
protected:
private:
    static void wrapOnPress(void);
    static void wrapOnRelease(void);
}; //GuiButton

#endif //__GUIBUTTON_H__
