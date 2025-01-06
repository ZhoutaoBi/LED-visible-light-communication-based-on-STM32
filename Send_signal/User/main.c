#include "stm32f10x.h"
#include "led.h"
#include "Delay.h"
#include "key.h"

 int i = 0;
 char j = 0;
int main()
{
	LED_Init();
	Key_GPIO_Config();
	GPIO_ResetBits(LED1_PORT,LED1_PIN);//点亮PA1
	while(1)
	{
	
		j = Key_Scan();
		if(j == 0)
		{
			GPIO_ResetBits(LED1_PORT,LED1_PIN);
		}
		else
		{
      
      for(i=0; i < j; i++)//将要发出的数据转化为低脉冲波
       {
         GPIO_SetBits(LED1_PORT,LED1_PIN);
         Delay_ms(10); 
         GPIO_ResetBits(LED1_PORT,LED1_PIN);
         Delay_ms(15);
         }    
				GPIO_SetBits(LED1_PORT,LED1_PIN);
				 j = 0;
          
		}
		
	}
}
