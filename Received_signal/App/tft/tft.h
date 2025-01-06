//lcd.h
#ifndef __tft_H
#define __tft_H

#include "stm32f10x.h"
#include "sys.h"
#include "spi.h"

#define LCD_RCC_ENABLE		RCC_APB2Periph_GPIOB 

#define LCD_RESRT 		PBout(6) 
#define LCD_CMD_DATA	PBout(3)
#define LCD_BACK_LIGHT	PBout(5)

#define LCD_RESET_MODE			GPIO_Mode_Out_PP
#define LCD_RESET_PIN			GPIO_Pin_6
#define LCD_RESET_SPEED			GPIO_Speed_50MHz
#define LCD_RESET_GPIO			GPIOB

#define LCD_CMD_DATA_MODE		GPIO_Mode_Out_PP
#define LCD_CMD_DATA_PIN		GPIO_Pin_3
#define LCD_CMD_DATA_SPEED		GPIO_Speed_50MHz
#define LCD_CMD_DATA_GPIO		GPIOB

#define LCD_BACK_LIGHT_MODE		GPIO_Mode_Out_PP
#define LCD_BACK_LIGHT_PIN		GPIO_Pin_5
#define LCD_BACK_LIGHT_SPEED	GPIO_Speed_50MHz
#define LCD_BACK_LIGHT_GPIO		GPIOB

#define LCD_NOP			0x00	//������
#define LCD_SWRESET		0x01	//�����λ����˯�ߺ���ʾģʽ�£������������ȴ�120ms�󷽿�ִ����һ��ָ��
#define LCD_RDDID		0x04	//��ȡLCD��������ID��8λ���������汾ID�����λΪ1��7λ������������ID��8λ��
#define LCD_RDDST		0x09	//��ȡ��ʾ������״̬����
#define LCD_RDDPM		0x0A	//��ȡ��ʾ������ģʽ
#define LCD_RDDMADCTL	0x0B	//��ȡ��ʾ��MADCTL
#define LCD_RDDCOLMOD	0x0C	//��ȡ��ʾ�����ض���
#define LCD_RDDIM		0x0D	//��ȡ��ʾ��ͼƬģʽ
#define LCD_RDDSM		0x0E	//��ȡ��ʾ�����ź�ģʽ
#define LCD_RDDSDR		0x0F	//��ȡ��ʾ��������Ͻ��
#define LCD_SLPIN		0x10	//������С����ģʽ
#define LCD_SLPOUT 		0x11	//�ر�˯��ģʽ
#define LCD_PTLON		0x12	//��Partialģʽ
#define LCD_NORON		0x13	//�ָ�������ģʽ
#define LCD_INVOFF		0x20	//��ʾ��תģʽ�лָ�
#define LCD_INVON		0x21	//���뷴����ʾģʽ
#define LCD_GAMSET		0x26	//��ǰ��ʾѡ�������٤������
#define LCD_DISPOFF		0x28	//�ر���ʾ��֡�ڴ�����������
#define LCD_DISPON		0x29	//������ʾ��֡�ڴ�����������
#define LCD_CASET		0x2A	//�е�ַ���ã�ÿ��ֵ����֡�ڴ��е�һ��
#define LCD_RASET		0x2B	//�е�ַ���ã�ÿ��ֵ����֡�ڴ��е�һ��
#define LCD_RAMWR		0x2C	//д���ڴ�
#define LCD_RGBSET		0x2D	//��ɫģʽ����
#define LCD_RAMRD		0x2E	//��ȡ�ڴ�
#define LCD_PTLAR		0x30	//����ģʽ����ʾ��������
#define LCD_SCRLAR		0x33	//���崹ֱ�����������ʾ
#define LCD_TEOFF		0x34	//�ر�(Active Low) TE�ź��ߵ�˺��ЧӦ����ź�
#define LCD_TEON		0x35	//��TE�ź��ߵ�˺��Ч������ź�
#define LCD_MADCTL		0x36	//����֡�ڴ�Ķ�дɨ�跽��
#define LCD_VSCSAD		0x37	//���ô�ֱ������ʼ��ַ���������봹ֱ��������(33h)һ��ʹ��
#define LCD_IDMOFF		0x38	//�رտ���ģʽ
#define LCD_IDMON		0x39	//��������ģʽ
#define LCD_COLMOD		0x3A	//����ͨ��MCU�ӿڴ����RGBͼƬ���ݵĸ�ʽ
#define LCD_FRMCTR1		0xB1	//����ȫɫ����ģʽ��֡Ƶ
#define LCD_FRMCTR2 	0xB2	//���ÿ���ģʽ��֡Ƶ
#define LCD_FRMCTR3 	0xB3	//���ò���ģʽ/ȫɫ��֡Ƶ��
#define LCD_INVCRT 		0xB4	//��תģʽ����
#define LCD_PWCTR1 		0xC0	//����AVDD��MODE��VRHP��VRHN
#define LCD_PWCTR2 		0xC1	//����VGH��VGL�Ĺ��繦��
#define LCD_PWCTR3 		0xC2	//��������ģʽ/ȫɫģʽ�µ��˷ŵĵ���
#define LCD_PWCTR4 		0xC3	//���ÿ���ģʽ/��ɫģʽ�µ��˷ŵĵ���
#define LCD_PWCTR5 		0xC4	//���ò���ģʽ/ȫɫģʽ�µ��˷ŵĵ���
#define LCD_VMCTR1 		0xC5	//����VCOM��ѹ��ƽ�Լ�����˸����
#define LCD_VMOFCTR		0xC7	//VCOMƫ�ƿ��ƣ���ʹ������0xC7֮ǰ������0xD9��λVMF_EN��������(����Ϊ1)
#define LCD_WRID2		0xD1	//д��LCDģ��汾��7λ���ݣ����浽NVM
#define LCD_WRID3		0xD2	//д����Ŀ����ģ���8λ���ݣ����浽NVM
#define LCD_NVFCTR1		0xD9	//NVM״̬����
#define LCD_RDID1		0xDA	//���ֽڷ���8λLCDģ���������ID
#define LCD_RDID2		0xDB	//���ֽڷ���8λLCDģ��/��������汾ID
#define LCD_RDID3		0xDC	//���ֽڷ���8λLCDģ��/����ID
#define LCD_NVFCTR2		0xDE	//NVM��ȡ����
#define LCD_NVFCTR3		0xDF	//NVMдȡ����
#define LCD_GMCTRP1		0xE0	//Gamma ��+�� Polarity Correction Characteristics Setting
#define LCD_GMCTRN1		0xE1	//Gamma ��+�� Polarity Correction Characteristics Setting
#define LCD_GCV			0xFC	//�Զ������ű�ʱ�ӣ���ʡ����


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111


