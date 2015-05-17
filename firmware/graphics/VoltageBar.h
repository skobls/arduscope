// VoltageBar.h

#ifndef _VOLTAGEBAR_h
#define _VOLTAGEBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Decimal.h"

class VoltageBarClass
{
 public:
    VoltageBarClass();
	void begin(void);
    void refresh(void);
    void setHighVoltage(float Vh);
    void setLowVoltage(float Vl);
 private:
    void refreshHighVoltage(void);
    void refreshLowVoltage(void);
    Decimal _Vh, _Vl;
};


#endif

