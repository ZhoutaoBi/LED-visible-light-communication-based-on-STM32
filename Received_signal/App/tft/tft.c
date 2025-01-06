//lcd.c
#include "tft.h"

//extern
	GPIO_InitTypeDef GPIO_Initure;

void lcd_init() {
	RCC_APB2PeriphClockCmd(LCD_RCC_ENABLE, ENABLE);
	
	//RESET
	GPIO_Initure.GPIO_Mode = LCD_RESET_MODE;
	GPIO_Initure.GPIO_Pin = LCD_RESET_PIN;
	GPIO_Initure.GPIO_Speed = LCD_RESET_SPEED;
	GPIO_Init(LCD_RESET_GPIO, &GPIO_Initure);
	
	//CMD DATA
	GPIO_Initure.GPIO_Mode = LCD_CMD_DATA_MODE;
	GPIO_Initure.GPIO_Pin = LCD_CMD_DATA_PIN;
	GPIO_Initure.GPIO_Speed = LCD_CMD_DATA_SPEED;
	GPIO_Init(LCD_CMD_DATA_GPIO, &GPIO_Initure);
	
	//BACK LIGHT
	GPIO_Initure.GPIO_Mode = LCD_BACK_LIGHT_MODE;
	GPIO_Initure.GPIO_Pin = LCD_BACK_LIGHT_PIN;
	GPIO_Initure.GPIO_Speed = LCD_BACK_LIGHT_SPEED;
	GPIO_Init(LCD_BACK_LIGHT_GPIO, &GPIO_Initure);
	
	LCD_RESRT = LCD_CMD_DATA = LCD_BACK_LIGHT = 1;
	
	spi_init();
	lcd_config();
}