//    Color16_WHITE         =0xFFFF,
//    Color16_BLACK         =0x0000,
//    Color16_BLUE          =0x001F,
//    Color16_BRED          =0XF81F,
//    Color16_GRED          =0XFFE0,
//    Color16_GBLUE         =0X07FF,
//    Color16_RED           =0xF800,
//    Color16_MAGENTA       =0xF81F,
//    Color16_GREEN         =0x07E0,
//    Color16_CYAN          =0x7FFF,
//    Color16_YELLOW        =0xFFE0,
//    Color16_BROWN         =0XBC40, //��ɫ
//    Color16_BRRED         =0XFC07, //�غ�ɫ
//    Color16_GRAY          =0X8430, //��ɫ
//    //GUI��ɫ

//    Color16_DARKBLUE      =0X01CF,//����ɫ
//    Color16_LIGHTBLUE     =0X7D7C,//ǳ��ɫ  
//    Color16_GRAYBLUE      =0X5458, //����ɫ
//    //������ɫΪPANEL����ɫ 

//    Color16_LIGHTGREEN    =0X841F, //ǳ��ɫ
//    Color16_LIGHTGRAY     =0XEF5B,//ǳ��ɫ(PANNEL)
//    Color16_LGRAY         =0XC618, //ǳ��ɫ(PANNEL),���屳��ɫ

//    Color16_LGRAYBLUE     =0XA651, //ǳ����ɫ(�м����ɫ)
//    Color16_LBBLUE        =0X2B12, //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)



enum TFT_DATA_TYPE {
	TFT_CMD = 0,
	TFT_DATA
};

void lcd_init(void);
void lcd_config(void);
void lcd_reset(void);
void lcd_write(u8 c_d, u8 data);
void set_background(u16 color);
void set_scan_direction(u8 data);
void set_color_format(u8 data);
void set_frame_size(u16 x_start, u16 x_end, u16 y_start, u16 y_end);
void set_point(u16 x, u16 y, u16 color);
void set_rectangle(u16 x_start, u16 x_end, u16 y_start, u16 y_end, u16 color);
void DispGrayHor16(void);
void DispFrame(void);
void DispBand(void);
void DispPic(u8 x,u8 y,u8 w, u8 h,const unsigned char *p);

#endif	//__LCD_H
