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
    void addDataPoint(uint16_t data,uint16_t color=RGB(255,0,0));
 private:
    EventHandler onScreenFull;
    uint16_t cursor_position;
    ButtonFSM btn;
    void drawVerticalGridline(uint16_t xpos);
    void drawHorizontalGridline(uint16_t ypos);
};

extern PlotSpaceClass PlotSpace;

#endif

