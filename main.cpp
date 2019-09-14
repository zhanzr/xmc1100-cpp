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

namespace std {
	typedef decltype(nullptr) nullptr_t;
}

void test_normal_ptr(void) {
	cout << __func__ << endl;
	
	LED* p_auto_led1 (new LED(3));
	__IO uint32_t tmpTick;
	
		LED* p_auto_led2 = p_auto_led1; 
		
		tmpTick = g_Ticks;
		while((tmpTick+400) > g_Ticks) {
			__NOP();
			__WFI();
		}	
		
		p_auto_led2->Toogle(); 
		tmpTick = g_Ticks;
		while((tmpTick+400) > g_Ticks) {
			__NOP();
			__WFI();
		}				

		p_auto_led1->Toogle(); 	
		
		//Leaking memory
	cout << "exit " << __func__ << endl;		
}

void test_auto_ptr(void) {
	cout << __func__ << endl;

	auto_ptr<LED> p_auto_led1 (new LED(3));
	__IO uint32_t tmpTick;
	
		// Copy and transfer ownership. 																			
		// p_auto_led1 gets set to empty!
		auto_ptr<LED> p_auto_led2 = p_auto_led1; 
		
		tmpTick = g_Ticks;
		while((tmpTick+400) > g_Ticks) {
			__NOP();
			__WFI();
		}	
		
		// Works.
		p_auto_led2->Toogle(); 
		tmpTick = g_Ticks;
		while((tmpTick+400) > g_Ticks) {
			__NOP();
			__WFI();
		}				

		// Hopefully raises some NULL pointer exception.		
		p_auto_led1->Toogle(); 	
		
		//Will call destructor via the owner of the pointer
	cout << "exit " << __func__ << endl;
}
		
__declspec(noreturn) int main(void) {
	LED LED1(0);
	LED* pLED4 = new LED(4);
	
  /* System timer configuration */
  ::SysTick_Config(SystemCoreClock / HZ);
	
	cout<<"Start @"<<SystemCoreClock/1000000<<" MHz"<<endl;
	cout << XMC_LIB_MAJOR_VERSION << ' ' << XMC_LIB_MINOR_VERSION << ' ' << XMC_LIB_PATCH_VERSION <<endl;
		
	vector<uint32_t> vD;
//	vD.reserve(64);

	__IO uint32_t tmpTick;

	while (1) {
//		cout << hex << endl;
//		cout << setw(8);
//    cout << setfill('0');
//		cout << SystemCoreClock  << ' ' << &SystemCoreClock << endl;
//		cout << dec << endl;
		
		test_normal_ptr();
		
		cout << endl;
		tmpTick = g_Ticks;
		while((tmpTick+4000) > g_Ticks) {
			__NOP();
			__WFI();
		}		
		
		test_auto_ptr();	
		
		cout << endl;
		tmpTick = g_Ticks;
		while((tmpTick+4000) > g_Ticks) {
			__NOP();
			__WFI();
		}		
  }
}
