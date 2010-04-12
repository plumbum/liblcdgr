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

/*
#include "fnt.h"

void printChar(int x, int y, char c)
{
    int j;
    char* p = header_data[c*32];

    for(j=0; j<48; j++)
    {
        lcdImageMono(x, y+j, 32, 48, p);
        p += 544;
    }
}
*/

int main(void)
{
	sysInit();
    FIO0DIR = 0x00000000 | (1<<3);
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
            FIO0SET = (1<<3);
            int color = color_table[i];
            lcdSetFgColor(color);
            FIO0CLR = (1<<3);
            lcdCircleFill(120, 160, 103);
        }
    }

    for(;;)
    {
        int i;
        for(i=0; i<8; i++)
        {
            int color = color_table[i];
            int r;
            for(r=0; r<=100; r++)
            {
                lcdSetFgColor(color);
                lcdCircleFill(120, 160, r);
            }
        }
    }

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
