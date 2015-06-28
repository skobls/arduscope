// plotSpace.h

#ifndef _PLOTSPACE_h
#define _PLOTSPACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Widget.h"
#include "ButtonFSM.h"

class PlotSpaceClass : public Widget
{
 public:
	PlotSpaceClass(EventHandler _on_press=EMPTY_EventHandler);
    void refresh();
    void clear();
    void onTouchpanelEvent(touchpanelEvent_t &e);
    void addDataPoint(uint16_t data0=0,uint16_t color0=RGB(255,0,0),uint16_t data1=0,uint16_t color1=RGB(0,255,0),uint16_t data2=0,uint16_t color2=RGB(0,0,255));
 private:
    EventHandler onScreenFull;
    uint16_t cursor_position;
    ButtonFSM btn;
    void drawVerticalGridline(uint16_t xpos);
    void drawHorizontalGridline(uint16_t ypos);
};

extern PlotSpaceClass PlotSpace;

#endif

