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

const led_position_pair LED::LedPositions[LED::LED_COUNT] = {
	std::make_pair(XMC_GPIO_PORT0, 7),
	std::make_pair(XMC_GPIO_PORT0, 5),
	std::make_pair(XMC_GPIO_PORT0, 6),
	std::make_pair(XMC_GPIO_PORT1, 4),
	std::make_pair(XMC_GPIO_PORT1, 5),
};

//Default Constructor
LED::LED(void) {
	m_num = LED::LED_COUNT;
	m_IsInv = false;
	m_HasInit = false;
}

LED::LED(const uint8_t num) {
	//TODO:Check the port and pin are valid parameter
	assert( num < LED::LED_COUNT );
	
	m_num = num;
	
	::XMC_GPIO_SetMode(LedPositions[num].first,
											LedPositions[num].second, 
											InitMode);

	m_HasInit = true;

	Off();
}

LED::~LED(void) {
	UnInit();
}

void LED::Init(const bool inv_logic) {
	assert( m_num < LED::LED_COUNT );

	if(m_HasInit) {
		UnInit();
	}

	m_IsInv = inv_logic;
	
	::XMC_GPIO_SetMode(LedPositions[m_num].first,
											LedPositions[m_num].second, 
											InitMode);

	m_HasInit = true;
	
	Off();
}

void LED::UnInit(void) {
	assert( m_num < LED::LED_COUNT );

	if(m_HasInit) {
		::XMC_GPIO_SetMode(LedPositions[m_num].first,
											LedPositions[m_num].second, 
												UnInitMode);	

		m_HasInit = false;				
	}			
}

void LED::On(void) {
	assert( m_num < LED::LED_COUNT );

	if(m_HasInit) {
		if(m_IsInv) {
			::XMC_GPIO_SetOutputLow(LedPositions[m_num].first,
											LedPositions[m_num].second);
		} else {
			::XMC_GPIO_SetOutputHigh(LedPositions[m_num].first,
											LedPositions[m_num].second);
		}
	}
}

void LED::Off(void) {
	assert( m_num < LED::LED_COUNT );

	if(m_HasInit) {
		if(m_IsInv) {
			::XMC_GPIO_SetOutputHigh(LedPositions[m_num].first,
											LedPositions[m_num].second);
		}	else {
			::XMC_GPIO_SetOutputLow(LedPositions[m_num].first,
											LedPositions[m_num].second);
		}
	}			
}

void LED::Toogle(void) {
	assert( m_num < LED::LED_COUNT );

	if(m_HasInit) {
		XMC_GPIO_ToggleOutput(LedPositions[m_num].first,
											LedPositions[m_num].second);
	}		
}
