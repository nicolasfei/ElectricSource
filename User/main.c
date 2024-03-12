/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // main.c
* 文件标识： // 
* 内容摘要： // 焊机控制main程序
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
#include "Pinout.h"
#include "WatchDog.h"
#include "SysTick.h"
#include "TaskManage.h"
#include "usart.h"
#include "spi.h"
#include "TM1640.h"
#include "PWM.h"
#include "GetAdc.h"
#include "OutSwitch.h"
#include "Ds18b20.h"
#include "ErrorControl.h"
#include "math.h"
#include "DispParam.h"
/**********************************************************************
* 函数名称： // int main(void)
* 功能描述： // 焊机控制 main程序
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
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
//unsigned short data[16] = {0x3f,0x06,0x5b,0x34f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int main(void)
{ 	
	int i=0;
		Port_Init();                //端口初始化
		HC245_Set();
		SysTick_Init();
		Usart1_init(115200);
		XL2543_Init();
		TM1640_IO_Init();
		TM1640_Disp_Init();
		PWM_Init();
		FanTurnOn(FAN_ID_1,LOW_DUTY);			//开机开最小挡位
		FanTurnOn(FAN_ID_2,LOW_DUTY);			//开机开最小挡位
		
		DS18B20_Init();
		Lpf_Init();							//一阶滤波器初始化
		
		ModbusRegInit();				//Modbus 寄存器数据初始化
	
		DispFull();							//数码管显示0
	
		DeviceWorkStatus(DEVICE_CHECK_SUCCESS);		//设备自检中
		
		for(i=0; i<3; i++){
		ModbusResponseTask();			//modbus数据交互
		DelayUs(1000000);
		}
		DeviceWorkStatus(DEVICE_WORK_NORMAL);			//设备正常工作
		ModbusResponseTask();			//modbus数据交互
		
		HC4051_Switch_do(0);
		
		//Wdg_Init(800,FWDGT_PSC_DIV64);    	      //与分频数为64,重载值为800,溢出时间为1.28s
		while(1)
		{ 
			//Wdg_Reload();        //喂狗
			TaskManage();
		}
}
