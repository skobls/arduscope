#include "Widget.h"

//   We shall assume that somewhere (probably in the `main.ino` file)
// exists an instance of `MI0283QT2` class, called `Display`.
extern MI0283QT2 Display;   // TODO: consider replacing with `GraphicsLib.h`

Widget::Widget( uint16_t _top, 
                uint16_t _left,  
                uint16_t _height, 
                uint16_t _width)
{
    top = _top;
    left = _left;
    height = _height;
    width = _width;
}

void Widget::refresh()
{
	Display.fillRect(left,top,width,height,RGB(0,255,255));
}
