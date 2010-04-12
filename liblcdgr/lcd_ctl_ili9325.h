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
 * @file lcd_ctl_al240p1.h
 * @brief 2.4" 240x320 TFT LCD AL240P1-3S01YG. Inits and definitions
 * @addtogroup LcdChipDefinitions
 * @{
 */

#ifndef _LCD_CTL_ILI9325_H_
#define _LCD_CTL_ILI9325_H_

#include "lcd.h"

/**
 * lcd_hw.h must be writed by user
 */
#include "lcd_hw_intf.h"
#include <lcd_hw.h>

typedef int16_t     lcd_coord_t;
typedef uint16_t    lcd_color_t;
typedef uint8_t     lcd_width_t;
typedef uint8_t     lcd_align_t;

typedef lcd_color_t lcd_pixel_t;

typedef uint16_t    lcd_value_t;

/* Define logical display size in pixels */
#define LCD_WIDTH 240UL
#define LCD_HEIGHT 320UL

#define LCD_LEFT 0UL
#define LCD_RIGHT 239UL

#define LCD_TOP 0UL
#define LCD_BOTTOM 319UL

// TODO make correct
#define FGCLR_DEFAULT 0xF0FF
#define BGCLR_DEFAULT 0x0F00

/**
 * Make 16bit color from RGB 8bit color components
 */
#define lcdGetColor(r, g, b) (lcd_color_t)(((r&0xF8)<<8) | ((g&0xFC)<<3) | (b>>3))

/**********************************************
 * Private section
 */

#ifdef _LCD_PRIVATE

/* Controller commands definitions */
#define LCD_WND_HORIZ_ADDR_START    0x0050
#define LCD_WND_HORIZ_ADDR_END      0x0051
#define LCD_WND_VERT_ADDR_START     0x0052
#define LCD_WND_VERT_ADDR_END       0x0053
#define LCD_GRAM_HORIZ_ADDR         0x0020
#define LCD_GRAM_VERT_ADDR          0x0021
#define LCD_GRAM_WR                 0x0022


inline static void lcdControllerCommand(lcd_value_t cmd);
inline static void lcdControllerData(lcd_value_t data);
inline static void lcdControllerPair(lcd_value_t cmd, lcd_value_t data);
inline static void lcdControllerWinHoriz(lcd_coord_t x1, lcd_coord_t x2);
inline static void lcdControllerWinVert(lcd_coord_t y1, lcd_coord_t y2);
inline static void lcdControllerGRAMPos(lcd_coord_t x, lcd_coord_t y);

typedef struct {
    uint8_t delay;
    uint8_t cmd;
    uint16_t data;
} lcd_command_ts;

#define lcdControllerColor(color) lcdHardwarePutW(color)

#define INIT_DELAY 20
inline static void lcdControllerInit(void)
{

    lcdHardwareDelayMs(INIT_DELAY); // 257 ms after reset
    lcdControllerPair(0xE5, 0x8000);

    lcdHardwareDelayMs(INIT_DELAY); // 358 ms after reset
    lcdControllerPair(0x00, 0x0001);
    lcdControllerPair(0x01, 0x0100);
    lcdControllerPair(0xe3, 0x3008);
    lcdControllerPair(0xe7, 0x0012);
    lcdControllerPair(0xef, 0x1231);
    lcdControllerPair(0x01, 0x0100);
    lcdControllerPair(0x02, 0x0700);
    lcdControllerPair(0x03, 0x10a8);
    lcdControllerPair(0x04, 0x0000);
    lcdControllerPair(0x08, 0x0207);
    lcdControllerPair(0x09, 0x0000);
    lcdControllerPair(0x0a, 0x0000);
    lcdControllerPair(0x0c, 0x0000);
    lcdControllerPair(0x0d, 0x0000);
    lcdControllerPair(0x0f, 0x0000);
    lcdControllerPair(0x10, 0x0000);
    lcdControllerPair(0x11, 0x0007);
    lcdControllerPair(0x12, 0x0003);
    lcdControllerPair(0x13, 0x0300);

    lcdHardwareDelayMs(INIT_DELAY*4); // 561 ms after reset
    lcdControllerPair(0x10, 0x1290);
    lcdControllerPair(0x11, 0x0227);

    lcdHardwareDelayMs(INIT_DELAY); // 660 ms after reset
    lcdControllerPair(0x12, 0x011C);

    lcdHardwareDelayMs(INIT_DELAY); // 763 ms after reset
    lcdControllerPair(0x13, 0x1F00);
    lcdControllerPair(0x29, 0x0009);
    lcdControllerPair(0x2B, 0x000D);

    lcdHardwareDelayMs(INIT_DELAY); // 864 ms after reset
    lcdControllerPair(0x20, 0x0000);
    lcdControllerPair(0x21, 0x0000);
    lcdControllerPair(0x30, 0x0004);
    lcdControllerPair(0x31, 0x0007);
    lcdControllerPair(0x32, 0x0006);
    lcdControllerPair(0x35, 0x0206);
    lcdControllerPair(0x36, 0x0408);
    lcdControllerPair(0x37, 0x0507);
    lcdControllerPair(0x38, 0x0200);
    lcdControllerPair(0x39, 0x0707);
    lcdControllerPair(0x3c, 0x0504);
    lcdControllerPair(0x3d, 0x0f02);

    lcdControllerPair(0x50, 0x0000);
    lcdControllerPair(0x51, 0x00ef);
    lcdControllerPair(0x52, 0x0000);
    lcdControllerPair(0x53, 0x013f);

    lcdControllerPair(0x60, 0xa700);
    lcdControllerPair(0x61, 0x0001);
    lcdControllerPair(0x6a, 0x0000);
    lcdControllerPair(0x80, 0x0000);
    lcdControllerPair(0x81, 0x0000);
    lcdControllerPair(0x82, 0x0000);
    lcdControllerPair(0x83, 0x0000);
    lcdControllerPair(0x84, 0x0000);
    lcdControllerPair(0x85, 0x0000);
    lcdControllerPair(0x90, 0x0010);
    lcdControllerPair(0x92, 0x0600);
    lcdControllerPair(0x93, 0x0003);
    lcdControllerPair(0x95, 0x0110);
    lcdControllerPair(0x97, 0x0000);
    lcdControllerPair(0x98, 0x0000);
    lcdControllerPair(0x07, 0x0133);
 
    lcdHardwareDelayMs(INIT_DELAY);
}

inline static void lcdControllerCommand(lcd_value_t cmd)
{
    lcdHardwareSelect();
    lcdHardwareCmd();
    lcdHardwarePutW(cmd);
    lcdHardwareRelease();
}

inline static void lcdControllerData(lcd_value_t data)
{
    lcdHardwareSelect();
    lcdHardwareData();
    lcdHardwarePutW(data);
    lcdHardwareRelease();
}

inline static void lcdControllerPair(lcd_value_t cmd, lcd_value_t data)
{
    lcdHardwareSelect();
    lcdHardwareCmd();
    lcdHardwarePutW(cmd);
    lcdHardwareData();
    lcdHardwarePutW(data);
    lcdHardwareRelease();
}

inline static void lcdControllerWinHoriz(lcd_coord_t x1, lcd_coord_t x2)
{
    lcdHardwareSelect();
    lcdHardwareCmd();
    lcdHardwarePutW(0x50);
    lcdHardwareData();
    lcdHardwarePutW(x1);
    lcdHardwareCmd();
    lcdHardwarePutW(0x51);
    lcdHardwareData();
    lcdHardwarePutW(x2);
    lcdHardwareRelease();
}

inline static void lcdControllerWinVert(lcd_coord_t y1, lcd_coord_t y2)
{
    lcdHardwareSelect();
    lcdHardwareCmd();
    lcdHardwarePutW(0x52);
    lcdHardwareData();
    lcdHardwarePutW(y1);
    lcdHardwareCmd();
    lcdHardwarePutW(0x53);
    lcdHardwareData();
    lcdHardwarePutW(y2);
    lcdHardwareRelease();
}

inline static void lcdControllerGRAMPos(lcd_coord_t x, lcd_coord_t y)
{
    lcdHardwareSelect();
    lcdHardwareCmd();
    lcdHardwarePutW(0x20);
    lcdHardwareData();
    lcdHardwarePutW(x);
    lcdHardwareCmd();
    lcdHardwarePutW(0x21);
    lcdHardwareData();
    lcdHardwarePutW(y);
    lcdHardwareRelease();
}


inline static void lcdControllerDirection(uint8_t dir)
{
    switch(dir)
    {
        default:
            lcdControllerPair(0x03, 0x10B0);
            break;
        case 1:
            lcdControllerPair(0x03, 0x10B8);
            break;
    }
}

inline static void lcdControllerFill(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2, lcd_color_t clr)
{
    int x, y;
    lcdControllerDirection(0);
    lcdControllerWinHoriz(x1, x2);
    lcdControllerWinVert(y1, y2);
    lcdControllerGRAMPos(x1, y1);
    lcdControllerCommand(LCD_GRAM_WR);
    lcdHardwareSelect();
    lcdHardwareData(); // We send datas only
    for(y=y1; y<=y2; y++)
        for(x=x1; x<=x2; x++)
            lcdControllerColor(clr);
    lcdHardwareRelease();
}

inline static void lcdControllerFillRect(lcd_coord_t x1, lcd_coord_t y1, lcd_coord_t x2, lcd_coord_t y2,
        lcd_color_t fgclr, lcd_color_t bgclr, lcd_width_t border)
{
    int x, y;
    lcdControllerDirection(0);
    lcdControllerWinHoriz(x1, x2);
    lcdControllerWinVert(y1, y2);
    lcdControllerGRAMPos(x1, y1);
    lcdControllerCommand(LCD_GRAM_WR);
    lcdHardwareSelect();
    lcdHardwareData(); // We send datas only
    for(y=y1; y<=y2; y++)
        for(x=x1; x<=x2; x++)
        {
            if((x<(x1+border)) ||
               (x>(x2-border)) ||
               (y<(y1+border)) ||
               (y>(y2-border)))
                lcdControllerColor(fgclr);
            else
                lcdControllerColor(bgclr);
        }
    lcdHardwareRelease();
}

inline static unsigned int sqrt_newton(int l)
{
      long temp , div;
      unsigned  rslt = (unsigned)l;
      if (l <=  0)
            return 0;
      else if (l & 0xFFFF0000L)
            if  (l & 0xFF000000L)
                  div  = 0x3FFF;
            else
                  div  = 0x3FF;
      else
            if  (l & 0x0FF00L)
                  div  = 0x3F;
            else
                  div  = (l > 4) ? 0x7 : l;
      while (1)
      {
            temp = l  / div + div;
            div =  temp >>  1;
            div += temp  & 1;
            if  (rslt > div)
                   rslt = (unsigned)div;
            else
            {
                  if (l / rslt == rslt - 1 && l % rslt == 0)
                        rslt--;
                  return rslt;
            }
      }
}

inline static void lcdControllerCircleFill(lcd_coord_t xc, lcd_coord_t yc, lcd_coord_t radius,
        lcd_color_t fgclr)
{
    int x, y;
    int r2 = radius*radius;
    for(y=0; y<radius; y++)
    {
        x = sqrt_newton(r2 - y*y);
        lcdControllerFill(xc-x, yc+y, xc+x, yc+y, fgclr);
        lcdControllerFill(xc-x, yc-y, xc+x, yc-y, fgclr);
    }
}

inline static void lcdControllerImageMono(
        lcd_coord_t x1, lcd_coord_t y1,
        lcd_coord_t x2, lcd_coord_t y2,
        const uint8_t* data)
{
    int x, y;
    lcdControllerDirection(0);
    lcdControllerWinHoriz(x1, x2);
    lcdControllerWinVert(y1, y2);
    lcdControllerGRAMPos(x1, y1);
    lcdControllerCommand(LCD_GRAM_WR);
    lcdHardwareSelect();
    lcdHardwareData(); // We send datas only
    for(y=y1; y<=y2; y++)
        for(x=x1; x<=x2; x++)
        {
            char d = *data++;
            lcdHardwarePutW(lcdGetColor(d, d, d));
        }
    lcdHardwareRelease();

}

#endif /* _LCD_PRIVATE */

/*
 * Controller like SPFD5408B or ILI9325
 * Commands compatible not full equal
 *
 * (0,0)                           (239,0)
 *      +-------------------------+
 *      |   ---> cmd 50           |
 *      |  |                      |
 *      |  |                      |
 *      |  V cmd 52               |
 *      |                         |
 *      |                         |
 *      |                         |
 *      |                         |
 *                 ....
 *                 ....
 *      |                         |
 *      |                         |
 *      +-------------------------+
 *          |                 |    (0,???)
 *         /                   \
 *        |                     |
 *        |_____________________|
 *  pins 36                      1
 *
 *  Pins:
 *    1 - NC
 *    2 - NC
 *    3 - NC
 *    4 - NC
 *    5 - NC
 *    6 - ResetB
 *    7 - Unknow connect to GND
 *    8 - Unknow connect to GND
 *    9 - Unknow connect to GND
 *   10 - Unknow connect to GND
 *   11 - DB15
 *   12 - DB14
 *   13 - DB13
 *   14 - DB12
 *   15 - DB11
 *   16 - DB10
 *   17 - DB9
 *   18 - DB8
 *   19 - Unknow connect to VDD
 *   20 - DB7
 *   21 - DB6
 *   22 - DB5
 *   23 - DB4
 *   24 - DB3
 *   25 - DB2
 *   26 - DB1
 *   27 - DB0
 *   28 - Unknow connect to VDD
 *   29 - #RD
 *   30 - #WR
 *   31 - RS
 *   32 - #CS
 *   33 - VSS (GND) 
 *   34 - VDD
 *   35 - LED- (9.6volt)
 *   36 - LED+ (9.6volt)
 *
 */

/**
 * @}
 */
    
#endif /* _LCD_CTL_ILI9325_H_ */

