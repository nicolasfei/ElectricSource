/*
 *  Wdg.c
 *
 *  Created on: 20220514
 *  Author: LiYi
 */
 
#include "WatchDog.h"
#include "gd32f4xx.h"

/*-----------------------------------------------------------------
函数名称: void WDG_Init(char cPrer,int cRlr)
函数功能: 独立看门狗初始化
参    数: cPrer:分频数:0~7(只有低3位有效!)
          分频因子=4*2^cPrer.但最大值只能是256!
          cRlr:重装载寄存器值:低11位有效.
          时间计算(大概):Tout=((4*2^cPrer)*cRlr)/40 (ms).
返 回 值: 无
-----------------------------------------------------------------*/
void Wdg_Init(short wReload, short wPrescaler) 
{
		rcu_osci_on(RCU_IRC32K);
		fwdgt_write_enable();  //使能对IWDG->PR和IWDG->RLR的写		 										  
		fwdgt_config(wReload,wPrescaler); 
		fwdgt_counter_reload();//reload											   
		fwdgt_enable();        //使能看门狗	
}

void Wdg_Reload(void)
{
		fwdgt_counter_reload();
}
