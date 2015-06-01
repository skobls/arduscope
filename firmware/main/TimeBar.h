// VoltageBar.h

#ifndef _TIMEBAR_h
#define _TIMEBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Decimal.h"
#include "Widget.h"

class TimeBarClass : public Widget
{
 public:
    TimeBarClass();
	void refresh(void);
    void setRightTime(float Tr);
    void setLeftTime(float Tl);
    void onTouchpanelEvent(touchpanelEvent_t &e){}; //TODO: add implementation
 private:
    void refreshRightTime(void);
    void refreshLeftTime(void);
    Decimal _Tr, _Tl;
};


#endif // _TIMEBAR_h

