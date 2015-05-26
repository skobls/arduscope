#include "Decimal.h"
#include "VoltageBar.h"
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <fonts.h>
#include <BMPheader.h>
#include <SPI.h>

#include <MI0283QT2.h>
MI0283QT2 Display;

#include "bar.h"
BarClass Bar(300,55,10);

#include "VoltageBar.h"
#include "plotSpace.h"

#include "colors.h"

VoltageBarClass VBar;

#include "GuiButton.h"
uint8_t counter = 0;
void showCounter(void){
    Display.drawInteger(100,10,counter,10,RGB(255,255,255),RGB(0,0,0),1);
}
// to use an anonymous function, you have to enable C++11 in arduino:
// http://stackoverflow.com/questions/16224746/how-to-use-c11-to-program-the-arduino
GuiButton foo(100,100,50,60, "Button1",
              [](void) -> void{counter++;showCounter();});
//// One can of course do the same stuff in the old way, without any anonymous functions, 
//void on_foo_press(void){
//    counter++;showCounter();}
//GuiButton foo(100,100,50,60, "Button1",on_foo_press);

void setup()
{
    Display.begin();
    Display.touchStartCal(); // without this command the touchscreen driver won't work properly.
       // However the calibration data can be stored in EEPROM. Need to consider it later.
    Bar.refresh();
    VBar.begin();
    foo.refresh();
    showCounter();
    
}

void loop()
{
    static uint8_t i;
    Bar.setState(i++);
    delay(10);
    
    static uint16_t j = 0x8000;
    if (0 == j)
    {
        j = 0x8000;
    }
    static char colorstring[8]={0,0,0,0,0,0,0,0};
    if (0 == i)
    {
        sprintf((char*)(&colorstring),"0x%04X",j);
        Display.drawText(50,200,(char*)(&colorstring),BLACK,WHITE,1);
        Display.fillRect(120,190,28,28,j);
        j>>=1;
    }
    
    // Only this code relates to the pressable button. If there are multiple GUIbuttons,
    // you should pass the touchEvent to all of them. Each button will decide if the event
    // concerns it.
    Display.touchRead();
    static touchpanelEvent_t e;
    e.x = Display.touchX();
    e.y = Display.touchY();
    e.pressure = Display.touchZ();
    foo.onTouchpanelEvent(e);
}