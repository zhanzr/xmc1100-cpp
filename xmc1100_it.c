#include <XMC1100.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>

#include "dbg.h"
#include "serial.h"

extern __IO uint32_t g_Ticks;

void SysTick_Handler(void) {	
	g_Ticks++;
}     
       
void USIC0_0_IRQHandler(void) {
  static uint8_t data;
  data = XMC_UART_CH_GetReceivedData(SERIAL_UART);
}
