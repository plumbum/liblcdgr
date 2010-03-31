/*
    LibLCDgr - Copyright (C) 2009-2010 Ivan A-R <ivan@tuxotronic.org>

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
 * @file lcd_mcu.h
 * @brief Hardware depended interface functions
 * @addtogroup McuDefinitions
 * @{
 */


#ifndef  _lcd_mcu_H_
#define  _lcd_mcu_H_

/**
 * lcd_config.h must be writed by user
 */
#include <lcd_config.h>

inline static void lcdHardwareInit(void);

inline static void lcdHardwareSelect(void);
inline static void lcdHardwareRelease(void);

inline static void lcdHardwareCmd(void);
inline static void lcdHardwareData(void);

inline static void lcdHardwarePut(uint8_t val);
inline static void lcdHardwarePutW(uint16_t val);

inline static uint8_t lcdHardwareGet(void);
inline static uint16_t lcdHardwareGetW(void);

/**
 * @}
 */

#endif   /* ----- #ifndef _lcd_mcu_H_  ----- */
