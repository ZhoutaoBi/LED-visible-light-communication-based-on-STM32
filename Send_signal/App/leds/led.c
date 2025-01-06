#include "led.h"

void LED_Init(void)
 {
 GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
 RCC_APB2PeriphClockCmd(LED1_PORT_RCC|LED2_PORT_RCC,ENABLE);
	 
 GPIO_InitStructure.GPIO_Pin=LED1_PIN; //选择你要设置的 IO 口
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //设置推挽输出模式
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //设置传输速率
 GPIO_Init(LED1_PORT,&GPIO_InitStructure); /* 初始化 GPIO */
 GPIO_SetBits(LED1_PORT,LED1_PIN); //将 LED 端口拉高，熄灭所有 LED
	 
 GPIO_InitStructure.GPIO_Pin=LED2_PIN; //选择你要设置的 IO 口
 GPIO_Init(LED2_PORT,&GPIO_InitStructure); /* 初始化 GPIO */
 GPIO_SetBits(LED2_PORT,LED2_PIN); //将 LED 端口拉高，熄灭所有 LED
 }
 
 