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

#ifndef  _LCD_MCU_AT90USB162_H_
#define  _LCD_MCU_AT90USB162_H_

#include "lcd_mcu.h"

#include <util/delay.h>
#define delayMs(ms) _delay_ms(ms)

#define LCD_RST_ON() PORTC &= ~(1<<LCD_RST)
#define LCD_RST_OFF() PORTC |= (1<<LCD_RST)

#define LCD_WR_ON() PORTC &= ~(1<<LCD_WR)
#define LCD_WR_OFF() PORTC |= (1<<LCD_WR)

#define LCD_RD_ON()
#define LCD_RD_OFF()

#define LCD_RS_ON() PORTB |= (1<<LCD_RS)
#define LCD_RS_OFF() PORTB &= ~(1<<LCD_RS)

#define LCD_CS_ON() PORTB &= ~(1<<LCD_CS)
#define LCD_CS_OFF() PORTB |= (1<<LCD_CS)

static void LCD_DATA(char x)
{
    PORTD = (PORTD & ~0x7E) | (x & 0x7E);
    if(x & 0x80)
        PORTB |= (1<<LCD_D7);
    else
        PORTB &= ~(1<<LCD_D7);
    if(x & 0x01)
        PORTB |= (1<<LCD_D0);
    else
        PORTB &= ~(1<<LCD_D0);
}

inline static void lcdHardwareInit(void)
{
    LCD_CS_OFF();
    LCD_RD_OFF();
    LCD_WR_OFF();

    delayMs(50); // Wait before hardware reset
    LCD_RST_ON();
    delayMs(10);
    LCD_RST_OFF();
    delayMs(50);
}

inline static void lcdHardwareCSGrab(void)
{
    LCD_CS_ON();
}

inline static void lcdHardwareCSRelease(void)
{
    LCD_CS_OFF();
}

inline static void lcdHardwareRSCmd(void)
{
    LCD_RS_OFF();
}

inline static void lcdHardwareRSData(void)
{
    LCD_RS_ON();
}

inline static void lcdHardwareValueB(uint8_t val)
{
    LCD_DATA(val);
    LCD_WR_ON();
    LCD_WR_OFF();
}

inline static void lcdHardwareValueW(uint16_t val)
{
    LCD_DATA((val>>8)&0xFF);
    LCD_WR_ON();
    LCD_WR_OFF();
    LCD_DATA(val&0xFF);
    LCD_WR_ON();
    LCD_WR_OFF();
}

/**
 * @}
 */


#endif   /* ----- #ifndef _LCD_MCU_AT90USB162_H_  ----- */

