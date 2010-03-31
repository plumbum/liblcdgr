#ifndef _UART_PROXY_H_
#define _UART_PROXY_H_

#include "uart0.h"

#define DBGEOLN "\r\n"

inline static void uartInit(void)
{
	uart0Init(B115200, UART_8N1, UART_FIFO_8); // setup the UART0 - debug uart
}

#define udbgPutch(c) uart0Putch(c)
#define udbgPuts(str) uart0Puts(str)
#define udbgGetch() uart0Getch()
#define udbgGetLn(str, maxlen) uart0GetLn(str, maxlen)

#define udbgPutEOLN() udbgPuts(DBGEOLN)

inline static void udbgPutsLn(const char* s)
{
    udbgPuts(s);
    udbgPutEOLN();
}

void udbgPutHex(uint8_t a);
void udbgPutHex16(uint16_t a);
void udbgPutHex32(uint32_t a);
void udbgPutHexDump(const uint8_t* data, int len);

void udbgPutUint(uint32_t val);
void udbgPutInt(int32_t val);


#endif /* _UART_PROXY_H_ */

