// 
// 
// 

#include "TimeBar.h"
#include "GUIcolors.h"
#include <MI0283QT2.h>
extern MI0283QT2 Display;// should be defined elsewhere, probably in `main.ino`

#define CHAR_WIDTH  (8)
#define CHAR_HEIGHT (8)

#define TBAR_XPOS (6*8)
#define TBAR_YPOS (200)
#define TBAR_WIDTH (320-TBAR_XPOS)
#define TBAR_HEIGHT (240-TBAR_YPOS)
#define TBAR_MARGIN (5)

TimeBarClass::TimeBarClass()
    :Widget(TBAR_XPOS,TBAR_YPOS,TBAR_WIDTH,TBAR_HEIGHT),
     _Tl(0,0),
     _Tr(2,5),
     _Tdiv(0,64)
{}

void TimeBarClass::refresh(void)
{
	Display.fillRect(left,top,width,height,GUI_BG);
    refreshRightTime();
    refreshLeftTime();
    refreshDivTime();
}

//void TimeBarClass::begin(void) __attribute__ ((alias("_ZN15TimeBarClass7refreshEv"))); //

void TimeBarClass::refreshRightTime(void)
{   
    char strBuf[8];
    sprintf(&(strBuf[_Tr.ToString(strBuf)])," S");
    Display.drawText(left+width-TBAR_MARGIN-CHAR_WIDTH*strlen((char*)(strBuf)),
                     top+(height-CHAR_HEIGHT)/2,
                     (char*)(&strBuf),
                     GUI_TEXT,
                     GUI_BG,
                     1);
}

void TimeBarClass::refreshLeftTime(void)
{
    char strBuf[8];
    sprintf(&(strBuf[_Tl.ToString(&strBuf[0])])," S");
    Display.drawText(left+TBAR_MARGIN,
	                 top+(height-CHAR_HEIGHT)/2,
	                 (char*)(&strBuf),
	                 GUI_TEXT,
	                 GUI_BG,
	                 1);
}

void TimeBarClass::refreshDivTime(void)
{
	char strBuf[12];
	sprintf(&(strBuf[_Tdiv.ToString(strBuf)])," S/div");
	Display.drawText(left+(width-CHAR_WIDTH*strlen((char*)(strBuf)))/2,
	                 top+(height-CHAR_HEIGHT)/2,
	                 (char*)(&strBuf),
	                 GUI_TEXT,
	                 GUI_BG,
	                 1);
}



