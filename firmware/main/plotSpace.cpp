// 
// 
// 

#include "plotSpace.h"
#include "GUIcolors.h"

#include <MI0283QT2.h>
extern MI0283QT2 Display; // should be defined elsewhere, probably in `main.ino`



 PlotSpaceClass::PlotSpaceClass(void):
    Widget(6*8,0,320-6*8,200)
{
	
}

void PlotSpaceClass::refresh()
{
	Display.fillRect(left,top,width,height,GUI_PLOT_BG);
    for(uint16_t i=64;i<width;i+=64)
    {   
        drawVerticalGridline(i);  
    }
    for(uint16_t i=4 ;i<width;i+=48)
    {   
        drawHorizontalGridline(i);    
    }
}

void PlotSpaceClass::drawVerticalGridline(uint16_t xpos)
{
	Display.setArea(left+xpos,top,left+xpos,top+height);
    Display.drawStart();
    for (uint16_t i = 0; i<height; i++)
    {   Display.draw((i&0x0007)?GUI_PLOT_BG:GUI_PLOT_GRID);}
    Display.drawStop();
}

void PlotSpaceClass::drawHorizontalGridline(uint16_t ypos)
{
	//Display.setOrientation(0);
	Display.setArea(left,ypos,left+width-1,ypos);
    Display.drawStart();
    for (uint16_t i = 0; i<width; i++)
    {   Display.draw((i&0x0007)?GUI_PLOT_BG:GUI_PLOT_GRID);}
    Display.drawStop();
}
