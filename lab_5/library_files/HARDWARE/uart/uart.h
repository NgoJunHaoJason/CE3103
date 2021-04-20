#ifndef __UART_H
#define __UART_H

#include "sys.h"
#include "system.h"

void uart_init(u32 baudRate);
void uart_task(void *pvParameters);
void usart3_send(u8 data);
int USART3_IRQHandler(void);

#endif
