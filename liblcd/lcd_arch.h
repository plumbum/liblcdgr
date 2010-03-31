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
 * @file lcd_arch.h
 * @brief
 * @addtogroup Main
 * @{
 */


#ifndef  _lcd_arch_H_
#define  _lcd_arch_H_

#include <lcd_config.h>

#if (LCD_MCU == MCU_STM32F10x)
#   include "lcd_mcu_stm32f10x.h"
#elif (LCD_MCU == MCU_LPC2103)
#   include "lcd_mcu_lpc2103.h"
#elif (LCD_MCU == MCU_AVR)
#   include "lcd_mcu_avr.h"
#else
#   error "Unsupported chip" LCD_MCU
#endif


#if (LCD_DISPLAY == CHIP_AL240P1)
#   include "lcd_ctl_al240p1.h"
#elif (LCD_DISPLAY == CHIP_ST7637)
#   include "lcd_ctl_st7637.h"
#else
#   error "Unsupported controller" LCD_DISPLAY
#endif

/**
 * @}
 */

#endif   /* ----- #ifndef _lcd_arch_H_  ----- */
