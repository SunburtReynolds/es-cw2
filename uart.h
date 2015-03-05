#ifndef UART_H__
#define UART_H__

extern void uart_init();
extern void uart_transmit(char c);
extern char uart_receive();
extern int uart_data_available();

#define UART_EMPTY 0
#define UART_FULL 1

#endif
