#ifndef __SYSTICK_H
#define __SYSTICK_H

#define TASK_END   0

#define TASK_START 1

#define TASK_NUM   5

typedef void (*TASK_FUNC)(void);	

typedef struct
{
		char  cRunFlag;    //运行标志  0:不运行 1:运行
		short cTimeCnt;   //时间计数
		short cTimeNum;   //设置时间
}T_TASK;


/*-----------------------------------------------------------------
函数名称: void SysTick_Init(void)
函数功能: SysTick初始化
参    数: 无
返 回 值: 无
-----------------------------------------------------------------*/
void SysTick_Init(void);
void TaskSchedule(T_TASK *ptTask);
void TaskProcess(TASK_FUNC *pTaskFunc);

void DelayUs(volatile unsigned int us);
#endif
