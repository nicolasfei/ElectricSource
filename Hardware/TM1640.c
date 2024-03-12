/*
 *  TM1640.c
 *  Created on: 2021年08月23日
 *  Author: LiYi
 */

#include "gd32f4xx.h"
#include "TM1640.h"

void MCU_DATA1_H(void)      
{
		gpio_bit_set(GPIOA,GPIO_PIN_1);
}
void MCU_DATA1_L(void)      
{
		gpio_bit_reset(GPIOA,GPIO_PIN_1);
}

void MCU_CLK1_H(void)       
{
		gpio_bit_set(GPIOA,GPIO_PIN_2);
}
void MCU_CLK1_L(void)       
{
		gpio_bit_reset(GPIOA,GPIO_PIN_2);
}

void MCU_DATA2_H(void)
{
		gpio_bit_set(GPIOA,GPIO_PIN_3);
}

void MCU_DATA2_L(void)      
{
		gpio_bit_reset(GPIOA,GPIO_PIN_3);
}

void MCU_CLK2_H(void)       
{
		gpio_bit_set(GPIOA,GPIO_PIN_4);
}

void MCU_CLK2_L(void)       
{
		gpio_bit_reset(GPIOA,GPIO_PIN_4);
}

void MCU_DATA3_H(void)      
{
		gpio_bit_set(GPIOA,GPIO_PIN_5);
}

void MCU_DATA3_L(void)
{
		gpio_bit_reset(GPIOA,GPIO_PIN_5);
}

void MCU_CLK3_H(void)       
{		
		gpio_bit_set(GPIOA,GPIO_PIN_6);
}

void MCU_CLK3_L(void)       
{	
		gpio_bit_reset(GPIOA,GPIO_PIN_6);
}

/*------------------------------------------------------------
函数名称: void TM1640_IO_Init(void)
函数功能: 显示芯片TM1640引脚初始化
参    数: 无
返 回 值: 无
-------------------------------------------------------------*/
void TM1640_IO_Init(void)
{
		/*enable the GPIOA clock*/
		rcu_periph_clock_enable(RCU_GPIOA);
	
		//配置PA1引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_1);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);//配置为推挽输出，速度为50M
		
		//配置PA2引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_2);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);//配置为推挽输出，速度为50M
	
		//配置PA3引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//配置为推挽输出，速度为50M
	
		//配置PA4引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//配置为推挽输出，速度为50M
	
		//配置PA5引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//配置为推挽输出，速度为50M
		
		//配置PA6引脚的模式
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_6);//配置为下拉模式
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);//配置为推挽输出，速度为50M
		
		MCU_DATA1_L();
		MCU_CLK1_L();
		
		MCU_DATA2_L();
		MCU_CLK2_L();
		
		MCU_DATA3_L();
		MCU_CLK3_L();
}


/*------------------------------------------------------------
函数名称: static void TM1640_Send(int Data)
函数功能: 向显示芯片TM1640传递数据
参    数: Data：发送的数据
返 回 值: 无
-------------------------------------------------------------*/
static void TM1640_Send(MCU_DISP_PIN *ptMcuDispPin,int Data)
{
    char  i;
    for(i=0;i<8;i++)
    {
        ptMcuDispPin->MCU_CLK_L();
        __NOP();
        __NOP();
        if(Data&0x01)
        {
            ptMcuDispPin->MCU_DATA_H();
        }
        else 
        {
            ptMcuDispPin->MCU_DATA_L();
        }
        __NOP();
        __NOP();
        ptMcuDispPin->MCU_CLK_H();
        Data>>=1;
    }
    ptMcuDispPin->MCU_CLK_L();
}

/*------------------------------------------------------------
函数名称: static void TM1640_Start(void)
函数功能: 显示芯片TM1640开始发送数据
参    数: 无
返 回 值: 无
-------------------------------------------------------------*/
static void TM1640_Start(MCU_DISP_PIN *ptMcuDispPin)
{
    ptMcuDispPin->MCU_CLK_H();
    __NOP();
    __NOP();
     ptMcuDispPin->MCU_DATA_H();
    __NOP();
    __NOP();
     ptMcuDispPin->MCU_DATA_L();
    __NOP();
    __NOP();
     ptMcuDispPin->MCU_CLK_L(); 
}

