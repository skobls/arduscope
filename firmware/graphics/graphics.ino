#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <fonts.h>
#include <BMPheader.h>
#include <SPI.h>
#include <MI0283QT2.h>

MI0283QT2 Display;

#define WHITE 0xFFFF
#define BLACK 0x0000

void setup()
{
    // initializes the screen controller
    Display.begin();
    
    // Use Print::write(str)
    Display.setTextSize(2);
    Display.setCursor(320/2-8*12,240/2-8*2);
    Display.setTextColor(BLACK,WHITE);
    Display.fillScreen(WHITE);
    Display.write("Hello, World!");
    
    // Use GraphicsLib::drawText(x,y,str,fg_col,bg,col,size)
    Display.drawText(5,5,"TL",BLACK,WHITE,1);
    Display.drawText(320-5-16,  // (screen width) - (margin) - (text width)
                     5,"TR",BLACK,WHITE,1);
    Display.drawText(5,240-5-8, // (screen height) - margin) - (text height)
                     "BL",BLACK,WHITE,1);
    Display.drawText(320-5-16,240-5-8,"BR",BLACK,WHITE,1);
}

void loop()
{
    
}