#include "stm32f10x.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "sensor_AD.h"
#include "LCD_init.h"
#include "oled.h"
#include <math.h>

 char j = 0;
 float data = 0;
 float data_new = 0;
 int number = 0;
 int flag = 0;
 int flag_number = 0;
 int commond_number = 0;
 int time =  0;
 
int main()
{
	Delay_init();
	BEEP_Init();
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); //将 LED 端口拉高，熄灭所有 LED

	Adc_Config();
	OLED_Init();
 OLED_Display_On();
	OLED_ShowString(1,1,"Number:",16);
	OLED_ShowNum(4,4,0,2,16);
	while(1)
	{
		data = TEMT6000_ADC1();	
		if(data > 800 && flag == 1)
		{
			flag_number = 1;
			number++;
			flag = 0;
		}
	if(data < 800 && flag == 0)
		{		
			flag = 1;
		}
		while(TEMT6000_ADC1()<500 && time<30)
		{
			Delay_ms(1);
			time++;	
			if (time >20 && flag_number == 1)
			{
			commond_number = number;
			OLED_ShowNum(4,4,commond_number,2,16);
			if(commond_number == 16)
			{
				GPIO_SetBits(BEEP_PORT,BEEP_PIN); //
			}else
			{
				GPIO_ResetBits(BEEP_PORT,BEEP_PIN);
			}
			number = 0;
			time = 0;
			flag_number = 0;
			}
		}
		time = 0;

		


		
		
		
		
		
	}
}
