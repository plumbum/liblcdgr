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
 * @file lcd_mcu_lpc2103.h
 * @brief Hardware access definition for LPC2103 processors
 * @addtogroup McuDefinitions
 * @{
 */

#ifndef  _LCD_MCU_LPC2103_H_
#define  _LCD_MCU_LPC2103_H_

#include <inttypes.h>
#include <LPC2103.h>
#include "utils.h"

/* Define LCD controller type */
#define LCD_CTL LCD_CTL_ILI9325

/* TYPES */
typedef uint16_t lcd_data_t;


//#define LCD_DELAY()     do { asm volatile(" nop "); asm volatile(" nop "); asm volatile(" nop "); } while(0);
#define LCD_DELAY()

// MCU pin definitions
#define D_D0SHIFT  16 
#define D_D0    (D_D0SHIFT+0)
#define D_D1    (D_D0SHIFT+1)
#define D_D2    (D_D0SHIFT+2)
#define D_D3    (D_D0SHIFT+3)
#define D_D4    (D_D0SHIFT+4)
#define D_D5    (D_D0SHIFT+5)
#define D_D6    (D_D0SHIFT+6)
#define D_D7    (D_D0SHIFT+7)

#define D_DMASK ((1<<D_D0) | (1<<D_D1) | (1<<D_D2) | (1<<D_D3) | (1<<D_D4) | (1<<D_D5) | (1<<D_D6) | (1<<D_D7))

#define D_RS    27
#define D_CS    28
#define D_RD    29
#define D_WR    30
#define D_RST   31

#define D_CTLMASK ((1<<D_RS) | (1<<D_RST) | (1<<D_CS) | (1<<D_RD) | (1<<D_WR))

#define D_MASK (D_DMASK | D_CTLMASK)

inline static void lcdHardwareInit(void)
{
    FIO0DIR |= D_MASK;
    FIO0SET = D_CTLMASK;
    FIO0CLR = D_DMASK;
}

#define lcdHardwareDelayMs(ms) delay_ms(ms)
#define lcdHardwareDelayUs(us) delay_us(us)

inline static void lcdHardwareReset(void)
{
    FIO0CLR = (1<<D_RST);
    lcdHardwareDelayMs(50);
    FIO0SET = (1<<D_RST);
    lcdHardwareDelayMs(50);
}

#define lcdHardwareSelect(void)     FIO0CLR = (1<<D_CS)
#define lcdHardwareRelease(void)    FIO0SET = (1<<D_CS)
#define lcdHardwareCmd(void)        FIO0CLR = (1<<D_RS)
#define lcdHardwareData(void)       FIO0SET = (1<<D_RS)

inline static void lcdHardwarePutB(uint8_t val)
{
    FIO0CLR = D_DMASK;
    FIO0SET = (uint32_t)val<<D_D0SHIFT;
    LCD_DELAY();
    FIO0CLR = (1<<D_WR); // Write hi byte of value
    LCD_DELAY();
    FIO0SET = (1<<D_WR);
}

inline static void lcdHardwarePutW(uint16_t val)
{
    FIO0CLR = D_DMASK;
    FIO0SET = (uint32_t)(val>>8)<<D_D0SHIFT;
    LCD_DELAY();
    FIO0CLR = (1<<D_WR); // Write hi byte of value
    LCD_DELAY();
    FIO0SET = (1<<D_WR);

    FIO0CLR = D_DMASK;
    FIO0SET = (uint32_t)(val&0xFF)<<D_D0SHIFT;
    LCD_DELAY();
    FIO0CLR = (1<<D_WR); // Write hi byte of value
    LCD_DELAY();
    FIO0SET = (1<<D_WR);
}

inline static uint8_t lcdHardwareGetB(void)
{
    uint8_t dat;
    FIO0DIR &= ~D_DMASK;
    FIO0SET = D_DMASK;
    FIO0CLR = (1<<D_RD);
    LCD_DELAY();
    dat = (FIO0PIN>>D_D0SHIFT) & 0xFF;
    FIO0SET = (1<<D_RD);
    FIO0DIR |= D_DMASK;
    return dat;
}

inline static uint16_t lcdHardwareGetW(void)
{
    uint8_t dat;
    FIO0DIR &= ~D_DMASK;
    FIO0SET = D_DMASK;
    /* First byte */
    FIO0CLR = (1<<D_RD);
    LCD_DELAY();
    dat = ((FIO0PIN>>D_D0SHIFT)<<8) & 0xFF00;
    FIO0SET = (1<<D_RD);
    LCD_DELAY();
    /* Second byte */
    FIO0CLR = (1<<D_RD);
    LCD_DELAY();
    dat |= (FIO0PIN>>D_D0SHIFT) & 0xFF;
    FIO0SET = (1<<D_RD);
    FIO0DIR |= D_DMASK;
    return dat;
}

/**
 * @}
 */


#endif   /* ----- #ifndef _LCD_MCU_LPC2103_H_  ----- */

