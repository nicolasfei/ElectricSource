/* Copyright (C), 20022-2022,
* file:    Pinout.c
* brief:   Welder parts control GPIO parameter configuration
* author:  LiYi
* version: 1.0
* date:    2022-06-25
*/

/*Improvement Record
* now version:
* last version:
* brief: 
*/
#include "Pinout.h"


/*-----------------------------------------------------------------
函数名称: void Port_Init(void)
函数功能: 端口初始化
参    数: 
返 回 值: 无
-----------------------------------------------------------------*/
void Port_Init(void)
{
		rcu_periph_clock_enable(RCU_GPIOB);//使能PORTB时钟
		rcu_periph_clock_enable(RCU_GPIOC);//使能PORTC时钟
		rcu_periph_clock_enable(RCU_GPIOD);//使能PORTD时钟
		rcu_periph_clock_enable(RCU_GPIOG);//使能PORTG时钟
		
	
		gpio_deinit(GPIOG);
		//配置PG0引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_0);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_0);//配置为推挽输出，速度为50M
		
		//配置PG1引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_1);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);//配置为推挽输出，速度为50M
	
		//配置PG2引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_2);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);//配置为推挽输出，速度为50M
	
		//配置PG3引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//配置为推挽输出，速度为50M
	
		//配置PG4引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//配置为推挽输出，速度为50M
		
		//配置PG5引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//配置为推挽输出，速度为50M
		
		//配置PG6引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_6);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);//配置为推挽输出，速度为50M
		
		//配置PG7引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_7);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);//配置为推挽输出，速度为50M
		
		//配置PG8引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_8);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);//配置为推挽输出，速度为50M
		
		//配置PG9引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_9);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_9);//配置为推挽输出，速度为50M
		
		//配置PG10引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_10);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);//配置为推挽输出，速度为50M
		
		//配置PG11引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_11);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_11);//配置为推挽输出，速度为50M
		
		//配置PG12引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_12);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_12);//配置为推挽输出，速度为50M
		
		//配置PG13引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_13);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_13);//配置为推挽输出，速度为50M
		
		//配置PG14引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_14);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_14);//配置为推挽输出，速度为50M
		
		//配置PG15引脚的模式
		gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_15);//配置为下拉模式
		gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);//配置为推挽输出，速度为50M
		
		gpio_deinit(GPIOC);
		//配置PC0引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_0);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_0);//配置为推挽输出，速度为50M
		
		//配置PC1引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_1);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);//配置为推挽输出，速度为50M
	
		//配置PC2引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_2);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);//配置为推挽输出，速度为50M
	
		//配置PC3引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//配置为推挽输出，速度为50M
	
		//配置PC4引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//配置为推挽输出，速度为50M
		
		//配置PC5引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//配置为推挽输出，速度为50M
		
		//配置PC8引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_8);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);//配置为推挽输出，速度为50M
		
		//配置PC9引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_9);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_9);//配置为推挽输出，速度为50M
		
		//配置PC10引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_10);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);//配置为推挽输出，速度为50M
		
		//配置PC11引脚的模式
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_11);//配置为下拉模式
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_11);//配置为推挽输出，速度为50M
		
		//配置PB5引脚的模式
		gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//配置为推挽输出，速度为50M
		
		//配置PB6引脚的模式
		gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_6);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);//配置为推挽输出，速度为50M
		
		//配置PB12引脚的模式
		gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_12);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_12);//配置为推挽输出，速度为50M
		
		//配置PB13引脚的模式
		gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_13);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_13);//配置为推挽输出，速度为50M
		
		//配置PD1引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_1);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);//配置为推挽输出，速度为50M
		
		//配置PD11引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_11);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_11);//配置为推挽输出，速度为50M
		
		//配置PD11引脚的模式---NetLabelLS5V		控制离散量的5V电源
		gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_14);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_14);//配置为推挽输出，速度为50M
		
		//配置PD11引脚的模式---控制1553B的电源
		gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_15);//配置为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);//配置为推挽输出，速度为50M
		
		//配置PD7引脚的模式----线缆检测
		gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_8);//配置为输入模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);//配置为推挽输出，速度为50M
}


void Wdt_Toggle(void)
{
		gpio_bit_write(GPIOD,GPIO_PIN_11,(bit_status)(1-gpio_output_bit_get(GPIOD,GPIO_PIN_11)));
}

uint8_t Wire_Check(void)
{
		return gpio_input_bit_get(GPIOD,GPIO_PIN_8);
}
