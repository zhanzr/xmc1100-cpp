#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xmc_gpio.h>
	

//Valid LED GPIO Pins for this application
//0, 7 
//0, 5
//0, 6 
//1, 4 
//1, 5 

class LED
{
	public:	
	static XMC_GPIO_MODE_t InitMode;
	static XMC_GPIO_MODE_t UnInitMode;
	
		LED(void);
		
		LED(uint8_t port, uint8_t pin, bool inv_logic);
	
		~LED(void);
		
		void Init(uint8_t port, uint8_t pin, bool inv_logic);
		void UnInit(uint8_t port, uint8_t pin);
	
		void On(void);
		void Off(void);		
		void Toogle(void);
		
	private:
		uint8_t m_Port;
		uint8_t m_Pin;
		bool m_IsInv;
		bool m_HasInit;
};

#ifdef __cplusplus
}
#endif
