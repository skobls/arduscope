// 
// 
// 

#include "plotSpace.h"
#include "GUIcolors.h"

#include <MI0283QT2.h>
extern MI0283QT2 Display; // should be defined elsewhere, probably in `main.ino`



 PlotSpaceClass::PlotSpaceClass(EventHandler _on_press/*=EMPTY_EventHandler*/):
    Widget(6*8,0,320-6*8,200),
    btn(_on_press)
{
	cursor_position = 0;
}

void PlotSpaceClass::refresh()
{
    clear();
}

void PlotSpaceClass::clear()
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
    cursor_position=0;
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

void PlotSpaceClass::addDataPoint(uint16_t data)
{
	if (cursor_position>width)
    {   clear();    }        
    
    // TODO: data interpolation should be here:
    uint32_t interpolatedData = (((uint32_t)data)*192)/1024;
    
    
    Display.drawPixel(left+cursor_position++,height - 4 - interpolatedData,GUI_PLOT_DATA);
    if (cursor_position>width)
    {
        CALL_IF_NONEMPTY(onScreenFull);
    }    
}

void PlotSpaceClass::onTouchpanelEvent(touchpanelEvent_t &e)
{
	btn.FSM( (((e.x-left) < width)     // if the event happened inside this widget
	        &&((e.y-top) < height)
	        &&(e.pressure>20))?1:0);
}
