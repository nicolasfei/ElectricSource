#include "gd32f4xx.h"
#include "SysTick.h"

#define CAL_INT		(100)

static T_TASK s_tTask[TASK_NUM]={{TASK_END,1,1},{TASK_END,CAL_INT,CAL_INT},{TASK_END,CAL_INT*8,CAL_INT*8},
																				{TASK_END,CAL_INT*8,CAL_INT*8},{TASK_END,CAL_INT*8,CAL_INT*8}};

void TaskSchedule(T_TASK *ptTask);

 /*
函数功能: 延时us单位
*/
void DelayUs(volatile unsigned int us)
{
#if 1//	_SYSTICK_IRQ_
	int i,j;
	for(i=0;i<us;i++)
		for(j=0;j<36;j++);		//36---1us
#else
	uint32_t tmp;
	SysTick->VAL=0;         //CNT计数器值	
	SysTick->LOAD=9*us;     //9表示1us
	SysTick->CTRL|=1<<0;    //开启定时器	
	do
	{
			tmp=SysTick->CTRL; //读取状态
	}while((!(tmp&1<<16))&&(tmp&1<<0));
	SysTick->VAL=0;         //CNT计数器值	
	SysTick->CTRL&=~(1<<0); //关闭定时器	
#endif	
}

/*-----------------------------------------------------------------
函数名称: void SysTick_Init(void)
函数功能: SysTick初始化
参    数: 无
返 回 值: 无
-----------------------------------------------------------------*/
void SysTick_Init(void)
{	  	
		SysTick->CTRL &= (~(1 << 0)); /*禁止SysTick定时器*/
		SysTick->CTRL &= (~(1 << 1)); /*禁止SysTick中断*/
		SysTick->CTRL &= (~(1 << 2)); /*选择20M时钟源*/
		SysTick->LOAD  = 25000;       /*120M÷8=15M  15M/15000=1ms*/
		SysTick->CTRL |= (1 << 1);    /*使能SysTick中断*/
		SysTick->CTRL |= (1 << 0);    /*使能SysTick定时器*/
}

void SysTick_Handler(void)
{
		if((SysTick->CTRL & (1 << 16)) != 0)	
		{
				TaskSchedule(s_tTask);
		}
}

void TaskSchedule(T_TASK *ptTask)
{
		char i;
		for(i = 0; i < TASK_NUM; i++)
		{
				if(ptTask[i].cTimeCnt)
				{
						ptTask[i].cTimeCnt--;
						if(ptTask[i].cTimeCnt == 0)
						{
								ptTask[i].cTimeCnt = ptTask[i].cTimeNum;
								ptTask[i].cRunFlag = TASK_START;
						}
				}
		}
}


void TaskProcess(TASK_FUNC *pTaskFunc)
{
		char i;
		for(i = 0; i < TASK_NUM; i++)
		{
				if(s_tTask[i].cRunFlag == TASK_START)
				{
						pTaskFunc[i]();
						s_tTask[i].cRunFlag = TASK_END;
						
				}
		}
}
