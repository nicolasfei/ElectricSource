/*
 *  TM1640.c
 *  Created on: 2021��08��23��
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
��������: void TM1640_IO_Init(void)
��������: ��ʾоƬTM1640���ų�ʼ��
��    ��: ��
�� �� ֵ: ��
-------------------------------------------------------------*/
void TM1640_IO_Init(void)
{
		/*enable the GPIOA clock*/
		rcu_periph_clock_enable(RCU_GPIOA);
	
		//����PA1���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_1);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);//����Ϊ����������ٶ�Ϊ50M
		
		//����PA2���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_2);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);//����Ϊ����������ٶ�Ϊ50M
	
		//����PA3���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//����Ϊ����������ٶ�Ϊ50M
	
		//����PA4���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//����Ϊ����������ٶ�Ϊ50M
	
		//����PA5���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//����Ϊ����������ٶ�Ϊ50M
		
		//����PA6���ŵ�ģʽ
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_6);//����Ϊ����ģʽ
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);//����Ϊ����������ٶ�Ϊ50M
		
		MCU_DATA1_L();
		MCU_CLK1_L();
		
		MCU_DATA2_L();
		MCU_CLK2_L();
		
		MCU_DATA3_L();
		MCU_CLK3_L();
}


/*------------------------------------------------------------
��������: static void TM1640_Send(int Data)
��������: ����ʾоƬTM1640��������
��    ��: Data�����͵�����
�� �� ֵ: ��
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
��������: static void TM1640_Start(void)
��������: ��ʾоƬTM1640��ʼ��������
��    ��: ��
�� �� ֵ: ��
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
��������: static void TM1640_Stop(void)
��������: ��ʾоƬTM1640������������
��    ��: ��
�� �� ֵ: ��
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
��������: void TM1640_Disp_Init(void)
��������: ��ʾоƬTM1640��ʾ��ʼ��
��    ��: ��
�� �� ֵ: ��
-------------------------------------------------------------*/
void TM1640_Disp_Init(void)
{
/*------------------------------------------------------------
| B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
|----|----|----|----|----|----|----|----|
| 0  | 1  | 0  | 0  | 0  | 0  | 0  | 0  |   ��ַ�Զ���1
|----|----|----|----|----|----|----|----|
| 0  | 1  | 0  | 0  | 0  | 0  | 0  | 1  |   �̶���ַ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 0  | x  | x  | x  |   �ر���ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 0  | 0  |   1/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 0  | 1  |   2/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 1  | 0  |   4/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 0  | 1  | 1  |   10/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 0  | 0  |   11/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 0  | 1  |   12/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 1  | 0  |   13/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 0  | 0  | 0  | 1  | 1  | 1  | 1  |   14/16������ʾ
|----|----|----|----|----|----|----|----|
| 1  | 1  | 0  | 0  | 0  | 0  | 0  | 0  |   ��ʼ��ַDIG0����ʼ��������
|----|----|----|----|----|----|----|----|
                       |--------------|
                            ��ʼ��ַ 
------------------------------------------------------------------*/  
		MCU_DISP_PIN McuDispPin[3]={{MCU_DATA1_H,MCU_DATA1_L,MCU_CLK1_H,MCU_CLK1_L},{MCU_DATA2_H,MCU_DATA2_L,MCU_CLK2_H,MCU_CLK2_L},{MCU_DATA3_H,MCU_DATA3_L,MCU_CLK3_H,MCU_CLK3_L}};
    unsigned char i;
		for(i = 0; i < 3; i++)
		{
				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],DISP_DISABLE);              // ����ʾ
				TM1640_Stop(&McuDispPin[i]);

				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],AUTO_ADDR);                // �Զ���ַ
				TM1640_Stop(&McuDispPin[i]);

				TM1640_Start(&McuDispPin[i]);
				TM1640_Send(&McuDispPin[i],DISP_ENABLE|BRIGHTNESS10);  // ����ʾ 1i/16����
				TM1640_Stop(&McuDispPin[i]);
		}
}


/*------------------------------------------------------------
��������: void TM1640_Disp_Init(short *DataBuf)
��������: ��ʾоƬTM1640��ʾ��ʼ��
��    ��: *DataBuf�����µ�����
�� �� ֵ: ��
-------------------------------------------------------------*/
void TM1640_Disp_Update(unsigned char Num,unsigned short *DataBuf)
{
    MCU_DISP_PIN McuDispPin[3]={{MCU_DATA1_H,MCU_DATA1_L,MCU_CLK1_H,MCU_CLK1_L},{MCU_DATA2_H,MCU_DATA2_L,MCU_CLK2_H,MCU_CLK2_L},{MCU_DATA3_H,MCU_DATA3_L,MCU_CLK3_H,MCU_CLK3_L}};
		unsigned char i;
    TM1640_Start(&McuDispPin[Num]);
    TM1640_Send(&McuDispPin[Num],DISP_START_ADDR);            //��ʼ��ַ
    for(i=0;i<16;i++)                   //��16λ��
    {
        TM1640_Send(&McuDispPin[Num],*(DataBuf+i));
    }
    TM1640_Stop(&McuDispPin[Num]);
}



