/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // TaskManage.c
* 文件标识： // 
* 内容摘要： // 焊机内部器件控制
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

#include "usart.h"
#include "ErrorControl.h"
#include "SysTick.h"
#include "DispParam.h"
#include "CommIndicator.h"
#include "DataComm.h"
#include "UserTimer.h"
#include "Pinout.h"
#include "spi.h"
#include "GetAdc.h"
#include "OutSwitch.h"
#include "GetTemp.h"
#include "Ds18b20.h"
#include "PWM.h"
#include "gd32f4xx.h"                   // Device header
#include "stdint.h"

static char HeartBit = 0;

/**
	*	读取风机温度
	*/
void readFanTemp(void)
{
	int value=0;
	int fanValue=0;
	T_REG* t_Reg = ReadReg();
	if(t_Reg->RunMode == 1 && t_Reg->FanControlValue>2)		//上位机手动控制风机
	{
		FanTurnOn(FAN_ID_1, t_Reg->FanControlValue);
		FanTurnOn(FAN_ID_2, t_Reg->FanControlValue);
		fanValue = t_Reg->FanControlValue;
	}
	else
	{
		value = DS18B20_ReadTemp(DS18B20_Fan);		//温度值=实际温度值*10（保留一位小数）
		if(DS18B20_Temp_Finish(DS18B20_Fan))
		{
			if(value<=200)
			{
				FanTurnOn(FAN_ID_1,LOW_DUTY);
				FanTurnOn(FAN_ID_2,LOW_DUTY);
				fanValue = LOW_DUTY;
			}
			else if(value>200 && value<=300)
			{
				FanTurnOn(FAN_ID_1, SMALL_DUTY);
				FanTurnOn(FAN_ID_2, SMALL_DUTY);
				fanValue = SMALL_DUTY;
			}
			else if(value>300 && value<=500)
			{
				FanTurnOn(FAN_ID_1,	MED_DUTY);
				FanTurnOn(FAN_ID_2, MED_DUTY);
				fanValue = MED_DUTY;
			}
			else
			{
				FanTurnOn(FAN_ID_1, HIGH_DUTY);
				FanTurnOn(FAN_ID_2, HIGH_DUTY);
				fanValue = HIGH_DUTY;
			}
		}
	}
	//返回风机设定值给上位机
	if(fanValue>0)
	{
		t_Reg->FanControlValue = fanValue;
	}
}

/**
	*	读温度传感器
	*/
void readBoxTemp(void)
{
	int value=0;
	T_REG* t_Reg = ReadReg();
	
	value = DS18B20_ReadTemp(DS18B20_TEMP);		//温度值=实际温度值*10（保留一位小数）
	if(DS18B20_Temp_Finish(DS18B20_TEMP))
	{
		t_Reg->Temperature = value*10;					//寄存器值等于实际值*100；
	}
}

/**********************************************************************
* 函数名称： // static void OneMsTask(void)
* 功能描述： // 1ms周期运行任务
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
static void OneMsTask(void)
{
		TickCountTask();
	
		//SPI读取ADC数据采集
	gpio_bit_write(GPIOD,GPIO_PIN_1,1);
		Read_SPI_All();
	gpio_bit_write(GPIOD,GPIO_PIN_1,0);
}

/**********************************************************************
* 函数名称： // static void TenMsTask(void)
* 功能描述： // 10ms周期运行任务
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
static void TenMsTask(void)
{
		//通道切换
		HC4051_Switch();
		//ADC数据滤波
		FilterSpiData();
		//数据检测
		CheckAdcData();
		//ADC数据更新
		UpdateAdcData();
}
 
/**********************************************************************
* 函数名称： // static void HundredMsTask(void)
* 功能描述： // 100ms周期运行任务
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
static void HundredMsTask(void)
{
		//线缆检测
		ReadReg()->CableStatus = Wire_Check();
	
		//modbus数据交互
		ModbusResponseTask();
	
		//控制直/交流电源控制
		HC245_Power_Switch_Config();
	
		//读温度传感器
		readBoxTemp();
		
		//读取风扇温度
		readFanTemp();
	
		Wdt_Toggle();
		
		//显示数据到数码管
		DispUpdateTask();
		
		if(*ReadOnLineVal())
		{
				(*ReadOnLineVal())--;
		}
		
		//心跳灯
//		HeartBit = ~HeartBit;
//		gpio_bit_write(GPIOD,GPIO_PIN_1,HeartBit);
}

/**********************************************************************
* 函数名称： // static void TwoHundredsMsTask(void)
* 功能描述： // 500ms周期运行任务
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
static void FiveHundredsMsTask(void)
{
}

/**********************************************************************
* 函数名称： // static void ThousandMsTask(void)
* 功能描述： // 1000ms周期运行任务
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
static void ThousandMsTask(void)
{
}

/**********************************************************************
* 函数名称： // void TaskManage(void)
* 功能描述： // 任务管理器
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 无
* 其它说明： // 1s更新一次
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
void TaskManage(void)
{
		TASK_FUNC TaskMap[] = {&OneMsTask,&TenMsTask,&HundredMsTask,&FiveHundredsMsTask,&ThousandMsTask};
		TaskProcess(TaskMap);
}

