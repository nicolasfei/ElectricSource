/*********************************************************************
* 版权所有 (C)2023, 成都弧源科技有限公司
* 
* 文件名称： // CommIndicator.c
* 文件标识： // 
* 内容摘要： // 通信状态指示程序
* 其它说明： // 
* 当前版本： // V1.0
* 作     者：// 0001
* 完成日期： // 20230104
* 
* 修改记录
* 修改日期：
* 修 改 人：
* 修改内容： 
**********************************************************************/
#include "gd32f4xx.h"
#include "CommIndicator.h"
#include "ErrorControl.h"


void Heart_LED_Toggle(void)
{
		gpio_bit_write(GPIOD,GPIO_PIN_1,(bit_status)(1-gpio_output_bit_get(GPIOD,GPIO_PIN_1)));
}


void Heart_LED_Enable(void)
{
		gpio_bit_set(GPIOD,GPIO_PIN_1);
}

/**********************************************************************
* 函数名称： // void CommIndicatorTask(char *pcOnlineFlag)
* 功能描述： // 通信状态指示程序
* 访问的表： //
* 修改的表： //
* 输入参数： // *pcOnlineFlag：通信在线标志  >0： 在线，闪烁显示  0：离线，熄灭
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 其它说明
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/

void CommIndicatorTask(void)
{
		if(1 == ReadErrorStatus())
		{
				Heart_LED_Enable(); //PB2  //故障常亮
		}
		else
		{
				Heart_LED_Toggle();  //面板联通闪烁
		}
}

