// 
// 
// 

#include "VoltageBar.h"
#include "GUIcolors.h"
#include <MI0283QT2.h>
extern MI0283QT2 Display;// should be defined elsewhere, probably in `main.ino`

#define CHAR_WIDTH  (8)
#define CHAR_HEIGHT (8)

#define VBAR_XPOS   (0)
#define VBAR_YPOS   (0)
#define VBAR_WIDTH  (6*8)
#define VBAR_HEIGHT (200)
#define VBAR_MARGIN (5)

VoltageBarClass::VoltageBarClass()
    :Widget(VBAR_XPOS,VBAR_YPOS,VBAR_HEIGHT,VBAR_WIDTH),
     _Vl(0,0),
     _Vh(5,0)
{}

void VoltageBarClass::refresh(void)
{
	Display.fillRect(left,top,width,height,GUI_BG);
    refreshHighVoltage();
    refreshLowVoltage();
}

//void VoltageBarClass::begin(void) __attribute__ ((alias("_ZN15VoltageBarClass7refreshEv"))); //

void VoltageBarClass::refreshHighVoltage(void)
{   
    char strBuf[8];
    sprintf(&(strBuf[_Vh.ToString(&strBuf[0])])," V");
    Display.drawText(VBAR_XPOS+VBAR_WIDTH-VBAR_MARGIN-CHAR_WIDTH*strlen((char*)(strBuf)),
                     VBAR_MARGIN,
                     (char*)(&strBuf),
                     GUI_TEXT,
                     GUI_BG,
                     1);
}

void VoltageBarClass::refreshLowVoltage(void)
{
    char strBuf[8];
    sprintf(&(strBuf[_Vl.ToString(&strBuf[0])])," V");
    Display.drawText(VBAR_XPOS+VBAR_WIDTH-VBAR_MARGIN-CHAR_WIDTH*strlen((char*)(strBuf)),
	                 VBAR_HEIGHT-VBAR_MARGIN-CHAR_HEIGHT,
	                 (char*)(&strBuf),
	                 GUI_TEXT,
	                 GUI_BG,
	                 1);
}



