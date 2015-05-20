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

void setup()
{
    //char foo[8];
    //sprintf((char*)(foo),"%4.2f V",5.0);
    // initializes the screen controller
    Display.begin();
    Bar.refresh();
    VBar.begin();
    
    // Use Print::write(str)
    //Display.setTextSize(2);
    //Display.setCursor(320/2-8*12,240/2-8*2);
    //Display.setTextColor(BLACK,WHITE);
    //Display.fillScreen(WHITE);
    //Display.write(foo);
//
    //// Use GraphicsLib::drawText(x,y,str,fg_col,bg,col,size)
    //Display.drawText(5,5,"TL",BLACK,WHITE,1);
    //Display.drawText(320-5-16,  // (screen width) - (margin) - (text width)
                     //5,"TR",BLACK,WHITE,1);
    //Display.drawText(5,240-5-8, // (screen height) - margin) - (text height)
                     //"BL",BLACK,WHITE,1);
    //Display.drawText(320-5-16,240-5-8,"BR",BLACK,WHITE,1);
    //
    //Display.setTextSize(1);
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
}