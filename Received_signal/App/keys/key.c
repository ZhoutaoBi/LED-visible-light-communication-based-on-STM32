/*********************************************************************
 * 文件名  ：key4x4.c
 * 描述    ：按键应用函数库        

 * 硬件连接：-------------------------
 *          | PB8  - H4          |
 *          | PB9  - H3			 |
 *          | PB10 - H2          |
 *          | PB11 - H1		     |
 *          | PB12 - L4          |
 *          | PB13 - L3		     |
 *          | PB14 - L2          |
 *          | PB15 - L1			 |
 *           -------------------------
 * 库版本  ：ST3.5.0
*********************************************************************/

#include "key.h" 
#include "delay.h" 

 /*
 * 函数名：Key_GPIO_Config
 * 描述  ：配置按键用到的I/O口 GPIO端口可以自行定义
 * 输入  ：无
 * 输出  ：无
 */
void Key_GPIO_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	
  	/*开启按键端口的时钟*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //GPIO端口引脚可以自行定义
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
   //配置引脚速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    //配置引脚模式  GPIO_Mode_IPU 上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
 /*
 * 函数名：u8 Key_Scan
 * 描述  ：按键扫描函数
 * 输入  ：无
 * 输出  ：无
 */
u8 Key_Scan(void)
{
	u16 temp;
	u8 ucBackValue=0;
	//====扫描第一列==========
	GPIO_Write(GPIOB,0xfe00); 
	temp=GPIO_ReadInputData(GPIOB); //读出整个口得到的值
	temp=temp&0xf000;    //屏蔽低4位
	if (temp!=0xf000)      //假如高4位不全是1
	{ 
		Delay_ms(20);      // 延时消抖再读
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //消抖后如果再次高4位确定不是全1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //读出此次按键的值
			switch(temp)
			{ 
				case 0xee00:
				ucBackValue = 1;break;
				case 0xde00:
				ucBackValue = 5;break;
				case 0xbe00:
				ucBackValue = 9;break;
				case 0x7e00:
				ucBackValue = 13;break;
				default:break;
			}
			while(temp!=0xf000)   //等待按键放开，初始必然被执行
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}

		}
	}

	//====第二列送0==========
	GPIO_Write(GPIOB,0xfd00); 
	temp=GPIO_ReadInputData(GPIOB); //读出整个口得到的值
	temp=temp&0xf000;    //屏蔽低4位
	if (temp!=0xf000)      //假如高4位不全是1
	{ 
		Delay_ms(20);      // 延时消抖再读
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //消抖后如果再次高4位确定不是全1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //读出此次按键的值
			switch(temp)
			{ 
				case 0xed00:
					ucBackValue = 2; break;
				case 0xdd00:
					ucBackValue = 6; break;
				case 0xbd00:
					ucBackValue = 10; break;
				case 0x7d00:
					ucBackValue = 14; break;
				default:break;
		}
			while(temp!=0xf000)   //等待按键放开
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}
		}
	}
	//====第3列送0==========
	GPIO_Write(GPIOB,0xfb00); 
	temp=GPIO_ReadInputData(GPIOB); //读出整个口得到的值
	temp=temp&0xf000;    //屏蔽低4位
	if (temp!=0xf000)      //假如高4位不全是1
	{ 
		Delay_ms(20);      // 延时消抖再读
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //消抖后如果再次高4位确定不是全1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //读出此次按键的值
			switch(temp)
			{ 
				case 0xeb00:
				ucBackValue = 3; break;
				case 0xdb00:
				ucBackValue = 7; break;
				case 0xbb00:
				ucBackValue = 11; break;
				case 0x7b00:
				ucBackValue = 15; break;
				default:break;
		}
		while(temp!=0xf000)   //等待按键放开
		{ 
			temp=GPIO_ReadInputData(GPIOB); 
			temp=temp&0xf000;
		}
		}
	}
	//====第4列送0==========
	GPIO_Write(GPIOB,0xf700); 
	temp=GPIO_ReadInputData(GPIOB); //读出整个口得到的值
	temp=temp&0xf000;    //屏蔽低4位
	if (temp!=0xf000)      //假如高4位不全是1
	{ 
		Delay_ms(20);       // 延时消抖再读
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //消抖后如果再次高4位确定不是全1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; 
			switch(temp)
			{ 
				case 0xe700:
				ucBackValue = 4; break;
				case 0xd700:
				ucBackValue = 8; break;
				case 0xb700:
				ucBackValue = 12; break;
				case 0x7700:
				ucBackValue = 16; break;
				default:break;
			}
			while(temp!=0xf000)   //等待按键放开
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}
		}
	}
	return ucBackValue;
}

