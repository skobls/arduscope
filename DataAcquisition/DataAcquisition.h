// DataAcquisition.h

#ifndef _DATAACQUISITION_h
#define _DATAACQUISITION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DataAcquisitionClass
{
 protected:


 public:
	void init();
};

extern DataAcquisitionClass DataAcquisition;

#endif

