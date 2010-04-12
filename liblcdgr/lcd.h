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
 * @file lcd.h
 * @brief Abstract library graphical/character LCD, header file
 * @addtogroup Main
 * @{
 */


#ifndef  _LCD_H_
#define  _LCD_H_

/* #####   HEADER FILE INCLUDES   ################################################### */

#include <inttypes.h>

/**
 * lcd_config.h must be writed by user
 */
#include <lcd_config.h>

#include "lcd_arch.h"

/**
 * lcd_hw.h must be writed by user
 */
#include "lcd_hw_intf.h"
#include <lcd_hw.h>

/* #####   EXPORTED MACROS   ######################################################## */

#define LCD_ALIGN_LEFT      0x00
#define LCD_ALIGN_CENTER    0x01
#define LCD_ALIGN_RIGHT     0x02
#define LCD_ALIGN_ALIGN     0x03
#define LCD_ALIGN_TOP       0x04
#define LCD_ALIGN_MIDDLE    0x08
#define LCD_ALIGN_BOTTOM    0x0C


/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */

/**
 * Initial sequence 
 */
void lcdInit(void);

void lcdSetFgColor(lcd_color_t clr);
lcd_color_t lcdGetFgColor(void);

void lcdSetBgColor(lcd_color_t clr);
lcd_color_t lcdGetBgColor(void);

void lcdSetAlign(lcd_align_t align);
lcd_align_t lcdGetAlign(void);

void lcdClean(void);

void lcdBox(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2);
void lcdFillRect(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, lcd_width_t border);

void lcdPixel(lcd_coord_t x, lcd_coord_t y, lcd_color_t clr);

void lcdLine(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2);
void lcdLineW(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, lcd_width_t width);

void lcdCircle(lcd_coord_t x, lcd_coord_t y, lcd_coord_t radius);
void lcdCircleW(lcd_coord_t x, lcd_coord_t y, lcd_coord_t radius, lcd_width_t width);
void lcdCircleFill(lcd_coord_t x, lcd_coord_t y, lcd_coord_t radius);

void lcdImage(lcd_coord_t x, lcd_coord_t y, lcd_coord_t width, lcd_coord_t height, lcd_pixel_t* data);
void lcdImageMono(lcd_coord_t x, lcd_coord_t y, lcd_coord_t width, lcd_coord_t height, const uint8_t* data);
void lcdImagePcx(lcd_coord_t x, lcd_coord_t y, void* data);

void lcdCharXY(lcd_coord_t x, lcd_coord_t y, char ch);
void lcdTextXY(lcd_coord_t x, lcd_coord_t y, char* str);

void lcdTextBlock(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, char* str);

#endif   /* ----- #ifndef _LCD_H_  ----- */

/**
 * @}
 */
