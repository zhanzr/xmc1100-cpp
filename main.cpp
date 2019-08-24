#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <numeric>
#include <limits>

#include <typeinfo>
#include <map>
#include <string>
#include <functional>
#include <memory>

#include <XMC1100.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>
#include <xmc_uart.h>
#include <xmc_gpio.h>
#include "led.h"
#include "dbg.h"

using namespace std;

#define UART_RX P1_3
#define UART_TX P1_2

XMC_GPIO_CONFIG_t uart_tx;
XMC_GPIO_CONFIG_t uart_rx;

__IO uint32_t g_Ticks;

const uint32_t TEST_GENERATE_SIZE = 32;
	
LED LED1(0);
LED LED2(1);

int main(void) {
	LED* pLED4 = new LED(4);
	
  /* System timer configuration */
  ::SysTick_Config(SystemCoreClock / 1000);
	
  /*Initialize the UART driver */
	XMC_UART_CH_CONFIG_t uart_config;
	uart_tx.mode = ::XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
	uart_rx.mode = ::XMC_GPIO_MODE_INPUT_TRISTATE;
 /* Configure UART channel */
  uart_config.data_bits = 8U;
  uart_config.stop_bits = 1U;
  uart_config.baudrate = 921600;
  uart_config.frame_length = 8;
	uart_config.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE;
  ::XMC_UART_CH_Init(XMC_UART0_CH1, &uart_config);
  ::XMC_UART_CH_SetInputSource(XMC_UART0_CH1, XMC_UART_CH_INPUT_RXD,USIC0_C1_DX0_P1_3);
  ::XMC_UART_CH_EnableEvent(XMC_UART0_CH1, XMC_UART_CH_EVENT_STANDARD_RECEIVE);
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 0);	
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 1);
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 2);
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 3);
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 4);
	::XMC_UART_CH_SetInterruptNodePointer(XMC_UART0_CH1, 5);

	/* Start UART channel */
  ::XMC_UART_CH_Start(XMC_UART0_CH1);

  /* Configure pins */
	::XMC_GPIO_Init(UART_TX, &uart_tx);
  ::XMC_GPIO_Init(UART_RX, &uart_rx);
	
	cout<<"Start @"<<SystemCoreClock/1000000<<" MHz"<<endl;
	cout << XMC_LIB_MAJOR_VERSION << ' ' << XMC_LIB_MINOR_VERSION << ' ' << XMC_LIB_PATCH_VERSION <<endl;

	XMC_RTC_TIME_t now_rtc_time;	
	XMC_RTC_CONFIG_t rtc_config;
	XMC_RTC_TIME_t init_rtc_time;	
	//RTC
  rtc_config.time.seconds = 5U;
  rtc_config.prescaler = 0x7fffU;	
  ::XMC_RTC_Init(&rtc_config);
	
	init_rtc_time.year = 2019;
	init_rtc_time.month = XMC_RTC_MONTH_JULY;
	init_rtc_time.daysofweek = XMC_RTC_WEEKDAY_TUESDAY;
	init_rtc_time.days = 17;
	init_rtc_time.hours = 5;
	init_rtc_time.minutes = 6;
	init_rtc_time.seconds = 55;		
	::XMC_RTC_SetTime(&init_rtc_time);
	
//  XMC_RTC_EnableEvent(XMC_RTC_EVENT_PERIODIC_SECONDS);
//  XMC_SCU_INTERRUPT_EnableEvent(XMC_SCU_INTERRUPT_EVENT_RTC_PERIODIC);
//  NVIC_SetPriority(SCU_1_IRQn, 3);
//  NVIC_EnableIRQ(SCU_1_IRQn);
  ::XMC_RTC_Start();
		
	vector<uint32_t> vD;
//	vD.reserve(64);

	while (1) {			
//		test_enum_size();
//		test_typeinfo();	
		vD.clear();
		cout<<endl<<"generate " << TEST_GENERATE_SIZE << " rand number and push to the vector:"<<endl;		
		for(auto i=0; i<TEST_GENERATE_SIZE; ++i) {
			vD.push_back(rand());
			cout<<vD.at(i)<<' ';			
		}
		cout<<endl<<"Now sort them and the result:"<<endl;
			
		sort(vD.begin(), vD.end());
		
		for(auto i=0; i<vD.size(); ++i) {
			cout<<vD.at(i)<<' ';		
		}
		
		cout<<endl<<"sum: "<< accumulate(vD.begin(), vD.end(), 0)<< " size: "<< vD.size() <<" capacity: "<<vD.capacity()<<endl;			
		cout<<endl<<"generate " << TEST_GENERATE_SIZE << " rand number and push to the vector:"<<endl;		
		for(auto i=0; i<TEST_GENERATE_SIZE; ++i) {
			vD.push_back(rand());
			cout<<vD.at(i)<<' ';			
		}
		cout<<endl<<"sum: "<< accumulate(vD.begin(), vD.end(), 0) << " size: "<< vD.size() << " capacity: "<<vD.capacity()<<endl;			
		
		::XMC_RTC_GetTime(&now_rtc_time);
		cout<<now_rtc_time.hours<<":"<<now_rtc_time.minutes<<":"<<now_rtc_time.seconds<<endl;	
				
		LED1.Toogle();
		pLED4->Toogle();
		LED2.Toogle();
		
		__IO uint32_t tmpTick;
		__IO uint32_t deltaTick;
		
		tmpTick = g_Ticks;
		while((tmpTick+4000) > g_Ticks) {
			__NOP();
			__WFI();
		}		
  }
}
