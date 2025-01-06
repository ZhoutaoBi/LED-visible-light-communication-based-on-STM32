#include "stm32f10x.h"                  // Device header
//----------------------------------------------------------------
unsigned int TEMT6000_sensor_ADC_ConvertedValue;
float TEMT6000_sensor_ADC_ConvertedValueLocal;//�����⴫������ѹֵ����
char TEMT6000_sensor_data[7];
float TEMT6000_sensor_Lux;
char Lux[8];
//----------------------------------------------------------------
/*��ͨ����ADC�ɼ�*/
void  Adc_Config(void)
{ 	
    /*����������ʼ��Ҫ�õĽṹ�壬�����ÿ���ṹ���Ա��ֵ*/
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*
	  ʹ��GPIOA��ADC1ͨ��ʱ��
	  ע�⣺����RCC_APB2PeriphClockCmd����RCC_APB1PeriphClockCmd����ô�����ѡ��
      APB2������ʱ�ӣ����72MHz����Ҫ����AD���룬I/O������1���߼���ʱ��TIM
      APB1������ʱ�ӣ����36MHz����Ҫ����DA���������2��3��4��5����ͨ��ʱ��TIM,USB,IIC,CAN��SPI
  	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //72M/6=12, ADC�Ĳ���ʱ�����14MHz  
      
    /*���������ѹ���õ�PA0����*/         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //GPIO_Mode_AIN��ģ�����루��������ʲôģʽ���뿴����ĸ�¼ͼ1��
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
 
	
	ADC_DeInit(ADC1); //��λ����ADC1��صļĴ�����ΪĬ��ֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ģʽ��ADC1��ADC2��������ģʽ  ����������ʲôģʽ���뿴����ĸ�¼ͼ2��
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//��ģת��������ɨ�裨��ͨ����ģʽ=ENABLE�����Σ���ͨ����ģʽ=DISABLE
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//��ģת������������=ENABLE������=DISABLE
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ADCת��������������� ����������ʲôģʽ���뿴����ĸ�¼ͼ3��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���   �����Ҿ�����ADC_DataAlign_Left
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ   ��Χ��1-16
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADC1�ļĴ���
 
    /*ΪɶҪ����������һ����
     ϸ�ĵ�����Է��������ʼ����һ������ͨ������ʼ����һ��ADCת��������ADCת��������֪�����õ����ĸ����Űɣ�
     ��һ��Ŀ���ǣ�����ָ��ADC�Ĺ�����ͨ�������ţ����������ǵ�ת��˳��Ͳ���ʱ��
     ����ԭ�ͣ�void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime)
     ����1 ADCx��x������1����2��ѡ��ADC����ADC1��ADC2 
     ����2 ADC_Channel�������õ�ADCͨ��  ��ΧADC_Channel_0~ADC_Channel_17
     ����3 Rank�����������˳��ȡֵ��Χ1��16��
     ADC_SampleTime��ָ��ADCͨ���Ĳ���ʱ��ֵ  ��ȡֵ��Χ���뿴����ĸ�¼ͼ4��
    */	
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	  	
	  		    
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC  ע�⣺����ADC_Cmdֻ��������ADC���ú���֮�󱻵���
 
    /*����4���������ߣ��������*/
	ADC_ResetCalibration(ADC1);	//����ָ����ADC��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���һ���������
	ADC_StartCalibration(ADC1);	//��ʼָ��ADC��У׼״̬	
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ���һ����������		
 }	
 
 
float TEMT6000_ADC1(void)
{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
		TEMT6000_sensor_ADC_ConvertedValue=ADC_GetConversionValue(ADC1); 
	
		TEMT6000_sensor_ADC_ConvertedValueLocal =(float) TEMT6000_sensor_ADC_ConvertedValue/4096*5.0; //�����⴫������ȡ����
		TEMT6000_sensor_data[0]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/1000;
		TEMT6000_sensor_data[1]='.';
		TEMT6000_sensor_data[2]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/100%10;
		TEMT6000_sensor_data[3]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))/10%10;	
		TEMT6000_sensor_data[4]='0'+((int)(TEMT6000_sensor_ADC_ConvertedValueLocal*1000))%10;
		TEMT6000_sensor_data[5]='V';
		TEMT6000_sensor_data[6]='\0';
	
		TEMT6000_sensor_Lux=464.99*TEMT6000_sensor_ADC_ConvertedValueLocal-58.92;//��ѹ�����ǿ�ȵĺ���
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
 