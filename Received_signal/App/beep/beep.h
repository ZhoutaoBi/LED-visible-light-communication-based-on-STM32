	#ifndef _beep_H
	#define _beep_H
	#include "stm32f10x.h" /* LED ʱ�Ӷ˿ڡ����Ŷ��� */
	#define BEEP_PORT GPIOA
	#define BEEP_PIN GPIO_Pin_6
	#define BEEP_PORT_RCC RCC_APB2Periph_GPIOA

	
	void BEEP_Init(void);
#endif
