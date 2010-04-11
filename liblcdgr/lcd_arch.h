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


#ifndef  _LCD_ARCH_H_
#define  _LCD_ARCH_H_

#include <lcd_config.h>

/* #####   LCD controllers constant  ######################################################## */

#define LCD_CTL_ST7637     101
#define LCD_CTL_AL240P1    102
#define LCD_CTL_ILI9325    102
#define LCD_CTL_ILI9320    102

#if ((LCD_CTL == LCD_CTL_ILI9325) || (LCD_CTL == LCD_CTL_ILI9320))
#   include "lcd_ctl_ili9325.h"
#elif (LCD_CTL == LCD_CTL_ST7637)
#   include "lcd_ctl_st7637.h"
#else
#   error "Unsupported LCD controller: " LCD_CTL
#endif

/**
 * @}
 */

#endif   /* ----- #ifndef _LCD_ARCH_H_  ----- */