void lcd_config() {
	//===============reset============================
	lcd_reset();

	//===============exit sleep=======================
	lcd_write(TFT_CMD ,LCD_SLPOUT);
	Delay_ms(120);

	//===============frame set========================
	//Frame rate = fosc / ((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
//	lcd_write(TFT_CMD, LCD_FRMCTR1);
//	lcd_write(TFT_DATA, 0x02);
//	lcd_write(TFT_DATA, 0x35);
//	lcd_write(TFT_DATA, 0x36);
//	
//	lcd_write(TFT_CMD, LCD_FRMCTR2);
//	lcd_write(TFT_DATA, 0x02);
//	lcd_write(TFT_DATA, 0x35);
//	lcd_write(TFT_DATA, 0x36);
//	
//	lcd_write(TFT_CMD, LCD_FRMCTR3);
//	lcd_write(TFT_DATA, 0x02);
//	lcd_write(TFT_DATA, 0x35);
//	lcd_write(TFT_DATA, 0x36);
//	lcd_write(TFT_DATA, 0x02);
//	lcd_write(TFT_DATA, 0x35);
//	lcd_write(TFT_DATA, 0x36);
	
	lcd_write(TFT_CMD, LCD_FRMCTR1);
	lcd_write(TFT_DATA, 0x01);
	lcd_write(TFT_DATA, 0x2C);
	lcd_write(TFT_DATA, 0x2D);
	
	lcd_write(TFT_CMD, LCD_FRMCTR2);
	lcd_write(TFT_DATA, 0x01);
	lcd_write(TFT_DATA, 0x2C);
	lcd_write(TFT_DATA, 0x2D);
	
	lcd_write(TFT_CMD, LCD_FRMCTR3);
	lcd_write(TFT_DATA, 0x01);
	lcd_write(TFT_DATA, 0x2C);
	lcd_write(TFT_DATA, 0x2D);
	lcd_write(TFT_DATA, 0x01);
	lcd_write(TFT_DATA, 0x2C);
	lcd_write(TFT_DATA, 0x2D);
	
	//===============inversion of control=============
	lcd_write(TFT_CMD, LCD_INVCRT);
	lcd_write(TFT_DATA, 0x03);

	//===============power set========================
	lcd_write(TFT_CMD, LCD_PWCTR1);
	lcd_write(TFT_DATA, 0xA2);
	lcd_write(TFT_DATA, 0x02);
	lcd_write(TFT_DATA, 0x84);
		
	lcd_write(TFT_CMD, LCD_PWCTR2);
	lcd_write(TFT_DATA, 0xC5);

	lcd_write(TFT_CMD, LCD_PWCTR3);
	lcd_write(TFT_DATA, 0x0D);
	lcd_write(TFT_DATA, 0x00);
	
	lcd_write(TFT_CMD, LCD_PWCTR4);
	lcd_write(TFT_DATA, 0x8D);
	lcd_write(TFT_DATA, 0x2A);
	
	lcd_write(TFT_CMD, LCD_PWCTR5);
	lcd_write(TFT_DATA, 0x8D);
	lcd_write(TFT_DATA, 0xEE);

	//===============vcom set=========================
	lcd_write(TFT_CMD, LCD_VMCTR1);
	lcd_write(TFT_DATA, 0x03);

	//===============color format set=================
	set_color_format(0x05);
	
	//===============scanning direction set===========
	set_scan_direction(0x08);
	
	//===============gamma sequence set===============
	lcd_write(TFT_CMD, LCD_GMCTRP1);
	lcd_write(TFT_DATA, 0x12);
	lcd_write(TFT_DATA, 0x1C);
	lcd_write(TFT_DATA, 0x10);
	lcd_write(TFT_DATA, 0x18);
	lcd_write(TFT_DATA, 0x33);
	lcd_write(TFT_DATA, 0x2C);
	lcd_write(TFT_DATA, 0x25);
	lcd_write(TFT_DATA, 0x28);
	lcd_write(TFT_DATA, 0x28);
	lcd_write(TFT_DATA, 0x27);
	lcd_write(TFT_DATA, 0x2F);
	lcd_write(TFT_DATA, 0x3C);
	lcd_write(TFT_DATA, 0x00);
	lcd_write(TFT_DATA, 0x03);
	lcd_write(TFT_DATA, 0x03);
	lcd_write(TFT_DATA, 0x10);

	lcd_write(TFT_CMD, LCD_GMCTRN1);
	lcd_write(TFT_DATA, 0x12);
	lcd_write(TFT_DATA, 0x1C);
	lcd_write(TFT_DATA, 0x10);
	lcd_write(TFT_DATA, 0x18);
	lcd_write(TFT_DATA, 0x2D);
	lcd_write(TFT_DATA, 0x28);
	lcd_write(TFT_DATA, 0x23);
	lcd_write(TFT_DATA, 0x28);
	lcd_write(TFT_DATA, 0x28);
	lcd_write(TFT_DATA, 0x26);
	lcd_write(TFT_DATA, 0x2F);
	lcd_write(TFT_DATA, 0x3B);
	lcd_write(TFT_DATA, 0x00);
	lcd_write(TFT_DATA, 0x03);
	lcd_write(TFT_DATA, 0x03);
	lcd_write(TFT_DATA, 0x10);

	//===============partial area set=================
	lcd_write(TFT_CMD, LCD_PTLAR);             
	lcd_write(TFT_DATA, 0x00);             
	lcd_write(TFT_DATA, 0x00);             
	lcd_write(TFT_DATA, 0x00);             
	lcd_write(TFT_DATA, 0x80);
	
	//===============partial mode on==================
	lcd_write(TFT_CMD, LCD_PTLON);

	//===============display on=======================
	lcd_write(TFT_CMD, LCD_DISPON);
}

void lcd_reset() {
	LCD_RESRT = 1;
	Delay_ms(60);
	LCD_RESRT = 0;
	Delay_ms(120);
	LCD_RESRT = 1;
	Delay_ms(60);
}

void lcd_write(u8 c_d, u8 data) {
	LCD_CMD_DATA = c_d;
	spi_start();
	spi_write(data);
	spi_stop();
}

void set_background(u16 color) {
	u8 i,j;
	set_frame_size(0,0x7F,0x00,0x7F);

	for(i = 0; i < 128; i ++) {
	    for(j = 0; j < 128; j ++) {
			lcd_write(TFT_DATA, color >> 8);
			lcd_write(TFT_DATA, color);
		}
	}
}

void set_scan_direction(u8 data) {
	lcd_write(TFT_CMD, LCD_MADCTL);
	lcd_write(TFT_DATA, data);
}

void set_color_format(u8 data) {
	lcd_write(TFT_CMD, LCD_COLMOD);
	lcd_write(TFT_DATA, data);
}

void set_frame_size(u16 x_start, u16 x_end, u16 y_start, u16 y_end) {
	lcd_write(TFT_CMD, LCD_CASET);
	lcd_write(TFT_DATA, x_start >> 8);
	lcd_write(TFT_DATA, x_start);
	lcd_write(TFT_DATA, x_end >> 8);
	lcd_write(TFT_DATA, x_end);
	
	lcd_write(TFT_CMD, LCD_RASET);
	lcd_write(TFT_DATA, y_start >> 8);
	lcd_write(TFT_DATA, y_start);
	lcd_write(TFT_DATA, y_end >> 8);
	lcd_write(TFT_DATA, y_end);
	
	lcd_write(TFT_CMD, LCD_RAMWR);
}

