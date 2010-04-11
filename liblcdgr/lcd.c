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
 * @file lcd.c
 * @brief Abstract library graphical/character LCD, implementation file
 * @addtogroup Main
 * @{
 */

#define _LCD_PRIVATE

#include "lcd.h"

static lcd_color_t fgclr;
static lcd_color_t bgclr;

#if ((LCD_RIGHT-LCD_LEFT+1) != LCD_WIDTH) || ((LCD_BOTTOM-LCD_TOP+1) != LCD_HEIGHT)
#error Check your LCD constants
#endif

//#include "lcd_font5x8.h"

void lcdInit()
{
    lcdHardwareInit();
    lcdControllerInit();

    fgclr = FGCLR_DEFAULT;
    bgclr = BGCLR_DEFAULT;
}


void lcdSetFgColor(lcd_color_t clr)
{
    fgclr = clr;
}

void lcdSetBgColor(lcd_color_t clr)
{
    bgclr = clr;
}

void lcdClean(void)
{
    lcdControllerFill(LCD_LEFT, LCD_TOP, LCD_RIGHT, LCD_BOTTOM, bgclr);
}

void lcdBox(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2)
{
    int t;
    if(x2 < x1) { t = x2; x2 = x1; x1 = t; }
    if(y2 < y1) { t = y2; y2 = y1; y1 = t; }
    lcdControllerFill(x1, y1, x2, y2, fgclr);
}

void lcdFillRect(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, lcd_width_t border)
{
    int t;
    if(x2 < x1) { t = x2; x2 = x1; x1 = t; }
    if(y2 < y1) { t = y2; y2 = y1; y1 = t; }

    lcdControllerFillRect(x1, y1, x2, y2, fgclr, bgclr, border);

}

void lcdPixel(lcd_coord_t x, lcd_coord_t y, lcd_color_t clr)
{
    lcdControllerFill(x, y, x, y, clr);
}


void lcdCharXY(lcd_coord_t x, lcd_coord_t y, char ch)
{
#if 0
    char* pdata = (char*)lcd_font5x8 + ch*5;
    char data;

    lcdControllerDirection(1);
#ifdef LCD_NEED_FONT_SWAP
    lcdControllerWinVert(x, x+4);
    lcdControllerWinHoriz(y, y+7);
#else
    lcdControllerWinHoriz(x, x+4);
    lcdControllerWinVert(y, y+7);
#endif
    lcdControllerGRAMPos(x, y+7);

    lcdControllerCommand(LCD_GRAM_WR);
    lcdHardwareCSGrab();
    lcdHardwareRSData(); // We send datas only

    int i, j;
    for(j=0; j<5; j++)
    {
        data = *pdata++;
        for(i=0; i<8; i++)
        {
            lcdControllerColor((data & 1)?fgclr:bgclr);
            data >>= 1;
        }
    }
    lcdHardwareCSRelease();
#endif
}

// TODO Simple replace standart strlen
#if 0
static int strlen(char* s)
{
    int len = 0;
    while(*s++)
        len++;
    return len;
}
#endif

void lcdTextXY(lcd_coord_t x, lcd_coord_t y, char* s)
{
#if 0
    int slen = strlen(s);

    lcdControllerDirection(1);
#ifdef LCD_NEED_FONT_SWAP
    lcdControllerWinVert(x, x+(6*slen)-1);
    lcdControllerWinHoriz(y, y+7);
#else
    lcdControllerWinHoriz(x, x+(6*slen)-1);
    lcdControllerWinVert(y, y+7);
#endif
    lcdControllerGRAMPos(x, y+7);

    lcdControllerCommand(LCD_GRAM_WR);
    lcdHardwareCSGrab();
    lcdHardwareRSData(); // We send datas only

    int i, j;
    while(*s)
    {
        char* pdata = (char*)lcd_font5x8 + (*s++)*5;
        for(j=0; j<5; j++)
        {
            char data = *pdata++;
            for(i=0; i<8; i++)
            {
                lcdControllerColor((data & 1)?fgclr:bgclr);
                data >>= 1;
            }
        }
        for(i=0; i<8; i++)
            lcdControllerColor(bgclr);
    }
    lcdHardwareCSRelease();
#endif
}

/**
 * @}
 */

