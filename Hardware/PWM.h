#ifndef __PWM_H
#define __PWM_H 	

#define PERIOD     	9999	//2k     999   //20kHz
#define MAX_DUTY   	9999   //100%
#define HIGH_DUTY   2000   //75%
#define MED_DUTY   	4500   //50%
#define SMALL_DUTY  6000   //30%
#define LOW_DUTY   	8000	 //15%
#define NONE_DUTY   9900		//0%
#define MIN_DUTY   	0    	//0%

#define FAN_ID_1		0
#define FAN_ID_2		1

/*-----------------------------------------------------------------
函数名称: void PWM_Init(void)
函数功能: PWM初始化	  
参    数: 这里时钟选择为APB1的2倍，而APB1为36M
					arr:自动重装值。psc:时钟预分频数
		      Tout=(arr+1)*(psc+1)/Tclk    Tout:输出时间（us）
		      Tclk:输入频率(MHz)
返 回 值:
-----------------------------------------------------------------*/	
void PWM_Init(void);
void FanTurnOff(int channel);
void FanTurnOn(int channel, unsigned short Duty);
#endif
