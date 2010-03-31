#include "config.h"
#include "system.h"

#include "irq.h"
#include "utils.h"
#include "i2c.h"
#include "eeprom.h"
#include "uart_proxy.h"

#include "lcd.h"

#include <string.h>

char volatileCheck(void);

char volatileCheck(void)
{
    uint8_t buf[16];
    eepromRead(buf, 0, 16);
    if((buf[0] == 'R') ||
       (buf[1] == 'f') ||
       (buf[2] == 'C') ||
       (buf[3] == 'k'))
    {
        uint32_t rstcnt;
        // TODO check CRC16
        rstcnt = (buf[4]<<24) | (buf[5]<<16) | (buf[6]<<8) | buf[7];
        rstcnt++;
        buf[4] = (rstcnt>>24) & 0xFF;
        buf[5] = (rstcnt>>16) & 0xFF;
        buf[6] = (rstcnt>>8) & 0xFF;
        buf[7] = (rstcnt>>0) & 0xFF;

        udbgPuts("Reset device #");
        udbgPutHexDump(&buf[4], 4);
        udbgPutEOLN();

        // TODO recalculate CRC16
        eepromWrite(buf, 0, 16);
        return 0;
    }
    else
    {
        udbgPutsLn("Init device");
        int i;
        for(i=4; i<16; i++)
            buf[i] = 0;
        buf[0] = 'R'; // Magic word 'RfCk'
        buf[1] = 'f';
        buf[2] = 'C';
        buf[3] = 'k';

        // TODO recalculate CRC16
        eepromWrite(buf, 0, 16);
        return -1;
    }
}

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

#define bufLnSize 256
char bufLn[bufLnSize];
char buf2[bufLnSize];

int main(void)
{
	sysInit();
    FIO0DIR = 0x0FFF6000;
    FIO0CLR = 0xFFFFFFFF;
    FIO0SET = 0x0F006000;

    //initVIC(dummyISR); 

    i2cInit();

    uartInit();
    udbgPutEOLN();
	udbgPutsLn("LCD 2.4\" test");
	udbgPutsLn("(l) 2010, Ivan A-R <ivan@tuxotronic.org>");
    udbgPuts("PCLK=");
    udbgPutUint(PCLK);
    udbgPutsLn(" Hz");

    volatileCheck();

    // enableIRQFIQ();
#if 1
    FIO0SET = (1<<13);
    delayMs(100);
    FIO0CLR = (1<<13);
    delayMs(100);
    FIO0SET = (1<<13);
    delayMs(100);

#define RD FIO0CLR = (1<<26)
#define uRD FIO0SET = (1<<26)
#define WR FIO0CLR = (1<<27)
#define uWR FIO0SET = (1<<27)
#define RSdat FIO0SET = (1<<24)
#define RScmd FIO0CLR = (1<<24)
#define CS FIO0CLR = (1<<25)
#define uCS FIO0SET = (1<<25)

    int i;
    for(i=0; i<64; i++)
    {
        /* Write cmd */
        FIO0DIR |= (0xFF<<16);
        RScmd;
        uRD;
        WR;
        FIO0CLR = (0xFF<<16);
        delayMs(1);
        CS;
        delayMs(1);
        uCS;
        delayMs(1);
        CS;
        delayMs(1);
        uCS;

        /* Read data */
        FIO0DIR &= ~(0xFF<<16);
        FIO0SET = (0xFF<<16);

        RSdat;
        uWR;
        RD;
        delayMs(1);
        CS;
        delayMs(1);
        uint8_t hbyte = (FIO0PIN>>16) & 0xFF;
        uCS;
        delayMs(1);
        CS;
        delayMs(1);
        uint8_t lbyte = (FIO0PIN>>16) & 0xFF;
        uCS;

        udbgPuts("Read: ");
        udbgPutHex(i);
        udbgPuts(" ");
        udbgPutHex(hbyte);
        udbgPutHex(lbyte);
        udbgPutEOLN();
    }
#endif

    FIO0CLR = (1<<13);
    delayMs(100);
    FIO0SET = (1<<13);
    delayMs(100);

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