/*------------------------------------------------------------
函数名称: static void TM1640_Stop(void)
函数功能: 显示芯片TM1640结束发送数据
参    数: 无
返 回 值: 无
-------------------------------------------------------------*/
static void TM1640_Stop(MCU_DISP_PIN *ptMcuDispPin)
{
     ptMcuDispPin->MCU_CLK_L();
		__NOP();
    __NOP();
    ptMcuDispPin->MCU_DATA_L();
		__NOP();
    __NOP();
    ptMcuDispPin->MCU_CLK_H();
		__NOP();
    __NOP();
    ptMcuDispPin->MCU_DATA_H();
}




/*------------------------------------------------------------
函数名称: void TM1640_Disp_Init(void)
函数功能: 显示芯片TM1640显示初始化
参    数: 无
返 回 值: 无
-------------------------------------------------------------*/
void TM1640_Disp_Init(void)
{
/*------------------------------------------------------------
| B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
|----|----|----|----|----|----|----|----|
| 0  | 1  | 0  | 0  | 0  | 0  | 0  | 0  |   地址自动加1
|----|----|----|----|----|----|----|----|
| 0  | 1  | 0  | 0  | 0  | 0  | 0  | 1  |   固定地址
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 0  | x  | x  | x  |   关闭显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 0  | 0  |   1/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 0  | 1  |   2/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 1  | 0  |   4/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 1  | 1  |   10/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 0  | 0  |   11/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 0  | 1  |   12/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 1  | 0  |   13/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 1  | 1  |   14/16亮度显示
|----|----|----|----|----|----|----|----|
| 1  | 1  | 0  | 0  | 0  | 0  | 0  | 0  |   起始地址DIG0，开始发送数据
|----|----|----|----|----|----|----|----|
                       |--------------|
                            起始地址 
------------------------------------------------------------------*/  
		MCU_DISP_PIN McuDispPin[3]={{MCU_DATA1_H,MCU_DATA1_L,MCU_CLK1_H,MCU_CLK1_L},{MCU_DATA2_H,MCU_DATA2_L,MCU_CLK2_H,MCU_CLK2_L},{MCU_DATA3_H,MCU_DATA3_L,MCU_CLK3_H,MCU_CLK3_L}};
    unsigned char i;
		for(i = 0; i < 3; i++)
		{
				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],DISP_DISABLE);              // 关显示
				TM1640_Stop(&McuDispPin[i]);

				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],AUTO_ADDR);                // 自动地址
				TM1640_Stop(&McuDispPin[i]);

				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],DISP_ENABLE|BRIGHTNESS10);  // 开显示 1i/16亮度
				TM1640_Stop(&McuDispPin[i]);
		}
}


/*------------------------------------------------------------
函数名称: void TM1640_Disp_Init(short *DataBuf)
函数功能: 显示芯片TM1640显示初始化
参    数: *DataBuf：更新的数组
返 回 值: 无
-------------------------------------------------------------*/
void TM1640_Disp_Update(unsigned char Num,unsigned short *DataBuf)
{
    MCU_DISP_PIN McuDispPin[3]={{MCU_DATA1_H,MCU_DATA1_L,MCU_CLK1_H,MCU_CLK1_L},{MCU_DATA2_H,MCU_DATA2_L,MCU_CLK2_H,MCU_CLK2_L},{MCU_DATA3_H,MCU_DATA3_L,MCU_CLK3_H,MCU_CLK3_L}};
		unsigned char i;
    TM1640_Start(&McuDispPin[Num]);
    TM1640_Send(&McuDispPin[Num],DISP_START_ADDR);            //起始地址
    for(i=0;i<16;i++)                   //送16位数
    {
        TM1640_Send(&McuDispPin[Num],*(DataBuf+i));
    }
    TM1640_Stop(&McuDispPin[Num]);
}



