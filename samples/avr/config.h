/*
 * =====================================================================================
 * 
 *       Filename:  global.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  Fri Mar 14 17:46:40 MSK 2008
 *       Revision:  $Id$
 *       Compiler:  gcc
 * 
 *         Author:  Ivan Alfiorov-Romamentiev (http://iar.spb.ru), ivalrom@gmail.com
 *        Company:  Freelancer
 * 
 * =====================================================================================
 */

#ifndef  _CONFIG_H_
#define  _CONFIG_H_

//#define WDT_ENABLE

#include <inttypes.h>
#include <avr/io.h>
//#ifdef WDT_ENABLE
#include <avr/wdt.h>
//#endif

#define CYCLES_PER_US ((F_CPU+500000)/1000000) 	// cpu cycles per microsecond


#define PRF_PWR     PC2

/*
#define LCD_CS      PB5
#define LCD_RS      PB4
#define LCD_D0      PB6
#define LCD_D7      PB7
#define LCD_WR      PC6
#define LCD_RST     PC7
*/

#define BUZZER      PC5

#define BUT_MENU    PD7
#define BUT_RIGHT   PD1
#define BUT_LEFT    PD2


#define _B(x) (1<<(x))

#define _SB(x) |= _B(x)
#define _RB(x) &= ~(_B(x))

#define _SET(x, val, msk) (x) = (val | ((x) & ~(msk)))

#define HI(x) (uint8_t)((x)>>8)
#define LO(x) (uint8_t)((x) & 0xFF)

#define NOP __asm__ __volatile__ ("nop")

#ifdef WDT_ENABLE
#   define wdr() wdt_reset()
#else
#   define wdr() wdt_reset()
#endif


#endif   /* ----- #ifndef _CONFIG_H_  ----- */

