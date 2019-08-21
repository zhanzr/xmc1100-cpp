#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <typeinfo>

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

enum test_enum_type_1 {
	ENUM_1_0 = 0,
	ENUM_1_1,
	ENUM_1_2,
};

enum test_enum_type_2 {
	ENUM_2_0 = 0,
	ENUM_2_1 = 255,
	ENUM_2_2,
};

enum test_enum_type_3 {
	ENUM_3_0 = 0,
	ENUM_3_1 = 65535,
	ENUM_3_2,
};

enum test_enum_type_4 {
	ENUM_4_0 = 0,
	ENUM_4_1 = 4294967295,
	ENUM_4_2,
};

enum test_enum_type_5 {
	ENUM_5_0 = 0,
	ENUM_5_1 = 18446744073709551615,
//	ENUM_5_2,
};

enum test_enum_type_10: uint8_t {
	ENUM_10_0 = 0,
	ENUM_10_1 = 255,
//	ENUM_10_2,
};

enum test_enum_type_11: uint64_t {
	ENUM_11_0 = 0,
	ENUM_11_1 = 255,
	ENUM_11_2,
};

void test_enum_size(void) {
	cout << typeid(test_enum_type_1).name() << ": " << sizeof(test_enum_type_1) << endl;
	
	cout << typeid(test_enum_type_2).name() << ": " << sizeof(test_enum_type_2) << endl;
	
	cout << typeid(test_enum_type_3).name() << ": " << sizeof(test_enum_type_3) << endl;
	
	cout << typeid(test_enum_type_4).name() << ": " << sizeof(test_enum_type_4) << endl;
	
	cout << typeid(test_enum_type_5).name() << ": " << sizeof(test_enum_type_5) << endl;
	
	cout << typeid(test_enum_type_10).name() << ": " << sizeof(test_enum_type_10) << endl;
	
	cout << typeid(test_enum_type_11).name() << ": " << sizeof(test_enum_type_11) << endl;
}

int main(void) {
	LED LED1(0);
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
	vD.reserve(64);

	while (1) {			
		test_enum_size();
		
		LED1.Toogle();
		pLED4->Toogle();

		__IO uint32_t tmpTick;
		__IO uint32_t deltaTick;
		
		tmpTick = g_Ticks;
		while((tmpTick+4000) > g_Ticks) {
			__NOP();
			__WFI();
		}
		
		vD.clear();
		cout<<endl<<"generate 10 rand number and push to the vector:"<<endl;		
		for(auto i=0; i<10; ++i) {
			vD.push_back(rand());
			cout<<vD.at(i)<<' ';			
		}
		cout<<endl<<"Now sort them and the result:"<<endl;
			
		sort(vD.begin(), vD.end());
		
		for(auto i=0; i<vD.size(); ++i) {
			cout<<vD.at(i)<<' ';		
		}
		
		cout<<endl<<"sum: "<< accumulate(vD.begin(), vD.end(), 0)<<" capacity: "<<vD.capacity()<<endl;			
		
		::XMC_RTC_GetTime(&now_rtc_time);
		cout<<now_rtc_time.hours<<":"<<now_rtc_time.minutes<<":"<<now_rtc_time.seconds<<endl;	
  }
}
