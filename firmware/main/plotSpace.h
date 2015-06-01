// plotSpace.h

#ifndef _PLOTSPACE_h
#define _PLOTSPACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Widget.h"

class PlotSpaceClass : public Widget
{
 public:
	PlotSpaceClass(void);
    void refresh();
    void onTouchpanelEvent(touchpanelEvent_t &e){};
 private:
    void drawVerticalGridline(uint16_t xpos);
    void drawHorizontalGridline(uint16_t ypos);
};

extern PlotSpaceClass PlotSpace;

#endif

