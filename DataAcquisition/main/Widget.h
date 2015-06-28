// Widget.h

#ifndef _WIDGET_h
#define _WIDGET_h

#include <stdint.h>
#include <MI0283QT2.h>      // TODO: consider replacing with `GraphicsLib.h`


typedef struct  
{
    uint16_t x, y; // coordinates of a touch
    uint16_t pressure;
} touchpanelEvent_t;

class Widget
{
 protected:
    uint16_t top;       // Distance from top of the screen
    uint16_t left;      // Distance from the left side of the screen
    uint16_t height;    // Widget height
    uint16_t width;     // Widget width
    
 public:
	Widget( uint16_t _left,
            uint16_t _top,
            uint16_t _width,
            uint16_t _height);
    virtual void refresh();
    virtual void onTouchpanelEvent(touchpanelEvent_t &e)=0;
};


#endif

