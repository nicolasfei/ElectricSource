#ifndef __SPI_H
#define __SPI_H

#include "gd32f4xx.h"

#define XL2543_EOC_STATUS_GET		gpio_input_bit_get(GPIOF,GPIO_PIN_10) 	//ADCת������ź�

typedef struct
{
		unsigned int Data0;
		unsigned int Data1;
		unsigned int Data2;
		unsigned int Data3;
		unsigned int Data4;
		unsigned int Data5;
		unsigned int Data6;
		unsigned int Data7;
		unsigned int Data8;
		unsigned int Data9;
		unsigned int Data10;
}T_SPI_DATA;

/*******************************************************************************
* function name  : SPI1_Init
* brief          : SPI1 initialize
* param[in]      : None
* param[out]     : None
* retval         : None
* attention      : None
*******************************************************************************/
void XL2543_Init(void);
/******************************************************************************* 
���ƣ�unsigned int Read_SPI(unsigned char chan) 
���ܣ���ȡѡ��ͨ���ϵ�ADֵ 
�������������Ϊ��Ҫ��ȡ��ͨ��������ΪADֵ 
ʱ�䣺
�汾��1.0 
ע�⣺
*******************************************************************************/  
unsigned int Read_SPI(unsigned char chan);

void Delay_AD(volatile unsigned int time);

/**
	*��ȡ����adcͨ��������
	*
	*/
void Read_SPI_All(void);

/**
	*��ȡSPI����������
	*
	*/
T_SPI_DATA* getSpiData(void);

/**
	*��ȡADC�ɼ���˲ʱֵ
	*
	*/
T_SPI_DATA GetSpiTransientData(void);

/**
	*��ȡADC�ɼ�����ֵ̬
	*
	*/
T_SPI_DATA GetSpiSteadyData(void);

/**
	*���ADC�ɼ�����ֵ̬
	*
	*/
void ClearSpiSteadyData(void);

/**
	*�ɼ���spi�����˲�
	*
	*/
void FilterSpiData(void);
#endif

