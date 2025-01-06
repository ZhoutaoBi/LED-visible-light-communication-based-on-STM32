//spi.c
#include "spi.h"

extern GPIO_InitTypeDef GPIO_Initure;

void spi_init() {
	RCC_APB2PeriphClockCmd(SPI_RCC_ENABLE, ENABLE);
	
#if SPI_READ_ENABLE
	//SPI	DATA_IN		PA1
	GPIO_Initure.GPIO_Mode = SPI_DATA_IN_MODE;
	GPIO_Initure.GPIO_Pin = SPI_DATA_IN_PIN;
	GPIO_Initure.GPIO_Speed = SPI_DATA_IN_SPEED;
	GPIO_Init(SPI_DATA_IN_GPIO, &GPIO_Initure);
#endif
	
#if SPI_WRITE_ENABLE
	//SPI	DATA_OUT
	GPIO_Initure.GPIO_Mode = SPI_DATA_OUT_MODE;
	GPIO_Initure.GPIO_Pin = SPI_DATA_OUT_PIN;
	GPIO_Initure.GPIO_Speed = SPI_DATA_OUT_SPEED;
	GPIO_Init(SPI_DATA_OUT_GPIO, &GPIO_Initure);
#endif
	
	//SPI	SCLK
	GPIO_Initure.GPIO_Mode = SPI_SCLK_MODE;
	GPIO_Initure.GPIO_Pin = SPI_SCLK_PIN;
	GPIO_Initure.GPIO_Speed = SPI_SCLK_SPEED;
	GPIO_Init(SPI_SCLK_GPIO, &GPIO_Initure);
	
	//SPI	CS
	GPIO_Initure.GPIO_Mode = SPI_CS_MODE;
	GPIO_Initure.GPIO_Pin = SPI_CS_PIN;
	GPIO_Initure.GPIO_Speed = SPI_CS_SPEED;
	GPIO_Init(SPI_CS_GPIO, &GPIO_Initure);
	
	SPI_CS = 1;	//拉高SPI片选引脚，使通信无效
	SPI_SCLK = SPI_DATA_OUT = 0;
}

void spi_start(){
	SPI_CS = 0;
}

void spi_write_place(u8 data) {
	SPI_DATA_OUT = data == 1 ? SPI_DATA_VALID : !SPI_DATA_VALID;
	SPI_SCLK = !SPI_EDGE_TRIGGERED;
#if (SPI_SCLK_LOW_KEEP != 0 && SPI_SCLK_HIGH_KEEP != 0)
	SPI_EDGE_TRIGGERED == 1 ? delay_us(SPI_SCLK_LOW_KEEP) : delay_us(SPI_SCLK_HIGH_KEEP);
#endif
	SPI_SCLK = SPI_EDGE_TRIGGERED;
#if (SPI_SCLK_LOW_KEEP != 0 && SPI_SCLK_HIGH_KEEP != 0)
	SPI_EDGE_TRIGGERED == 1 ? delay_us(SPI_SCLK_LOW_KEEP) : delay_us(SPI_SCLK_HIGH_KEEP);
#endif
}

void spi_write(u8 data){
	u8 i = 0, place;

    for(; i < 8; i ++) {
    	place = data & 1 << (7 - i);
    	spi_write_place(place != 0 ? 1 : 0);
	} 
}

u8 spi_read_place() {
	u8 data;

	SPI_SCLK = !SPI_EDGE_TRIGGERED;
	SPI_EDGE_TRIGGERED == 1 ? Delay_us(SPI_SCLK_LOW_KEEP) : Delay_us(SPI_SCLK_HIGH_KEEP);
	SPI_SCLK = SPI_EDGE_TRIGGERED;
	data = SPI_DATA_IN;
	SPI_EDGE_TRIGGERED == 1 ? Delay_us(SPI_SCLK_LOW_KEEP) : Delay_us(SPI_SCLK_HIGH_KEEP);

	return data;
}

u8 spi_read(){
	u8 i = 0, data, place;

	for(; i < 8; i ++) {
		place = spi_read_place();
		data |= place << (7 - i);
	}
	
	return data;
}

void spi_stop() {
	SPI_CS = 1;
}
