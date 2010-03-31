/******************************************************************************
 * based on software from:
 * Copyright 2004, R O SoftWare
 * No guarantees, warrantees, or promises, implied or otherwise.
 * May be used for hobby or commercial purposes provided copyright
 * notice remains intact.
 * 
 * reduced to learn what has to be done to enable and use UART0
 *****************************************************************************/
#ifndef _UART0_H_
#define _UART0_H_

#include "uart_common.h"

void uart0Init(uint16_t baud, uint8_t mode, uint8_t fmode);
int uart0Putch(int ch);
uint16_t uart0Space(void);
const char *uart0Puts(const char *string);
int uart0TxEmpty(void);
void uart0TxFlush(void);
int uart0Getch(void);
int uart0GetLn(char* s, int maxlen);

#endif /* _UART0_H_ */

