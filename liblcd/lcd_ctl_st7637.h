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
 * @file lcd_ctl_st7637.h
 * @brief ST7637 COG based LCD graphical library
 * @addtogroup LcdChipDefinitions
 * @{
 */

/**
 *
 * Tested on:
 *   LCD with COG like ST7637
 *   Maked:
 *     DFM-076B-NL-WD.HKYA064
 *     BG999076A-V0.1-DG 081121 B2
 *
 *   Parallel interface. 27 pin flat cable
 *    1. VCC (3.0V, but it probably works at 3.3V too)
 *    2. GND
 *    3. -
 *    4. -
 *    5. CS# (Chip Select)
 *    6. D/C# (Data/Command)
 *    7. RD# (Read)
 *    8. WR# (Write)
 *    9. RST#
 *    0. D0
 *   11. -
 *   12. D1
 *   13. -
 *   14. D2
 *   15. -
 *   16. D3
 *   17. -
 *   18. D4
 *   19. -
 *   20. D5
 *   21. -
 *   22. D6
 *   23. -
 *   24. D7
 *   25. -
 *   26. LED Cathode (-3V)
 *   27. LED Anode   (+3V)
 *
 * ST7637 page: http://www.sitronix.com.tw/sitronix/product.nsf/Doc/ST7637?OpenDocument
 *
 */

#ifndef _LCD_CTL_ST7637_H_
#define _LCD_CTL_ST7637_H_

typedef uint16_t lcdvalue_t;
typedef uint16_t lcdcolor_t;


#include "lcd_ctl.h"

#define LCD_NEED_FONT_SWAP

/* Define logical display size in pixels */
#define LCD_WIDTH 128
#define LCD_HEIGHT 128
#define LCD_LEFT 4
#define LCD_RIGHT 0x83
#define LCD_TOP 4
#define LCD_BOTTOM 0x83

#define LCD_GRAM_WR         0x2C

// TODO make correct
#define FGCLR_DEFAULT       0xFFFF
#define BGCLR_DEFAULT       0x0000

#define LCD_INIT_DELAY25MS  (1<<5)
#define LCD_INIT_DELAY50MS  (2<<5)
#define LCD_INIT_DELAY75MS  (3<<5)
#define LCD_INIT_DELAY100MS (4<<5)
#define LCD_INIT_DELAY125MS (5<<5)
#define LCD_INIT_DELAY150MS (6<<5)
#define LCD_INIT_DELAY175MS (7<<5)

static const char lcd_init[] = {
    LCD_INIT_DELAY150MS |   0 , 0x01,           // Software reset
                            1 , 0xD7, 0xBF,     // Auto load set disable

    LCD_INIT_DELAY25MS  |   1 , 0x0E, 0x00,     // Control OTP WR/RD
    LCD_INIT_DELAY25MS  |   0 , 0xE3,           // Read from OTP
                            0 , 0xE1,           // OTP control cancel
                            0 , 0x28,           // Display off
    LCD_INIT_DELAY25MS  |   0 , 0x11,           // Sleep out & booster on

                            1 , 0xC3, 0x01, // Bias 1/12 (0x00)
                            1 , 0xC4, 0x06, // Setting Booster times X8 (0x05)
                            1 , 0xC5, 0x01, // Booster eff BE = 0x01 (Level 2) (0x011)
                            1 , 0xCB, 0x01, // Vg with booster x2 conol, Vg from Vdd2 (0x01)
                            // ID1 = 00 0xCC
                            // ID3 = 00 0xCE
                            1 , 0xB7, 0xC8, // Glass direction (0xC0)
                            1 , 0xD0, 0x1D, // Analog circuit setting
                            1 , 0xD7, 0xBF,
                            1 , 0xB5, 0x87,
                            1 , 0xB4, 0x18, // PTL mode set, power normal mode
                            0 , 0x20,           // Display inversion off (normal) 
                            1 , 0x3A, 0x05, // Color mode = 65k
                            1 , 0x36, 0x00, // Memory Access Control
                            0 , 0x29,           // Display on
                            1 , 0xB0, 0x83, // Duty = 132 duty (0x7F)

//                            2 , 0xC0, 0x00, 0x01, // Set Vop by init Module Vop = 13.64 (0xFB, 0x00)
                            2 , 0xC0, 0xF6, 0x00, // Set Vop by init Module Vop = 13.64 (0xFB, 0x00)

//                            16, 0xF9, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, // Gamma
//                                      0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E,
//                            0 , 0xF0,
                            0 , 0x38,           // Idle mode off
                            1 , 0xB1, 0x00,
                            1 , 0xB3, 0x00,
                            4 , 0xF0, 0x06, 0x0B, 0x14, 0x1B,
                            1 , 0xF3, 0x04,
                            3 , 0xF2, 0x1E, 0x28, 0x32,
                            8 , 0xF4, 0x00, 0x55, 0x60, 0xF0, 0xA3, 0xF9, 0x6F, 0xFF,
                            16, 0xF9, 0x00, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F,
                                      0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F,

                            2 , 0x2A, 0x00, 0x7F,
                            2 , 0x2B, 0x04, 0x83,
                            0 , 0x2C,
                            255
};

/**
 * Make 16bit color from RGB 8bit color components
 */
#define lcdGetColor(r, g, b) (lcdcolor_t)(((r&0xF8)<<8) | ((g&0xFC)<<3) | (b>>3))

#define lcdControllerColor(color) lcdHardwareValueW(color)

inline static void lcdControllerInit(void)
{
    char* pinit = (char*)lcd_init;
    char len;
    while((len = *pinit++) != 255)
    {
        lcdControllerCommand(*pinit++); // Get and send command
        int cnt;
        for(cnt=0; cnt<(len&0x1F); cnt++) // and send datas if needed
            lcdControllerData(*pinit++);
        if(len & 0xE0) // Delay after command if needed
            delayMs(25 * ((len&0xE0)>>5));
    }

    delayMs(10);
}

inline static void lcdControllerCommand(lcdvalue_t cmd)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(cmd);
    lcdHardwareCSRelease();
}

