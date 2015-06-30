#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <fonts.h>
#include <BMPheader.h>
#include <SPI.h>
#include "ADC_Configuration.h"



volatile bool ch_activation[3] = {false};
	uint8_t last_ch = 0;

uint8_t analogChannelEnabled_flags = 0x07;

#include <MI0283QT2.h>
MI0283QT2 Display; // this global object is used in many other classes. make sure it is present and it is called `Display`

enum Oscilloscope_modes{
    Paused,
    OneShot,
    Running,
    MODE_MAX
};
int data_read = 0 ;
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

/*
ButtonFSM dangerShield_buttons[3] = {
    ButtonFSM([](void) -> void {ain = 0;show_input_channel();}),
    ButtonFSM([](void) -> void {ain = 1;show_input_channel();}),
    ButtonFSM([](void) -> void {ain = 2;show_input_channel();})
};
*/
ButtonFSM dangerShield_buttons[3] = {
	ButtonFSM([](void) -> void {analogChannelEnabled_flags ^= ain_ch0;}),
	ButtonFSM([](void) -> void {analogChannelEnabled_flags ^= ain_ch1;}),
	ButtonFSM([](void) -> void {analogChannelEnabled_flags ^= ain_ch2;})
};
const uint8_t d_in[3] = {24,23,22}; // digital inputs of ARDUINO MEGA 2560, wired to the `danger shield` buttons
                                    // depend on actual wiring



Widget* activeWidgets[] = {&foo,&TBar,&VBar,&PSpace};
#define N_Widgets (sizeof(activeWidgets)/sizeof(Widget*))

ADC_Configuration inst1;

void setup()
{
	Serial.begin(9600);
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
	for (uint8_t i=0; i<3; i++)
	{
		ch_activation[i] = false;
	}
    show_input_channel();
	//ADC_Enable();
	//inst1.change_mode(FREE_RUNING_AUTO_TRIGGER_MODE);
	//inst1.Start_Conversion();
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
    for(uint8_t i=0;i<3;i++)
    {
			if (digitalRead(d_in[i]) == 0)
			{
				ch_activation[i] = ch_activation[i]?0:1;
			}
		   
	}
    switch (globalMode)
    {
        case OneShot:
        case Running:
        //PSpace.addDataPoint(digitalRead(d_in[0]));
		PSpace.addDataPoint(inst1.readValue(0),ch_colors[0],
							inst1.readValue(1),ch_colors[1],
							inst1.readValue(2),ch_colors[2]);
		/*
        if ( ch_activation[0] == true)
        {
			PSpace.addDataPoint(inst1.readValue(0),ch_colors[0]);
        }
		if (ch_activation[1] == true)
		{
			PSpace.addDataPoint(inst1.readValue(1),ch_colors[1]);
		} 
		if (ch_activation[2] = true)
		{
			PSpace.addDataPoint(inst1.readValue(2),ch_colors[2]);
		}
		*/
		
    }
    
}
/*
ISR(ADC_vect)
{
	
	data_read = ADC;
	last_ch++;
	if ( last_ch < 3)
	{
		ADMUX |= (last_ch << MUX0);
	}
	else
	{
		last_ch = 0;
		ADMUX |= (last_ch << MUX0);
	}
	
	
}
*/