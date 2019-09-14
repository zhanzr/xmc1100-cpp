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
#include <iomanip>

#include <XMC1100.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>
#include <xmc_uart.h>
#include <xmc_gpio.h>

#include "led.h"
#include "dbg.h"
#include "serial.h"

using namespace std;

__IO uint32_t g_Ticks;

const uint32_t TEST_GENERATE_SIZE = 32;

XMC_GPIO_CONFIG_t uart_tx;
XMC_GPIO_CONFIG_t uart_rx;

/* UART configuration */
#ifdef __cplusplus
// before C++ 20, C style partial initialization not supported
const XMC_UART_CH_CONFIG_t uart_config = {	
  SERIAL_BAUDRATE,	// baudrate
  false,	// normal_divider_mode
	8U,	// data_bits
	0,	// frame_length
  1U,	// stop_bits
	0, // oversampling
	XMC_USIC_CH_PARITY_MODE_NONE, // parity_mode
};
#else
const XMC_UART_CH_CONFIG_t uart_config = {	
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = SERIAL_BAUDRATE
};
#endif

int main(void) {
	LED LED1(0);
	LED LED2(1);
	LED* pLED4 = new LED(4);
	
  /* System timer configuration */
  ::SysTick_Config(SystemCoreClock / HZ);
	
 /*Initialize the UART driver */
	uart_tx.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
	uart_rx.mode = XMC_GPIO_MODE_INPUT_PULL_UP;
	/* Configure UART channel */
  XMC_UART_CH_Init(SERIAL_UART, &uart_config);
  XMC_UART_CH_SetInputSource(SERIAL_UART, XMC_UART_CH_INPUT_RXD, SERIAL_RX_INPUT);
  
  /* Set service request for receive interrupt */
  XMC_USIC_CH_SetInterruptNodePointer(SERIAL_UART, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 0U);
  XMC_USIC_CH_SetInterruptNodePointer(SERIAL_UART, XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE, 0U);

  /*Set priority and enable NVIC node for receive interrupt*/
  NVIC_SetPriority(SERIAL_RX_IRQN, 3);
  NVIC_EnableIRQ(SERIAL_RX_IRQN);

  XMC_UART_CH_EnableEvent(SERIAL_UART, XMC_UART_CH_EVENT_STANDARD_RECEIVE | XMC_UART_CH_EVENT_ALTERNATIVE_RECEIVE);
	
	/* Start UART channel */
  XMC_UART_CH_Start(SERIAL_UART);

  /* Configure pins */
	XMC_GPIO_Init(SERIAL_TX_PIN, &uart_tx);
  XMC_GPIO_Init(SERIAL_RX_PIN, &uart_rx);
	
	cout<<"Start @"<<SystemCoreClock/1000000<<" MHz"<<endl;
	cout << XMC_LIB_MAJOR_VERSION << ' ' << XMC_LIB_MINOR_VERSION << ' ' << XMC_LIB_PATCH_VERSION <<endl;
		
	vector<uint32_t> vD;
//	vD.reserve(64);

	while (1) {
		cout << hex << endl;
		cout << setw(8);
    cout << setfill('0');
		cout << SystemCoreClock  << ' ' << &SystemCoreClock << endl;
		cout << dec << endl;
		
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
