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
 * @file lcd_ctl.h
 * @brief Controller interface functions
 * @addtogroup LcdChipDefinitions
 * @{
 */



#ifndef  _LCD_CTL_H_
#define  _LCD_CTL_H_

/**
 * lcd_config.h must be writed by user
 */
#include <lcd_config.h>


#if defined(__DOXYGEN__)
typedef int16_t     lcd_coord_t;
typedef uint16_t    lcd_color_t;
typedef lcd_color_t lcd_pixel_t;
typedef uint8_t     lcd_width_t;
typedef uint8_t     lcd_align_t;
#endif


inline static void lcdControllerInit(void);

inline static void lcdControllerFill(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, lcd_color_t clr);
inline static void lcdControllerFillRect(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2,
        lcd_color_t fgclr, lcd_color_t bgclr, lcd_width_t border);

/**
 * @}
 */

#endif   /* ----- #ifndef _LCD_CTL_H_  ----- */
