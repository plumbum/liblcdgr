#include "config.h"
#include "system.h"

#include "irq.h"
#include "utils.h"
#include "uart_proxy.h"

#include "lcd.h"

#include <string.h>

/*
static void dummyISR(void) __attribute__ ((interrupt));
static void dummyISR(void)
{
  //do something... for example print some serious error message
}
*/

int main(void)
{
	sysInit();
    /*
    FIO0DIR = 0x0FFF6000;
    FIO0CLR = 0xFFFFFFFF;
    FIO0SET = 0x0F006000;
    */
    FIO0DIR = 0x00000000;
    FIO0CLR = 0xFFFFFFFF;
    FIO0SET = 0x00000000;

    //initVIC(dummyISR); 

    uartInit();
    udbgPutEOLN();
	udbgPutsLn("LCD 2.4\" test");
	udbgPutsLn("(l) 2010, Ivan A-R <ivan@tuxotronic.org>");
    udbgPuts("PCLK=");
    udbgPutUint(PCLK);
    udbgPutsLn(" Hz");

    // enableIRQFIQ();
    lcdInit();

    lcdSetBgColor(lcdGetColor(0, 255, 255));
    lcdClean();
    
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

    for(;;)
    {
        int i;
        for(i=0; i<8; i++)
        {
            int color = color_table[i];
            int j;
            for(j=0; j<4; j++)
            {
                int x = 0;
                int y = 0;
                int clr = 0;
                switch(j) {
                    case 0: clr = color; x = 0; y = 0; break;
                    case 1: clr = 7*color/8; x = 16; y = 0; break;
                    case 2: clr = 6*color/8; x = 0; y = 16; break;
                    case 3: clr = 5*color/8; x = 16; y = 16; break;
                }
                int xx, yy;
                lcdSetFgColor(clr);
                for(yy=y; yy<320; yy+=32)
                    for(xx=x; xx<240; xx+=32)
                        lcdBox(xx, yy, xx+15, yy+15);

            }
            delay_ms(50);
        }
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

	return 0;	
}
