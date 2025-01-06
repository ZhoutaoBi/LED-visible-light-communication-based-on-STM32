#include "beep.h"

void BEEP_Init(void)
 {
 GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
 RCC_APB2PeriphClockCmd(BEEP_PORT_RCC|BEEP_PORT_RCC,ENABLE);
	 
 GPIO_InitStructure.GPIO_Pin=BEEP_PIN; //选择你要设置的 IO 口
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //设置推挽输出模式
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //设置传输速率
 GPIO_Init(BEEP_PORT,&GPIO_InitStructure); /* 初始化 GPIO */
 GPIO_ResetBits(BEEP_PORT,BEEP_PIN); //将 LED 端口拉高，熄灭所有 LED
	 

 }
 
 