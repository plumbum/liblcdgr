/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Digital photo frame based on AT90USB162 
 *
 *        Version:  1.0
 *        Created:  Wed, 21 Oct 2009 13:38:11 +0400
 *       Revision:  $Id$
 *       Compiler:  gcc
 *
 *         Author:  Ivan A-R <ivan@tuxotronic.org>
 *        License:  GPL v3
 *
 * =====================================================================================
 */

#include "config.h"

#include <string.h>
#include <stdio.h>

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "helpers.h"
#include "lcd.h"

char getKeys(void)
{
    char r;
    DDRD &= ~0x7E;
    PORTD |= 0x7E;
    _delay_us(10);
    r = PIND & 0x7E;
    DDRD |= 0x7E;
    return r;
}

#define PWR_ON PORTC &= ~(1<<PRF_PWR);
#define PWR_OFF PORTC |= (1<<PRF_PWR);

int main(void)
{
#ifdef WDT_ENABLE
#error TODO fix watchdog
    wdt_enable(WDTO_15MS);
#else
    MCUSR &= ~(1 << WDRF);
    wdt_disable();
#endif
    
    CLKPR = 0x80;
    CLKPR = 0x00;

    /*
    PORTB = (1<<LCD_CS) | (1<<LCD_RS);
    DDRB =  (1<<LCD_CS) | (1<<LCD_RS) | (1<<LCD_D0) | (1<<LCD_D7);

    PORTC = (1<<LCD_RST) | (1<<LCD_WR) | (1<<PRF_PWR);
    DDRC = (1<<LCD_RST) | (1<<LCD_WR) | (1<<PRF_PWR) | (1<<BUZZER);

    PORTD = 0xFF;
    DDRD = 0x7F;
    */

    PORTB = 0;
    DDRB =  0;

    PORTC = (1<<PRF_PWR);
    DDRC =  (1<<PRF_PWR) | (1<<BUZZER);

    PORTD = 0xFF;
    DDRD =  0x7F;

//    PRR0 = 0;
    TCCR0A = (0<<COM0A0) | (2<<COM0B0) | (3<<WGM00);
    TCCR0B = (1<<WGM02) | (1<<CS00);
    OCR0A = 80;
    OCR0B = 22;

    PWR_ON;

    lcdInit();

    lcdSetBgColor(lcdGetColor(0, 255, 255));
    lcdClean();
    
    uint16_t x, y;
    for(y=0; y<320; y += 20)
        for(x=0; x<240; x += 15)
        {
            lcdSetFgColor(lcdGetColor(x, 2*y/3, 0));
            lcdBox(x, y, x+14, y+19);
        }
    /*
    lcdSetFgColor(lcdGetColor(255, 0, 0));
    lcdBox(0, 0, 50, 100);
    lcdSetFgColor(lcdGetColor(0, 255, 0));
    lcdBox(50, 100, 100, 200);
    lcdSetFgColor(lcdGetColor(0, 0, 255));
    lcdBox(100, 200, 150, 300);

    lcdSetFgColor(lcdGetColor(255, 0, 255));
    lcdSetBgColor(lcdGetColor(0, 255, 0));
    lcdFillRect(100, 100, 200, 200, 3);
    */

    const int color_table[] = {
        lcdGetColor(0, 0, 0),
        lcdGetColor(0, 0, 255),
        lcdGetColor(0, 255, 0),
        lcdGetColor(0, 255, 255),
        lcdGetColor(255, 0, 0),
        lcdGetColor(255, 0, 255),
        lcdGetColor(255, 255, 0),
        lcdGetColor(255, 255, 255),
    };

    lcdSetFgColor(lcdGetColor(128, 128, 128));
    lcdCircleFill(120, 160, 103);

    lcdSetFgColor(lcdGetColor(0, 255, 0));
    lcdCircleFill(64, 64, 32);
    lcdSetFgColor(lcdGetColor(0, 0, 255));
    lcdCircleFill(240-64, 320-64, 32);
    lcdSetFgColor(lcdGetColor(255, 0, 0));
    lcdCircleFill(64, 320-64, 32);
    lcdSetFgColor(lcdGetColor(255, 255, 0));
    lcdCircleFill(240-64, 64, 32);

    for(;;)
    {
        int i;
        for(i=0; i<8; i++)
        {
            wdr();
            int color = color_table[i];
            lcdSetFgColor(color);
            lcdCircleFill(120, 160, 103);

            if((PIND & (1<<PD7)) == 0)
            {
                asm("jmp 0x3000");
            }
        }
    }
    return 0;
}

// vim: sw=4:ts=4:si:et
//
