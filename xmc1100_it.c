#include <XMC1100.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>

#include "dbg.h"
#include "serial.h"

extern __IO uint32_t g_Ticks;

void HardFault_Handler(void)
{
	
	while(1)
	{;}
}

void SVC_Handler(void)
{
	
	while(1)
	{;}
}

void PendSV_Handler(void)
{
	
	while(1)
	{;}
}

void SysTick_Handler(void)
{	
	g_Ticks++;
}

void SCU_0_IRQHandler(void)
{
	
	while(1)
	{;}
}

//RTC Alarm
void SCU_1_IRQHandler(void) {
	while(1)
	{;}
}
                 
void SCU_2_IRQHandler(void) {
	while(1)
	{;}
}

void ERU0_0_IRQHandler(void)
{
	
	while(1)
	{;}
}

void ERU0_1_IRQHandler(void)
{
	
	while(1)
	{;}
}
                   
void ERU0_2_IRQHandler(void)
{
	
	while(1)
	{;}
}

void ERU0_3_IRQHandler(void)
{
	
	while(1)
	{;}
}     
       
void USIC0_0_IRQHandler(void) {
  static uint8_t data;

  data = XMC_UART_CH_GetReceivedData(SERIAL_UART);
}

void USIC0_1_IRQHandler(void)
{
	
	while(1)
	{;}
}

void USIC0_2_IRQHandler(void)
{
	
	while(1)
	{;}
}

void USIC0_3_IRQHandler(void)
{
	
	while(1)
	{;}
}        
       
void USIC0_4_IRQHandler(void)
{
	
	while(1)
	{;}
}

void USIC0_5_IRQHandler(void)
{
	
	while(1)
	{;}
}

void VADC0_C0_0_IRQHandler(void)
{
	
	while(1)
	{;}
}      
      
void VADC0_C0_1_IRQHandler(void)
{
	
	while(1)
	{;}
}

void CCU40_0_IRQHandler(void)
{
	
	while(1)
	{;}
}

void CCU40_1_IRQHandler(void)
{
	
	while(1)
	{;}
}   
      
void CCU40_2_IRQHandler(void)
{
	
	while(1)
	{;}
}

void CCU40_3_IRQHandler(void)
{
	
	while(1)
	{;}
} 
