#include "PWM.h"
#include "gd32f4xx.h"

/*-----------------------------------------------------------------
函数名称: void PWM_Init(void)
函数功能: PWM初始化	  
参    数: 
返 回 值:
-----------------------------------------------------------------*/	
void PWM_Init(void)
{
		timer_parameter_struct timer1_init;
		timer_oc_parameter_struct timer1_ocintpara;
		
		/*	关闭定时器1		*/
		timer_deinit(TIMER1);
		/*	开启对应引脚时钟	*/
		rcu_periph_clock_enable(RCU_GPIOB);
		/*	开启定时器3时钟	*/
		rcu_periph_clock_enable(RCU_TIMER1);
		/*  配置定时器时钟   CK_TIMERx = 4 x CK_APB1 = 4x50M = 200MHZ */
		rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
		
    gpio_mode_set(GPIOB,GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10 | GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10 | GPIO_PIN_11);
    gpio_af_set(GPIOB,GPIO_AF_1, GPIO_PIN_10 | GPIO_PIN_11);
		
		/* TIMER1 configuration */
		timer1_init.prescaler         = 9;
		timer1_init.alignedmode       = TIMER_COUNTER_EDGE;
		timer1_init.counterdirection  = TIMER_COUNTER_UP;
		timer1_init.period            = PERIOD;							//20kHz
		timer1_init.clockdivision     = TIMER_CKDIV_DIV1;
		timer1_init.repetitioncounter = 0;
		timer_init(TIMER1,&timer1_init);
		
		/* CH1 configuration in PWM mode */
		timer1_ocintpara.outputstate  = TIMER_CCX_ENABLE;
		timer1_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
		timer1_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
		timer1_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
		timer1_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
		timer1_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

		timer_channel_output_config(TIMER1,TIMER_CH_2,&timer1_ocintpara);
		timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,NONE_DUTY);
		timer_channel_output_mode_config(TIMER1,TIMER_CH_2,TIMER_OC_MODE_PWM0);
		timer_channel_output_shadow_config(TIMER1,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
		
		timer_channel_output_config(TIMER1,TIMER_CH_3,&timer1_ocintpara);
		timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,NONE_DUTY);
		timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
		timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
		
		
		/* auto-reload preload enable */
		timer_auto_reload_shadow_enable(TIMER1);
		/* 所有通道输出使能 */
		timer_primary_output_config(TIMER1, ENABLE);
		/* enable TIMER1 */
		timer_enable(TIMER1);
}

void FanTurnOff(int channel)
{
	switch(channel)
	{
		case 0:
			/* CH2 configuration in PWM mode0,duty cycle 0% */
			timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,MIN_DUTY);
			timer_channel_output_mode_config(TIMER1,TIMER_CH_2,TIMER_OC_MODE_PWM0);
			timer_channel_output_shadow_config(TIMER1,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
		break;
		case 1:
			/* CH3 configuration in PWM mode0,duty cycle 0% */
			timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,MIN_DUTY);
			timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
			timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
		break;
		default:
			break;
	}
}

void FanTurnOn(int channel, unsigned short Duty)
{
	switch(channel)
	{
		case 0:
			/* CH2 configuration in PWM mode0,duty cycle 0% */
			timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,Duty);
			timer_channel_output_mode_config(TIMER1,TIMER_CH_2,TIMER_OC_MODE_PWM0);
			timer_channel_output_shadow_config(TIMER1,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
		break;
		case 1:
			/* CH3 configuration in PWM mode0,duty cycle 0% */
			timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,Duty);
			timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
			timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
		break;
		default:
			break;
	}
}

