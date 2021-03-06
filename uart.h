#ifndef UART_H
#define UART_H

#include <string.h>
#include <stdlib.h>

void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);
char USART_need_rx_update(void);
void USART_unset_rxb_update(void);
void USART_copy_rxb(void);
char* USART_get_last_message(void);
char USART_get_tx_status(void);

#endif