inline static void lcdControllerData(lcdvalue_t data)
{
    lcdHardwareCSGrab();
    lcdHardwareRSData();
    lcdHardwareValueB(data);
    lcdHardwareCSRelease();
}

/**
 * Send command and data pair to controller
 * @param cmd - command word
 * @param data - data word
 */
static void lcdControllerPair(lcdvalue_t cmd, lcdvalue_t data)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(cmd);
    lcdHardwareRSData();
    lcdHardwareValueB(data);
    lcdHardwareCSRelease();
}

/**
 * Same as lcdControllerPair
 * Don't release CS after return.
 * Release CS manually with function lcdHardwareCSRelease()
 * @param cmd - command word
 * @param data - data word
 */
/*
inline static void lcdControllerPairLong(lcdvalue_t cmd, lcdvalue_t data)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(cmd);
    lcdHardwareRSData();
    lcdHardwareValueB(data);
}
*/

inline static void lcdControllerWinHoriz(uint16_t x1, uint16_t x2)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(0x2A);
    lcdHardwareRSData();
    lcdHardwareValueB(x1);
    lcdHardwareValueB(x2);
    lcdHardwareCSRelease();
}
    
inline static void lcdControllerWinVert(uint16_t y1, uint16_t y2)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(0x2B);
    lcdHardwareRSData();
    lcdHardwareValueB(y1);
    lcdHardwareValueB(y2);
    lcdHardwareCSRelease();
}

inline static void lcdControllerGRAMPos(uint16_t x, uint16_t y)
{
    lcdHardwareCSGrab();
    lcdHardwareRSCmd();
    lcdHardwareValueB(0x2C);
    lcdHardwareRSData();
    lcdHardwareValueB(x);
    lcdHardwareValueB(y);
    lcdHardwareCSRelease();

}

#define MV 5
#define MX 6
#define MY 7

inline static void lcdControllerDirection(uint8_t dir)
{
    lcdControllerPair(0x36, (dir & 7)<<5);
    /*
    switch(dir & 0x03)
    {
        default:
            lcdControllerPair(0x36, (0<<MV) | (0<<MX) | (0<<MY));
            break;
        case 1: // CW - 90
            lcdControllerPair(0x36, (1<<MV) | (1<<MX) | (0<<MY));
            break;
        case 2: // CW - 180
            lcdControllerPair(0x36, (0<<MV) | (1<<MX) | (1<<MY));
            break;
        case 3: // CW - 270
            lcdControllerPair(0x36, (1<<MV) | (0<<MX) | (1<<MY));
            break;
    }
    */
}

/**
 * @}
 */
    
#endif /* _LCD_CTL_ST7637_H_ */

