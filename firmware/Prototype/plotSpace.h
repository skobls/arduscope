// plotSpace.h

#ifndef _PLOTSPACE_h
#define _PLOTSPACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PlotSpaceClass
{
 public:
	//PlotSpaceClass(void);
    //void begin();
    //void refresh();
};

extern PlotSpaceClass PlotSpace;

#endif

