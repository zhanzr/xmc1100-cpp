#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <XMC1100.h>
#include <xmc_uart.h>
#include "dbg.h"

int stdout_putchar (int ch) {
	XMC_UART_CH_Transmit(XMC_UART0_CH1, ch);
	return ch;
}

void ttywrch (int ch) {
	XMC_UART_CH_Transmit(XMC_UART0_CH1, ch);
}
