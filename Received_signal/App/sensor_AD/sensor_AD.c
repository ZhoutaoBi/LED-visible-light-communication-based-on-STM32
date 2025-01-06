#include "stm32f10x.h"                  // Device header
//----------------------------------------------------------------
unsigned int TEMT6000_sensor_ADC_ConvertedValue;
float TEMT6000_sensor_ADC_ConvertedValueLocal;//环境光传感器电压值变量
char TEMT6000_sensor_data[7];
float TEMT6000_sensor_Lux;
char Lux[8];
//----------------------------------------------------------------
/*单通道的ADC采集*/
void  Adc_Config(void)
{ 	
    /*定义两个初始化要用的结构体，下面给每个结构体成员赋值*/
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*
	  使能GPIOA和ADC1通道时钟
	  注意：除了RCC_APB2PeriphClockCmd还有RCC_APB1PeriphClockCmd，那么该如何选择？
      APB2：高速时钟，最高72MHz，主要负责AD输入，I/O，串口1，高级定时器TIM
      APB1：低速时钟，最高36MHz，主要负责DA输出，串口2、3、4、5，普通定时器TIM,USB,IIC,CAN，SPI
  	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //72M/6=12, ADC的采样时钟最快14MHz  
      
    /*配置输入电压所用的PA0引脚*/         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //GPIO_Mode_AIN：模拟输入（还有其他什么模式？请看下面的附录图1）
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
 
	
	ADC_DeInit(ADC1); //复位，将ADC1相关的寄存器设为默认值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//工作模式：ADC1和ADC2独立工作模式  （还有其他什么模式？请看下面的附录图2）
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//数模转换工作：扫描（多通道）模式=ENABLE、单次（单通道）模式=DISABLE
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//数模转换工作：连续=ENABLE、单次=DISABLE
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ADC转换由软件触发启动 （还有其他什么模式？请看下面的附录图3）
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐   除了右就是左：ADC_DataAlign_Left
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目   范围是1-16
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADC1的寄存器
 
    /*为啥要设置下面这一步？
     细心的你可以发现上面初始化了一个引脚通道，初始化了一个ADC转换器，但ADC转换器并不知道你用的是哪个引脚吧？
     这一步目的是：设置指定ADC的规则组通道（引脚），设置它们的转化顺序和采样时间
     函数原型：void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime)
     参数1 ADCx：x可以是1或者2来选择ADC外设ADC1或ADC2 
     参数2 ADC_Channel：被设置的ADC通道  范围ADC_Channel_0~ADC_Channel_17
     参数3 Rank：规则组采样顺序。取值范围1到16。
     ADC_SampleTime：指定ADC通道的采样时间值  （取值范围？请看下面的附录图4）
    */	
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	  	
	  		    
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC  注意：函数ADC_Cmd只能在其他ADC设置函数之后被调用
 
    /*下面4步按流程走，走完就行*/
	ADC_ResetCalibration(ADC1);	//重置指定的ADC的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1)); //等待上一步操作完成
	ADC_StartCalibration(ADC1);	//开始指定ADC的校准状态	
	while(ADC_GetCalibrationStatus(ADC1));//等待上一步操作按成		
 }	
 
 
float TEMT6000_ADC1(void)
{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
		TEMT6000_sensor_ADC_ConvertedValue=ADC_GetConversionValue(ADC1); 
	
		TEMT6000_sensor_ADC_ConvertedValueLocal =(float) TEMT6000_sensor_ADC_ConvertedValue/4096*5.0; //环境光传感器读取数据
		TEMT6000_sensor_data[0]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/1000;
		TEMT6000_sensor_data[1]='.';
		TEMT6000_sensor_data[2]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/100%10;
		TEMT6000_sensor_data[3]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/10%10;	
		TEMT6000_sensor_data[4]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))%10;
		TEMT6000_sensor_data[5]='V';
		TEMT6000_sensor_data[6]='\0';
	
		TEMT6000_sensor_Lux=464.99*TEMT6000_sensor_ADC_ConvertedValueLocal-58.92;//电压与光照强度的函数
		Lux[0]='0'+((int)TEMT6000_sensor_Lux)/1000;
		Lux[1]='0'+((int)TEMT6000_sensor_Lux)/100%10;
		Lux[2]='0'+((int)TEMT6000_sensor_Lux)/10%10;	
		Lux[3]='0'+((int)TEMT6000_sensor_Lux)%10;
		Lux[4]='L';
		Lux[5]='u';
		Lux[6]='x';
		Lux[7]='\0';
		return TEMT6000_sensor_Lux;
}
 