#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <fonts.h>
#include <BMPheader.h>
#include <SPI.h>

#include <MI0283QT2.h>
MI0283QT2 Display; // this global object is used in many other classes. make sure it is present and it is called `Display`

enum Oscilloscope_modes{
    Paused,
    OneShot,
    Running,
    MODE_MAX
};
volatile Oscilloscope_modes globalMode;

volatile uint8_t ain; // active analog input
const uint16_t ch_colors[3] = {
    RGB(255,0,0),   // red
    RGB(0,255,0),   // green
    RGB(0,255,255)  // magenta
};

#include "VoltageBar.h"
VoltageBarClass VBar;

#include "TimeBar.h"
TimeBarClass TBar;

#include "plotSpace.h"
PlotSpaceClass PSpace(
    [](void) -> void{// Do this code on press at the plotSpace
        static Oscilloscope_modes backup_of_global_mode = Running;
        if (Paused == globalMode) // master Yoda notation
        {
            globalMode = backup_of_global_mode;
        } else {
            backup_of_global_mode = globalMode;
            globalMode = Paused;
        }
        //PSpace.clear();
    });

#include "GuiButton.h"
//uint8_t counter = 0;
//void showCounter(void){
    //Display.drawInteger(100,10,counter,10,RGB(255,255,255),RGB(0,0,0),1);
//}
// to use an anonymous function, you have to enable C++11 in arduino:
// http://stackoverflow.com/questions/16224746/how-to-use-c11-to-program-the-arduino
GuiButton foo(0,200,6*8,40, "clear",
              [](void) -> void{PSpace.clear();});
//// One can of course do the same stuff in the old way, without any anonymous functions: 
//void on_foo_press(void){
//    counter++;showCounter();}
//GuiButton foo(100,100,50,60, "Button1",on_foo_press);

// this is not the best way to implement it, but...
void show_input_channel(void){
    char buf[5];
    sprintf(buf,"CH%d",ain);
    Display.drawText(10,50,buf,ch_colors[ain],0x0000,1);
}

ButtonFSM dangerShield_buttons[3] = {
    ButtonFSM([](void) -> void {ain = 0;show_input_channel();}),
    ButtonFSM([](void) -> void {ain = 1;show_input_channel();}),
    ButtonFSM([](void) -> void {ain = 2;show_input_channel();})
};
const uint8_t d_in[3] = {24,23,22}; // digital inputs of ARDUINO MEGA 2560, wired to the `danger shield` buttons
                                    // depend on actual wiring



Widget* activeWidgets[] = {&foo,&TBar,&VBar,&PSpace};
#define N_Widgets (sizeof(activeWidgets)/sizeof(Widget*))

void setup()
{
    Display.begin();
    Display.touchStartCal(); // without this command the touchscreen driver won't work properly.
       // However the calibration data can be stored in EEPROM. Need to consider it later.
    for(uint8_t i=0;i<N_Widgets;i++)
    {   activeWidgets[i]->refresh();    }
    globalMode = Running;
    ain = 0;
    // initialize the `danger shield` buttons
    for(uint8_t i=0;i<3;i++){
        pinMode(d_in[i],INPUT_PULLUP);
    }
    show_input_channel();
}

void loop()
{
    delay(10);
    
    // Only this code relates to the pressable button. If there are multiple GUIbuttons,
    // you should pass the touchEvent to all of them. Each button will decide if the event
    // concerns it.
    Display.touchRead();
    static touchpanelEvent_t e;
    e.x = Display.touchX();
    e.y = Display.touchY();
    e.pressure = Display.touchZ();
    for(uint8_t i=0;i<N_Widgets;i++)
    {
        activeWidgets[i]->onTouchpanelEvent(e);
    }
    
    // read data from the physical buttons
    for(uint8_t i=0;i<3;i++)
    {   dangerShield_buttons[i].FSM((digitalRead(d_in[i]))?0:1);  } //use bit inversion because of the pullup resistor
    
    // Perform the data acquisition:
    switch (globalMode)
    {
        case OneShot:
        case Running:
        //PSpace.addDataPoint(digitalRead(d_in[0]));
        PSpace.addDataPoint(analogRead(ain),ch_colors[ain]);
    }
    
}