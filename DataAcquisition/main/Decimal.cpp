// 
// 
// 

#include "Decimal.h"
#include <stdio.h>


 Decimal::Decimal(float value)
{
	integer = (int8_t)(value);
	decimal = (int8_t)((value-integer)*100);
}

 Decimal::Decimal(int8_t integer_part, uint8_t decimal_part)
{
	integer = integer_part;
    decimal = decimal_part;
}

uint8_t Decimal::ToString(char* buf)
{
    if (0 == decimal)
    {
        return sprintf((char*)(buf),"%d",integer);
    } 
    else
    {
        return sprintf((char*)(buf),"%d.%d",integer,decimal);
    }
}
