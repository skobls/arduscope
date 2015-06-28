// Decimal.h

#ifndef _DECIMAL_h
#define _DECIMAL_h

#include <stdint.h>


class Decimal
{
 public:
    int8_t integer;
    uint8_t decimal;
	Decimal(float value);
    Decimal(int8_t integer_part, uint8_t decimal_part);
    uint8_t ToString(char* buf);
};

#endif

