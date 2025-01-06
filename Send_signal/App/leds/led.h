	#ifndef _led_H
	#define _led_H
	#include "stm32f10x.h" /* LED 时钟端口、引脚定义 */
	#define LED1_PORT GPIOA
	#define LED1_PIN GPIO_Pin_1
	#define LED1_PORT_RCC RCC_APB2Periph_GPIOA
	
	#define LED2_PORT GPIOE
	#define LED2_PIN GPIO_Pin_5
	#define LED2_PORT_RCC RCC_APB2Periph_GPIOE
	
	void LED_Init(void);
#endif
