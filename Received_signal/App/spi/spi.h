//spi.h
#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define SPI_RCC_ENABLE		RCC_APB2Periph_GPIOB 

#define SPI_DATA_IN_MODE	GPIO_Mode_IN_FLOATING
#define SPI_DATA_IN_PIN		GPIO_Pin_1
#define SPI_DATA_IN_SPEED	GPIO_Speed_50MHz
#define SPI_DATA_IN_GPIO	GPIOC

#define SPI_DATA_OUT_MODE	GPIO_Mode_Out_PP
#define SPI_DATA_OUT_PIN	GPIO_Pin_1
#define SPI_DATA_OUT_SPEED	GPIO_Speed_50MHz
#define SPI_DATA_OUT_GPIO	GPIOB

#define SPI_SCLK_MODE		GPIO_Mode_Out_PP
#define SPI_SCLK_PIN		GPIO_Pin_0
#define SPI_SCLK_SPEED		GPIO_Speed_50MHz
#define SPI_SCLK_GPIO		GPIOB

#define SPI_CS_MODE			GPIO_Mode_Out_PP
#define SPI_CS_PIN			GPIO_Pin_4
#define SPI_CS_SPEED		GPIO_Speed_50MHz
#define SPI_CS_GPIO			GPIOB

#define SPI_DATA_IN 	PCin(1)
#define SPI_DATA_OUT 	PBout(1)
#define SPI_SCLK		PBout(0)
#define SPI_CS			PBout(4)

#define SPI_SCLK_HIGH_KEEP	0	//时钟信号低电平维持时间
#define SPI_SCLK_LOW_KEEP	0	//时钟信号高电平维持时间

#define SPI_DATA_VALID		1	//0-低电平有效， 1-高电平有效
#define SPI_EDGE_TRIGGERED	1	//0-下降沿有效， 1-上升沿有效

#define SPI_WRITE_ENABLE	1	//0-禁止SPI写入数据，1-使能SPI读取数据
#define SPI_READ_ENABLE		0	//0-禁止SPI读取数据，1-使能SPI写入数据

void spi_init(void);
void spi_start(void);
void spi_write_place(u8 data);
void spi_write(u8 data);
u8 spi_read_place(void);
u8 spi_read(void);
void spi_stop(void);

#endif	//__SPI_H
