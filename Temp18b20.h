
#ifndef __TEMP18B20_H
#define __TEMP18B20_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "gd32f4xx.h"                   // Device header
#include "stdint.h"
 
/*封装接口*/
 
//初始化DS18B20为输入模式
//温度计1
#define DS18B20_T1_IN() 		{gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);}
#define DS18B20_T1_OUT() 		{gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);}
//温度计2
#define DS18B20_T2_IN() 		{gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);}
#define DS18B20_T2_OUT() 		{gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);}

//IO操作函数
//温度计1
#define DS18B20_T1_GET_BIT	gpio_input_bit_get(GPIOC,GPIO_PIN_4) 	//读总线电平
#define DS18B20_T1_DOWN 		gpio_bit_reset(GPIOC,GPIO_PIN_4) 			//拉高总线电平
#define DS18B20_T1_UP 			gpio_bit_set(GPIOC,GPIO_PIN_4) 				//拉低总线电平
//温度计2
#define DS18B20_T2_GET_BIT	gpio_input_bit_get(GPIOC,GPIO_PIN_5) 	//读总线电平
#define DS18B20_T2_DOWN 		gpio_bit_reset(GPIOC,GPIO_PIN_5) 			//拉高总线电平
#define DS18B20_T2_UP 			gpio_bit_set(GPIOC,GPIO_PIN_5) 				//拉低总线电平

#define DS18B20_TEMP1	0
#define DS18B20_TEMP2	1
 
//函数声明
uint8_t DS18B20_CleckAck(void);
uint8_t DS18B20_CheckDevice(void);
void DS18B20_Init(void);
uint16_t DS18B20_ReadTemp(void);
uint8_t DS18B20_ReadByte(void);
void DS18B20_WriteByte(uint8_t cmd);


#endif

