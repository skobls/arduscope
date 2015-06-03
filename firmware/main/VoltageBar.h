// VoltageBar.h

#ifndef _VOLTAGEBAR_h
#define _VOLTAGEBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Decimal.h"
#include "Widget.h"

class VoltageBarClass : public Widget
{
 public:
    VoltageBarClass();
	void refresh(void);
    void setHighVoltage(float Vh);
    void setLowVoltage(float Vl);
    void onTouchpanelEvent(touchpanelEvent_t &e){}; //TODO: add implementation
 private:
    void refreshHighVoltage(void);
    void refreshLowVoltage(void);
    void refreshDivVoltage(void);
    Decimal _Vh, _Vl, _Vdiv;
};


#endif

