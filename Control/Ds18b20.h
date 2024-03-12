
#ifndef __DS18B20_H
#define __DS18B20_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "gd32f4xx.h"                   // Device header
#include "stdint.h"
#include "SysTick.h"
 
/*��װ�ӿ�*/
 
//��ʼ��DS18B20Ϊ����ģʽ
//�¶ȼ�1
#define DS18B20_T1_IN() 		{gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);}
#define DS18B20_T1_OUT() 		{gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);}
//�¶ȼ�2
#define DS18B20_T2_IN() 		{gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);}
#define DS18B20_T2_OUT() 		{gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);}

//IO��������
//�¶ȼ�1
#define DS18B20_T1_GET_BIT	gpio_input_bit_get(GPIOC,GPIO_PIN_5) 	//�����ߵ�ƽ
#define DS18B20_T1_DOWN 		gpio_bit_reset(GPIOC,GPIO_PIN_5) 			//�������ߵ�ƽ
#define DS18B20_T1_UP 			gpio_bit_set(GPIOC,GPIO_PIN_5) 				//�������ߵ�ƽ
//�¶ȼ�2
#define DS18B20_T2_GET_BIT	gpio_input_bit_get(GPIOC,GPIO_PIN_4) 	//�����ߵ�ƽ
#define DS18B20_T2_DOWN 		gpio_bit_reset(GPIOC,GPIO_PIN_4) 			//�������ߵ�ƽ
#define DS18B20_T2_UP 			gpio_bit_set(GPIOC,GPIO_PIN_4) 				//�������ߵ�ƽ

#define DS18B20_TEMP	0			//�¶�1
#define DS18B20_Fan		1			//�¶�2--�������
 
//��������
uint8_t DS18B20_CleckAck(int channel);
uint8_t DS18B20_CheckDevice(int channel);
void DS18B20_Init(void);
uint16_t DS18B20_ReadTemp(int channel);
uint8_t DS18B20_ReadByte(int channel);
void DS18B20_WriteByte(int channel, uint8_t cmd);
uint8_t DS18B20_Temp_Finish(int channel);

#endif
