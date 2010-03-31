#include "config.h"
#include "system.h"

#include "irq.h"
#include "utils.h"
#include "uart_proxy.h"

#include "lcd.h"

#include <string.h>

//extern void delayMs(int ms);
void delayMs(int ms)
{
    delay_us(ms*1000);
}

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
    FIO0DIR = 0x0FFF6000;
    FIO0CLR = 0xFFFFFFFF;
    FIO0SET = 0x0F006000;

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
    
    lcdSetFgColor(lcdGetColor(255, 0, 0));
    lcdBox(0, 0, 50, 100);
    lcdSetFgColor(lcdGetColor(0, 255, 0));
    lcdBox(50, 100, 100, 200);
    lcdSetFgColor(lcdGetColor(0, 0, 255));
    lcdBox(100, 200, 150, 300);

    lcdSetFgColor(lcdGetColor(255, 0, 255));
    lcdSetBgColor(lcdGetColor(0, 255, 0));
    lcdFillRect(100, 100, 200, 200, 3);

    while(1)
    {
    }

	return 0;	
}
