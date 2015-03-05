#include "uart.h"
#include "led.h"
#include "MK70F12.h"

/**
* This function initializes UART2, which is the module responsible for USB to Serial Bridge communication.
*/
void uart_init() {

	// enable clock signal to Port E
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// enable clock gating to UART 2
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;

	// ensure correct baud rate is set up to 115200
	// UART baud rate = UART module clock / (16 × (SBR[12:0] + BRFD))
	// 115200 = 50MHz / (16 x (SBR[12:0] + 0)) --> SRB[12:0] ~= 27
	UART2_BDL = 27;

	// set the RE bit --> enables UART2 receiver
	UART2_C2 |= UART_C2_RE_MASK;
	// set the TE bit --> enables UART2 transmitter
	UART2_C2 |= UART_C2_TE_MASK;

	// write to pin command register so that UART2 transmitter (Tx) is selected
	PORTE_PCR17 = PORT_PCR_MUX(3); // use ALT3 (UART2_TX)
	// write to pin command register so that UART2 receiver (Rx) is selected
	PORTE_PCR16 = PORT_PCR_MUX(3); // use ALT3 (UART2_RX)

}

/**
* This function polls the UART2 receive data register. If data register is not
* completely full, then it returns 0. If the data register is completely full,
* and therefore ready to read, then it returns 1.
*/
int uart_data_available() {
	
	return (UART2_S1 & UART_S1_RDRF_MASK);

}

/**
* This function blocks reads 8 bits from the UART2 data register. It will
* block until the receive data register is completely full, so as to not
* receive partial messages.
*/
char uart_receive() {

	// wait until the UART receieve data register is full of received data
	while (!(UART2_S1 & UART_S1_RDRF_MASK)) {}
	// debug tool
	led_toggle(LED_GREEN);

	// return the contents of the data register
	return UART2_D;
	
}

/**
* This function writes 8 bits to the UART2 data register, which in turn causes the UART
* to transmit the data. It will block until the send data register is empty, so as to not
* overwrite previous transmissions before they have completed.
*/
void uart_transmit(char message) {

	// wait until the UART transmit data register is empty of any data
	while (!(UART2_S1 & UART_S1_TDRE_MASK)) {}
	// debug tool
	led_toggle(LED_YELLOW);

	// write to the transmit data register to prompt UART transmission
	UART2_D = message;
	
}
