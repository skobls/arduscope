/* 
* GuiButton.cpp
*
* Created: 5/23/2015 9:07:13 PM
* Author: skobls
*/


#include "GuiButton.h"
//   We shall assume that somewhere (probably in the `main.ino` file)
// exists an instance of `MI0283QT2` class, called `Display`.
extern MI0283QT2 Display;   // TODO: consider replacing with `GraphicsLib.h`

//---------------------------------------------------------------------
//      wraparounds for event handlers
//---------------------------------------------------------------------
GuiButton* pBtn;
//inline void GuiButton::wrapOnPress(void)
//{
    //pBtn->setColor(pBtn->bg_color_on);
    ////if (pBtn->onPress != EMPTY_EventHandler )
    ////{
        ////pBtn->onPress();
    ////} 
    //CALL_IF_NONEMPTY(pBtn->onPress);
//}
//inline void GuiButton::wrapOnRelease(void)
//{
    //pBtn->setColor(pBtn->bg_color_off);
    ////if (pBtn->onRelease != EMPTY_EventHandler)
    ////{
        ////pBtn->onRelease();
    ////}
  //#ifndef BUTTON_FSM_LONGPRESS
    //CALL_IF_NONEMPTY(pBtn->onRelease);
  //#else
    //CALL_IF_NONEMPTY(pBtn->onEnteringReleasedState);
  //#endif
//}

//---------------------------------------------------------------------
// constructor
GuiButton::GuiButton(uint16_t _left
                    ,uint16_t _top
                    ,uint16_t _width
                    ,uint16_t _height
                    ,char*    _label
                    ,EventHandler _on_press /*= EMPTY_EventHandler*/
                    ,EventHandler _on_release /*= EMPTY_EventHandler*/
                #ifdef BUTTON_FSM_LONGPRESS
                    ,EventHandler _on_long_press /*= EMPTY_EventHandler*/ 
                    ,EventHandler _on_long_release /*= EMPTY_EventHandler*/ 
                  #ifdef BUTTON_FSM_REPEATITIONS
                    ,EventHandler _on_repeatition /*= EMPTY_EventHandler*/ 
                  #endif // BUTTON_FSM_REPEATITIONS
                    ,EventHandler _on_entering_released_state /*= EMPTY_EventHandler*/
                #endif // BUTTON_FSM_LONGPRESS
                    ,uint16_t _color_released
                    ,uint16_t _color_pressed):
            Widget(_left,_top,_width,_height), // pass some parameters to the base class constructor
            btn( // pass some parameters to the internal variable's constructor
                 [](void) -> void{pBtn->setColor(pBtn->bg_color_on); CALL_IF_NONEMPTY(pBtn->onPress);}
              #ifndef BUTTON_FSM_LONGPRESS
                ,[](void) -> void{pBtn->setColor(pBtn->bg_color_off);CALL_IF_NONEMPTY(pBtn->onRelease);}
              #else
                ,_on_release
                ,_on_long_press
                ,_on_long_release
                ,[](void) -> void{pBtn->setColor(pBtn->bg_color_off);CALL_IF_NONEMPTY(pBtn->onEnteringReleasedState);}
               #ifdef BUTTON_FSM_REPEATITIONS
                ,_on_repeatition 
               #endif // BUTTON_FSM_REPEATITIONS
              #endif // BUTTON_FSM_LONGPRESS
                )
{
    bg_color_on = _color_pressed;
    bg_color_off = _color_released;
	color = bg_color_off; //TODO: consider making `color` a pointer
    label = _label;
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

void GuiButton::onTouchpanelEvent(touchpanelEvent_t &e)
{
    //uint16_t dx = e.x-left;
    //uint16_t dy = e.y-top;
    //char tmp[15];
    //sprintf(tmp,"%u,%u,%u",dx,dy,e.pressure);
    //int len = strlen(tmp);
    //Display.fillRect(3+len*8,230,(15-len)*8,8,0x0000);
    //Display.drawText(3,230,tmp,0xFFFF,0x0000,1);
	//if ((dx < width)     // if the event happened inside this widget
      //&&(dy < height)
      //&&(e.pressure>20))
	//{
        pBtn = this;
        btn.FSM( (((e.x-left) < width)     // if the event happened inside this widget
                &&((e.y-top) < height)
                &&(e.pressure>20))?1:0);
	//}
}

void GuiButton::setColor(uint16_t _color)
{
	color = _color;
    refresh();
}

void GuiButton::refresh()
{
	Display.drawRect(left,top,width,height,RGB(0,0,0));
    Display.fillRect(left+1,top+1,width-2,height-2,color);
    Display.drawText(left + 1 + (width-8*strlen(label)-2)/2,// 
                     top  + height/2-4,
                     label,color^0xFFFF,color,1);
}

void GuiButton::hide(uint16_t fill_color/* = RGB(255,255,255)*/)
{ Display.fillRect(left,top,width,height,fill_color);}