void set_point(u16 x, u16 y, u16 color) {
	set_frame_size(x, x + 1, y, y + 1);

	lcd_write(TFT_DATA, color >> 8);
	lcd_write(TFT_DATA, color);
}

void set_rectangle(u16 x_start, u16 x_end, u16 y_start, u16 y_end, u16 color) {
	u8 i, j, w, h;
	
	w = x_end - x_start;
	h = y_end - y_start;
	
	set_frame_size(x_start, x_end, y_start, y_end);
	
	for(i = 0; i < w; i ++) {
	    for(j = 0; j < h; j ++) {
			lcd_write(TFT_DATA, color >> 8);
			lcd_write(TFT_DATA, color);
		}
	}
}

void DispGrayHor16(void) {
	u8 i,j,k;

   	set_frame_size(0, 127, 0, 127);

	for(i = 0;i < 128; i ++) {	
		for(j=0;j<16;j++) {
	        for(k=0;k< 128 / 16; k ++) {		
				lcd_write(TFT_DATA, ((j*2)<<3)|((j*4)>>3));		 
				lcd_write(TFT_DATA, ((j*4)<<5)|(j*2));
			} 
		}
	}
}

void DispFrame(void) {
	u8 i,j;
	
	set_frame_size(0, 127, 0, 127);

	lcd_write(TFT_DATA, 0xF8);
	lcd_write(TFT_DATA, 0x00);
	
	for(i = 0; i < 126; i ++){
		lcd_write(TFT_DATA, 0xFF);
		lcd_write(TFT_DATA, 0xFF);
	}
	
	lcd_write(TFT_DATA, 0x00);
	lcd_write(TFT_DATA, 0x1F);

	for(j = 0; j < 126; j ++)
	{
		lcd_write(TFT_DATA, 0xF8);
		lcd_write(TFT_DATA, 0x00);
		for(i = 0; i < 126; i ++) {
			lcd_write(TFT_DATA, 0x00);
			lcd_write(TFT_DATA, 0x00);
		}
		
		lcd_write(TFT_DATA, 0x00);
		lcd_write(TFT_DATA, 0x1F);
	}
	
	lcd_write(TFT_DATA, 0xf8);
	lcd_write(TFT_DATA, 0x00);
	
	for(i=0;i<126;i++){
		lcd_write(TFT_DATA, 0xFF);
		lcd_write(TFT_DATA, 0xFF);
	}
	
	lcd_write(TFT_DATA, 0x00);
	lcd_write(TFT_DATA, 0x1F);
	
}

void DispBand(void) {
	u8 i,j,k;
	u16 color[8]={0x001f,0x07e0,0xf800,0x07ff,0xf81f,0xffe0,0x0000,0xffff};
//	u16 color[8]={0xf800,0xf800,0x07e0,0x07e0,0x001f,0x001f,0xffff,0xffff};//0x94B2
	//unsigned int gray16[]={0x0000,0x1082,0x2104,0x3186,0x42,0x08,0x528a,0x630c,0x738e,0x7bcf,0x9492,0xa514,0xb596,0xc618,0xd69a,0xe71c,0xffff};

	lcd_write(TFT_CMD, 0x36); //Set Scanning Direction
	lcd_write(TFT_DATA, 0x08); //0xc8

   	set_frame_size(0, 127, 0, 127);																								  

	for(i=0;i < 8;i++)
	{
		for(j=0;j < 128 / 8;j++)
		{
	        for(k=0;k< 128;k++)
			{
				lcd_write(TFT_DATA, color[i]>>8); 
				lcd_write(TFT_DATA, color[i]);   
			} 
		}
	}
}

void DispPic(u8 x,u8 y,u8 w, u8 h,const unsigned char *p) {
	unsigned int i,j;
	unsigned char pic_h,pic_l;
	
//	lcd_write(TFT_CMD, 0x36); //Set Scanning Direction
//	lcd_write(TFT_DATA, 0xC8); //0xc8
	
	set_frame_size(x, x + w - 1, y, y + h - 1);    

	for(i = 0; i < h; i ++) {
	    for(j = 0; j < w; j ++) {    
			pic_l=(*p) ;
			pic_h=(*(p+1)) ;
			lcd_write(TFT_DATA, pic_h);				  
			lcd_write(TFT_DATA, pic_l);
			p=p+2;
		}
	}
}
