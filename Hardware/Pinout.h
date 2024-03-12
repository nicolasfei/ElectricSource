#ifndef __PINOUT_H
#define __PINOUT_H

#include "gd32f4xx.h"
#include "stdint.h"

#define AIN_CTL_S0_H                  gpio_bit_set(GPIOC,GPIO_PIN_0)   
#define AIN_CTL_S0_L                  gpio_bit_reset(GPIOC,GPIO_PIN_0)
#define AIN_CTL_S1_H                  gpio_bit_set(GPIOC,GPIO_PIN_1)   
#define AIN_CTL_S1_L                  gpio_bit_reset(GPIOC,GPIO_PIN_1)
#define AIN_CTL_S2_H                  gpio_bit_set(GPIOC,GPIO_PIN_2)   
#define AIN_CTL_S2_L                  gpio_bit_reset(GPIOC,GPIO_PIN_2)


//switch
#define DO_AC_CH1_ON				gpio_bit_set(GPIOG,GPIO_PIN_0)
#define DO_AC_CH1_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_0);s_tReg->AcPowerControl &= ~(1<<0);}

#define DO_DC1_CH1_ON				gpio_bit_set(GPIOG,GPIO_PIN_1)
#define DO_DC1_CH1_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_1);s_tReg->DcPowerControl &= ~(1<<0);}

#define DO_DC2_CH1_ON				gpio_bit_set(GPIOG,GPIO_PIN_2)
#define DO_DC2_CH1_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_2);s_tReg->DcPowerControl &= ~(1<<1);}

#define DO_AC_CH2_ON				gpio_bit_set(GPIOG,GPIO_PIN_3)
#define DO_AC_CH2_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_3);s_tReg->AcPowerControl &= ~(1<<1);}

#define DO_DC1_CH2_ON				gpio_bit_set(GPIOG,GPIO_PIN_4)
#define DO_DC1_CH2_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_4);s_tReg->DcPowerControl &= ~(1<<2);}

#define DO_DC2_CH2_ON				gpio_bit_set(GPIOG,GPIO_PIN_5)
#define DO_DC2_CH2_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_5);s_tReg->DcPowerControl &= ~(1<<3);}

#define DO_AC_CH3_ON				gpio_bit_set(GPIOG,GPIO_PIN_6)
#define DO_AC_CH3_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_6);s_tReg->AcPowerControl &= ~(1<<2);}

#define DO_DC1_CH3_ON				gpio_bit_set(GPIOG,GPIO_PIN_7)
#define DO_DC1_CH3_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_7);s_tReg->DcPowerControl &= ~(1<<4);}

#define DO_DC2_CH3_ON				gpio_bit_set(GPIOG,GPIO_PIN_8)
#define DO_DC2_CH3_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_8);s_tReg->DcPowerControl &= ~(1<<5);}

#define DO_AC_CH4_ON				gpio_bit_set(GPIOG,GPIO_PIN_9)
#define DO_AC_CH4_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_9);s_tReg->AcPowerControl &= ~(1<<3);}

#define DO_DC1_CH4_ON				gpio_bit_set(GPIOG,GPIO_PIN_10)
#define DO_DC1_CH4_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_10);s_tReg->DcPowerControl &= ~(1<<6);}

#define DO_DC2_CH4_ON				gpio_bit_set(GPIOG,GPIO_PIN_11)
#define DO_DC2_CH4_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_11);s_tReg->DcPowerControl &= ~(1<<7);}

#define DO_AC_CH5_ON				gpio_bit_set(GPIOG,GPIO_PIN_12)
#define DO_AC_CH5_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_12);s_tReg->AcPowerControl &= ~(1<<4);}

#define DO_DC1_CH5_ON				gpio_bit_set(GPIOG,GPIO_PIN_13)
#define DO_DC1_CH5_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_13);s_tReg->DcPowerControl &= ~(1<<8);}

#define DO_DC2_CH5_ON				gpio_bit_set(GPIOG,GPIO_PIN_14)
#define DO_DC2_CH5_OFF			{gpio_bit_reset(GPIOG,GPIO_PIN_14);s_tReg->DcPowerControl &= ~(1<<9);}

#define DO_AC_CH6_ON				gpio_bit_set(GPIOG,GPIO_PIN_15)
#define DO_AC_CH6_OFF				{gpio_bit_reset(GPIOG,GPIO_PIN_15);s_tReg->AcPowerControl &= ~(1<<5);}

#define DO_DC1_CH6_ON				gpio_bit_set(GPIOB,GPIO_PIN_12)
#define DO_DC1_CH6_OFF			{gpio_bit_reset(GPIOB,GPIO_PIN_12);s_tReg->DcPowerControl &= ~(1<<10);}

#define DO_DC2_CH6_ON				gpio_bit_set(GPIOB,GPIO_PIN_13)
#define DO_DC2_CH6_OFF			{gpio_bit_reset(GPIOB,GPIO_PIN_13);s_tReg->DcPowerControl &= ~(1<<11);}

#define DO_DC3_ON						gpio_bit_set(GPIOC,GPIO_PIN_10)
#define DO_DC3_OFF					{gpio_bit_reset(GPIOC,GPIO_PIN_10);s_tReg->DcPowerControl &= ~(1<<12);}

#define DO_LS1_ON						gpio_bit_set(GPIOD,GPIO_PIN_14)//gpio_bit_set(GPIOB,GPIO_PIN_5)
#define DO_LS1_OFF					{gpio_bit_reset(GPIOD,GPIO_PIN_14);s_tReg->DcPowerControl &= ~(1<<13);}

#define DO_LS2_ON						gpio_bit_set(GPIOB,GPIO_PIN_6)
#define DO_LS2_OFF					{gpio_bit_reset(GPIOB,GPIO_PIN_6);s_tReg->DcPowerControl &= ~(1<<14);}

#define DO_1553B_ON					gpio_bit_set(GPIOD,GPIO_PIN_15)
#define DO_1553B_OFF				{gpio_bit_reset(GPIOD,GPIO_PIN_15);s_tReg->DcPowerControl &= ~(1<<15);}

#define DO_LS3_ON						gpio_bit_set(GPIOC,GPIO_PIN_8)
#define DO_LS3_OFF					gpio_bit_reset(GPIOC,GPIO_PIN_8)

#define DO_LS4_ON						gpio_bit_set(GPIOC,GPIO_PIN_9)
#define DO_LS4_OFF					gpio_bit_reset(GPIOC,GPIO_PIN_9)

void Port_Init(void);
void Wdt_Toggle(void);
uint8_t Wire_Check(void);
#endif

