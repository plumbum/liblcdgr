/*
    LibLCDgr - Copyright (C) 2009 Ivan A-R <ivan@tuxotronic.org>

    This file is part of liblcdgr project

    LibLCDgr is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    LibLCDgr is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes LibLCDgr, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file lcd_mcu_stm32f10x.h
 * @brief Hardware access definition for STM32F10x processors
 * @addtogroup McuDefinitions
 * @{
 */

#ifndef  _LCD_MCU_AVR_H_
#define  _LCD_MCU_AVR_H_

#include <inttypes.h>
/* TYPES */

typedef uint16_t lcd_data_t;


#ifdef _LCD_PRIVATE

#include "lcd_mcu.h"

#include <avr/io.h>


#ifndef LCD_RST
#define LCD_RST     PC7
#endif

#ifndef LCD_CS
#define LCD_CS      PB5
#endif 

#ifndef LCD_RS
#define LCD_RS      PB4
#endif

#ifndef LCD_WR
#define LCD_WR      PC6
#endif

#ifndef LCD_D0
#define LCD_D0      PB6
#endif

#ifndef LCD_D1
#define LCD_D1      PD1
#endif

#ifndef LCD_D7
#define LCD_D7      PB7
#endif

#ifndef LCD_RST_ON
#define LCD_RST_ON() PORTC &= ~(1<<LCD_RST)
#endif

#ifndef LCD_RST_OFF
#define LCD_RST_OFF() PORTC |= (1<<LCD_RST)
#endif

#ifndef LCD_WR_ON
#define LCD_WR_ON() PORTC &= ~(1<<LCD_WR)
#endif

#ifndef LCD_WR_OFF
#define LCD_WR_OFF() PORTC |= (1<<LCD_WR)
#endif

#ifndef LCD_RD_ON
#define LCD_RD_ON()
#endif

#ifndef LCD_RD_OFF
#define LCD_RD_OFF()
#endif

#ifndef LCD_RS_ON
#define LCD_RS_ON() PORTB |= (1<<LCD_RS)
#endif

#ifndef LCD_RS_OFF
#define LCD_RS_OFF() PORTB &= ~(1<<LCD_RS)
#endif

#ifndef LCD_CS_ON
#define LCD_CS_ON() PORTB &= ~(1<<LCD_CS)
#endif

#ifndef LCD_CS_OFF
#define LCD_CS_OFF() PORTB |= (1<<LCD_CS)
#endif

#ifndef LCD_PORT_INIT
#define LCD_PORT_INIT() { \
    DDRB |= (1<<LCD_CS) | (1<<LCD_RS) | (1<<LCD_D0) | (1<<LCD_D7); \
    DDRC |= (1<<LCD_WR) | (1<<LCD_RST); \
    DDRD |= 0x7E; \
}
#endif

#ifndef LCD_PUT_DATA
#define LCD_PUT_DATA(x) \
{ \
    PORTD = (PORTD & ~0x7E) | (x & 0x7E); \
    if(x & 0x80) \
        PORTB |= (1<<LCD_D7); \
    else \
        PORTB &= ~(1<<LCD_D7); \
    if(x & 0x01) \
        PORTB |= (1<<LCD_D0); \
    else \
        PORTB &= ~(1<<LCD_D0); \
}
#endif


// TODO
#ifndef LCD_GET_DATA
#define LCD_GET_DATA() (0)
#endif

inline static void lcdHardwareInit(void)
{
    LCD_RST_OFF();
    LCD_CS_OFF();
    LCD_RD_OFF();
    LCD_WR_OFF();
    LCD_PORT_INIT();

    delayMs(50); // Wait before hardware reset
    LCD_RST_ON();
    delayMs(10);
    LCD_RST_OFF();
    delayMs(50);
}


inline static void lcdHardwareSelect(void)
{
    LCD_CS_ON();
}

inline static void lcdHardwareRelease(void)
{
    LCD_CS_OFF();
}

inline static void lcdHardwareCmd(void)
{
    LCD_RS_OFF();
}

inline static void lcdHardwareData(void)
{
    LCD_RS_ON();
}

inline static void lcdHardwarePut(uint8_t val)
{
    LCD_PUT_DATA(val);
    LCD_WR_ON();
    LCD_WR_OFF();
}

inline static void lcdHardwarePutW(uint16_t val)
{
    LCD_PUT_DATA((val>>8)&0xFF);
    LCD_WR_ON();
    LCD_WR_OFF();
    LCD_PUT_DATA(val&0xFF);
    LCD_WR_ON();
    LCD_WR_OFF();
}

inline static uint8_t lcdHardwareGet(void)
{
    return LCD_GET_DATA();
}

inline static uint16_t lcdHardwareGetW(void)
{
    uint16_t r;
    r = LCD_GET_DATA()<<8;
    return r | LCD_GET_DATA();
}

#endif /* _LCD_PRIVATE */

/**
 * @}
 */


#endif   /* ----- #ifndef _LCD_MCU_AVR_H_  ----- */

