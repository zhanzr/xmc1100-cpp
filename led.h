#pragma once

#include <utility> 

#include <assert.h>      

#include <xmc_gpio.h>

//Valid LED GPIO Pins for this application
//0, 7 
//0, 5
//0, 6 
//1, 4 
//1, 5 

typedef std::pair <XMC_GPIO_PORT_t*, uint8_t> led_position_pair;
	
class LED
{
	public:	
	static XMC_GPIO_MODE_t InitMode;
	static XMC_GPIO_MODE_t UnInitMode;
	
	static const uint8_t LED_COUNT = 5;
		
		LED(void);
		
		LED(const uint8_t num);
	
		~LED(void);
		
		void Init(const bool inv_logic);
		void UnInit(void);
	
		void On(void);
		void Off(void);		
		void Toogle(void);
		
	private:
		uint8_t m_num;
		bool m_IsInv;
		bool m_HasInit;
};

