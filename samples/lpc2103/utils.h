#ifndef _UTILS_H_
#define _UTILS_H_

#include <inttypes.h>
#include "config.h"

#define TUNE_FAC 0.96154

//#define delay_us(delayval) delay_us_( (uint32_t)( (FOSC*PLL_MUL) / (1000000/(delayval)) /2 ) ) 
#define delay_us(delayval) delay_us_( (uint32_t)( (FOSC*PLL_MUL) / (1000000/(delayval)) /4 * TUNE_FAC) ) 
void delay_us_(uint32_t delayval);
//void delay_ms(uint32_t delayval);

char* ultoa(uint32_t val, char* dest);
char* ltoa(int32_t val, char* dest);

#endif /* _UTILS_H_ */

