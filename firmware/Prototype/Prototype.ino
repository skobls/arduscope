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
BarClass foo(60,55,50);
BarClass bar(135,55,50);
BarClass baz(210,55,50);

#include "VoltageBar.h"
#include "plotSpace.h"

#include "colors.h"

VoltageBarClass VBar;

void setup()
{
    Display.begin();
    foo.refresh();
    bar.refresh();
    baz.refresh();
}

void loop()
{
    foo.setState(0x00FF&(analogRead(0)>>2));
    bar.setState(0x00FF&(analogRead(1)>>2));
    baz.setState(0x00FF&(analogRead(2)>>2));
    delay(10);
    
    //static uint16_t j = 0x8000;
    //if (0 == j)
    //{
        //j = 0x8000;
    //}
    //static char colorstring[8]={0,0,0,0,0,0,0,0};
    //if (0 == i)
    //{
        //sprintf((char*)(&colorstring),"0x%04X",j);
        //Display.drawText(50,200,(char*)(&colorstring),BLACK,WHITE,1);
        //Display.fillRect(120,190,28,28,j);
        //j>>=1;
    //}
}