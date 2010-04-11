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

#ifndef  _lcd_mcu_stm32f10x_H_
#define  _lcd_mcu_stm32f10x_H_

#include "stm32f10x.h"

#include "lcd_mcu.h"

//#define USE_DELAYS

// MCU pin definitions
#define D_D0SHIFT   0
#define D_D0    (D_D0SHIFT+0)
#define D_D1    (D_D0SHIFT+1)
#define D_D2    (D_D0SHIFT+2)
#define D_D3    (D_D0SHIFT+3)
#define D_D4    (D_D0SHIFT+4)
#define D_D5    (D_D0SHIFT+5)
#define D_D6    (D_D0SHIFT+6)
#define D_D7    (D_D0SHIFT+7)

#define D_DMASK ((1<<D_D0) | (1<<D_D1) | (1<<D_D2) | (1<<D_D3) | (1<<D_D4) | (1<<D_D5) | (1<<D_D6) | (1<<D_D7))

#define D_RS    8
#define D_RD    9
#define D_WR    10
#define D_CS    11
#define D_RST   12

#define D_CTLMASK ((1<<D_RS) | (1<<D_RST) | (1<<D_CS) | (1<<D_RD) | (1<<D_WR))

#define D_MASK (D_DMASK | D_CTLMASK)

#define LCD_PORT    GPIOC


inline static void lcdHardwareInit(void)
{
    // TODO rewrite with stm library undepedence
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;

    LCD_PORT->CRL = 0x33333333; // Out_PP
    LCD_PORT->CRH = (LCD_PORT->CRH & 0xFFF00000) | 0x00033333;
    //LCD_PORT->ODR = VAL_GPIOCODR;
    LCD_PORT->BSRR = D_CTLMASK;

    delayMs(50); // Wait before hardware reset
    LCD_PORT->BRR = (1<<D_RST);  // Reset LCD
    delayMs(10);
    LCD_PORT->BSRR = (1<<D_RST);
    delayMs(50);
}

inline static void lcdHardwareCSGrab(void)
{
    LCD_PORT->BRR = (1<<D_CS);
#ifdef USE_DELAYS
    volatile int i;
    for(i=0; i<50; i++)
        ;
#endif
}

inline static void lcdHardwareCSRelease(void)
{
    LCD_PORT->BSRR = (1<<D_CS);
}

inline static void lcdHardwareRSCmd(void)
{
    LCD_PORT->BRR = (1<<D_RS);
}

inline static void lcdHardwareRSData(void)
{
    LCD_PORT->BSRR = (1<<D_RS);
}

inline static void lcdHardwareValueB(uint8_t val)
{
    LCD_PORT->BRR =  D_DMASK;
    LCD_PORT->BSRR = val<<D_D0SHIFT;
    LCD_PORT->BRR =  (1<<D_WR); // Write hi byte of value
#ifdef USE_DELAYS
    asm volatile (" nop "); asm volatile (" nop "); asm volatile (" nop ");
#endif
    LCD_PORT->BSRR = (1<<D_WR);
#ifdef USE_DELAYS
    asm volatile (" nop "); asm volatile (" nop "); asm volatile (" nop ");
#endif
}

inline static void lcdHardwareValueW(uint16_t val)
{
    LCD_PORT->BRR =  D_DMASK;
    LCD_PORT->BSRR = ((val&0xFF00)>>8)<<D_D0SHIFT;
    LCD_PORT->BRR =  (1<<D_WR); // Write hi byte of value
#ifdef USE_DELAYS
    asm volatile (" nop "); asm volatile (" nop "); asm volatile (" nop ");
#endif
    LCD_PORT->BSRR = (1<<D_WR);

    LCD_PORT->BRR =  D_DMASK;
    LCD_PORT->BSRR = (val&0xFF)<<D_D0SHIFT;
    LCD_PORT->BRR =  (1<<D_WR); // Write low byte of value
#ifdef USE_DELAYS
    asm volatile (" nop "); asm volatile (" nop "); asm volatile (" nop ");
#endif
    LCD_PORT->BSRR = (1<<D_WR);
#ifdef USE_DELAYS
    asm volatile (" nop "); asm volatile (" nop "); asm volatile (" nop ");
#endif
}

/**
 * @}
 */


#endif   /* ----- #ifndef _lcd_mcu_stm32f10x_H_  ----- */
