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
inline void GuiButton::wrapOnPress(void)
{
    pBtn->setColor(pBtn->bg_color_on);
    if (pBtn->onPress != EMPTY_EventHandler )
    {
        pBtn->onPress();
    } 
}
inline void GuiButton::wrapOnRelease(void)
{
    pBtn->setColor(pBtn->bg_color_off);
    if (pBtn->onRelease != EMPTY_EventHandler)
    {
        pBtn->onRelease();
    }
}

//---------------------------------------------------------------------
// constructor
GuiButton::GuiButton(uint16_t _top, 
                     uint16_t _left, 
                     uint16_t _height, 
                     uint16_t _width, 
                     char*    _label,
                     EventHandler _on_press /*= EMPTY_EventHandler*/,
                     EventHandler _on_release /*= EMPTY_EventHandler*/, 
                     uint16_t _color_released,
                     uint16_t _color_pressed):
            Widget(_top,_left,_height,_width),
            btn(wrapOnPress,wrapOnRelease)
{
    bg_color_on = _color_pressed;
    bg_color_off = _color_released;
	color = bg_color_off; //TODO: consider making `color` a pointer
    label = _label;
    onPress = _on_press;
    onRelease = _on_release;
}

void GuiButton::onTouchpanelEvent(touchpanelEvent_t e)
{
    uint16_t dx = e.x-left;
    uint16_t dy = e.y-top;
    char tmp[15];
    sprintf(tmp,"%u,%u,%u",dx,dy,e.pressure);
    int len = strlen(tmp);
    Display.fillRect(3+len*8,230,(15-len)*8,8,0x0000);
    Display.drawText(3,230,tmp,0xFFFF,0x0000,1);
	if ((dx < width)     // if the event happened inside this widget
      &&(dy < height))
	{
        pBtn = this;
        btn.FSM(e.pressure>20);
	}
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

