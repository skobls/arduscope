//
//
//

#include "bar.h"
#include "MI0283QT2.h"
extern MI0283QT2 Display; // should be instantiated elsewhere, most likely -- in main.ino


BarClass::BarClass(uint16_t x_pos,uint16_t y_pos,uint16_t width)
{
	_x_pos = x_pos;
    _y_pos = y_pos;
    _width = width;
    _height = 130; // 1+128+1
    state = 0;
    border_color = 0x0000;
    bg_color = 0xF000;
    fill_color= 0x00FF;
    //refresh();
}

void BarClass::refresh(void)
{
	Display.drawRect(_x_pos,_y_pos,_width,_height,border_color);
    if (0 != state)
    {
        Display.fillRect(_x_pos+1,_y_pos+1,_width-2,128-state,bg_color);
    }
    if (state < 128)
    {
        Display.fillRect(_x_pos+1,_y_pos+1+128-state,_width-2,state,fill_color);
    }
}

void BarClass::setState(uint8_t newState)
{
	state = newState>>1;
    refresh();
}
