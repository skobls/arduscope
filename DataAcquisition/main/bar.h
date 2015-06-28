// bar.h

#ifndef _BAR_h
#define _BAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class BarClass
{
 public:
	//BarClass(void);
    //BarClass(x_pos,y_pos);
    BarClass(uint16_t x_pos,uint16_t y_pos,uint16_t width); // height is fixed to 128 pixels for now

    void setState(uint8_t newState);
    void refresh(void);

 private:
    uint16_t _x_pos, _y_pos, _width, _height;
    uint8_t state;
    uint16_t border_color,bg_color,fill_color;
};

#endif

