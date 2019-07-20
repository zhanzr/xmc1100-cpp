#include <xmc_gpio.h>
#include "led.h"

//Valid LED GPIO Pins for this application
//0, 7 
//0, 5
//0, 6 
//1, 4 
//1, 5 

XMC_GPIO_MODE_t LED::InitMode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
XMC_GPIO_MODE_t LED::UnInitMode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;

//Default Constructor
LED::LED(void) {
	m_Port = 0;
	m_Pin = 0;
	m_IsInv = false;
	m_HasInit = false;
}

LED::LED(uint8_t port, uint8_t pin, bool inv_logic) {
	//TODO:Check the port and pin are valid parameter
	m_Port = port;
	m_Pin = pin;
	m_IsInv = inv_logic;
	
	::XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)(PORT0_BASE + port*0x100),
											pin, 
											InitMode);

	m_HasInit = true;

	Off();
}

LED::~LED(void) {
	UnInit(m_Port, m_Pin);
}

void LED::Init(uint8_t port, uint8_t pin, bool inv_logic) {
	//TODO:Check the port and pin are valid parameter
	if(m_HasInit) {
		UnInit(port, pin);
	}
	
	m_Port = port;
	m_Pin = pin;
	m_IsInv = inv_logic;
	
	::XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)(PORT0_BASE + port*0x100),
											pin, 
											InitMode);

	m_HasInit = true;
	
	Off();
}

void LED::UnInit(uint8_t port, uint8_t pin) {
	//UnInitialization
	if(m_HasInit) {
		::XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100),
												m_Pin, 
												UnInitMode);	

		m_HasInit = false;				
	}			
}

void LED::On(void) {
	if(m_HasInit) {
		if(m_IsInv) {
			::XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100), m_Pin);
		} else {
			::XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100), m_Pin);
		}
	}
}

void LED::Off(void) {
	if(m_HasInit) {
		if(m_IsInv) {
			::XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100), m_Pin);
		}	else {
			::XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100), m_Pin);
		}
	}			
}

void LED::Toogle(void) {
	if(m_HasInit) {
		XMC_GPIO_ToggleOutput((XMC_GPIO_PORT_t *)(PORT0_BASE + m_Port*0x100), m_Pin);
	}		
}
