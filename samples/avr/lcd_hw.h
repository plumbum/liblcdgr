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
#include <avr/io.h>
#include <util/delay.h>

/* Define LCD controller type */
#define LCD_CTL LCD_CTL_ILI9325

/* TYPES */
typedef uint16_t lcd_data_t;


#define LCD_RST     PC7
#define LCD_CS      PB5
#define LCD_RS      PB4
#define LCD_WR      PC6
#define LCD_RD
#define LCD_D0      PB6
#define LCD_D1      PD1
#define LCD_D2      PD2
#define LCD_D3      PD3
#define LCD_D4      PD4
#define LCD_D5      PD5
#define LCD_D6      PD6
#define LCD_D7      PB7

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

// TODO
#define LCD_GET_DATA() (0)

inline static void lcdHardwareInit(void)
{
    LCD_RST_OFF();
    LCD_CS_OFF();
    LCD_RD_OFF();
    LCD_WR_OFF();

    // LCD_PORT_INIT
    DDRB |= (1<<LCD_CS) | (1<<LCD_RS) | (1<<LCD_D0) | (1<<LCD_D7);
    DDRC |= (1<<LCD_WR) | (1<<LCD_RST);
    DDRD |= 0x7E;
}

#define lcdHardwareDelayMs(ms) _delay_ms(ms)
#define lcdHardwareDelayUs(us) _delay_us(us)

inline static void lcdHardwareReset(void)
{
    LCD_RST_ON();
    lcdHardwareDelayMs(50);
    LCD_RST_OFF();
    lcdHardwareDelayMs(50);
}

#define lcdHardwareSelect(void)     LCD_CS_ON()
#define lcdHardwareRelease(void)    LCD_CS_OFF()
#define lcdHardwareCmd(void)        LCD_RS_OFF()
#define lcdHardwareData(void)       LCD_RS_ON()

inline static void lcdHardwarePutB(uint8_t val)
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

inline static uint8_t lcdHardwareGetB(void)
{
    uint8_t r;
    LCD_RD_ON();
    r = LCD_GET_DATA();
    LCD_RD_OFF();
    return r;
}

inline static uint16_t lcdHardwareGetW(void)
{
    uint16_t r;
    LCD_RD_ON();
    r = LCD_GET_DATA()<<8;
    LCD_RD_OFF();
    LCD_RD_ON();
    r |=  LCD_GET_DATA();
    LCD_RD_OFF();
    return r;
}


/**
 * @}
 */

#endif   /* ----- #ifndef _LCD_MCU_AVR_H_  ----- */

