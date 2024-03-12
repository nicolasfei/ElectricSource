#ifndef __SPI_H
#define __SPI_H

#include "gd32f4xx.h"

#define XL2543_EOC_STATUS_GET		gpio_input_bit_get(GPIOF,GPIO_PIN_10) 	//ADC转换完成信号

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
名称：unsigned int Read_SPI(unsigned char chan) 
功能：读取选定通道上的AD值 
参数：输入参数为需要读取的通道，返回为AD值 
时间：
版本：1.0 
注意：
*******************************************************************************/  
unsigned int Read_SPI(unsigned char chan);

void Delay_AD(volatile unsigned int time);

/**
	*读取所有adc通道的数据
	*
	*/
void Read_SPI_All(void);

/**
	*获取SPI读到的数据
	*
	*/
T_SPI_DATA* getSpiData(void);

/**
	*获取ADC采集的瞬时值
	*
	*/
T_SPI_DATA GetSpiTransientData(void);

/**
	*获取ADC采集的稳态值
	*
	*/
T_SPI_DATA GetSpiSteadyData(void);

/**
	*清空ADC采集的稳态值
	*
	*/
void ClearSpiSteadyData(void);

/**
	*采集的spi数据滤波
	*
	*/
void FilterSpiData(void);
#endif

