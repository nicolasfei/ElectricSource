/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // ErrorControl.h
* 文件标识： // 
* 内容摘要： // 故障控制程序
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

#ifndef __ERRORCONTROL_H
#define __ERRORCONTROL_H

#include "stdio.h"
#include "stdlib.h"

#define NOERR             0
#define ERR_OH_IGBT       1
#define ERR_OH_DIODE      2
#define ERR_OH_LEFT_OUT   3
#define ERR_OH_RIGHT_OUT  4
#define ERR_LACKPHASE     5
#define ERR_UV            6
#define ERR_OV            7
#define ERR_OC            8
#define ERR_IGBT_SHORT    9
#define ERR_FLOW_BLOCK    10
#define ERR_COMM_BREAK    11

#define ERR_CH1_28VDC1_V		0
#define ERR_CH1_28VDC1_I		1
#define ERR_CH1_28VDC2_V		2
#define ERR_CH1_28VDC2_I		3
#define ERR_CH1_115V_T_V		4
#define ERR_CH1_115V_T_I		5
#define ERR_CH1_115V_S_V		6
#define ERR_CH1_115V_S_I		7

#define ERR_CH2_28VDC1_V		8
#define ERR_CH2_28VDC1_I		9
#define ERR_CH2_28VDC2_V		10
#define ERR_CH2_28VDC2_I		11
#define ERR_CH2_115V_T_V		12
#define ERR_CH2_115V_T_I		13
#define ERR_CH2_115V_S_V		14
#define ERR_CH2_115V_S_I		15

#define ERR_CH3_28VDC1_V		16
#define ERR_CH3_28VDC1_I		17
#define ERR_CH3_28VDC2_V		18
#define ERR_CH3_28VDC2_I		19
#define ERR_CH3_115V_T_V		20
#define ERR_CH3_115V_T_I		21
#define ERR_CH3_115V_S_V		22
#define ERR_CH3_115V_S_I		23

#define ERR_CH4_28VDC1_V		24
#define ERR_CH4_28VDC1_I		25
#define ERR_CH4_28VDC2_V		26
#define ERR_CH4_28VDC2_I		27
#define ERR_CH4_115V_T_V		28
#define ERR_CH4_115V_T_I		29
#define ERR_CH4_115V_S_V		30
#define ERR_CH4_115V_S_I		31

#define ERR_CH5_28VDC1_V		32
#define ERR_CH5_28VDC1_I		33
#define ERR_CH5_28VDC2_V		34
#define ERR_CH5_28VDC2_I		35
#define ERR_CH5_115V_T_V		36
#define ERR_CH5_115V_T_I		37
#define ERR_CH5_115V_S_V		38
#define ERR_CH5_115V_S_I		39

#define ERR_CH6_28VDC1_V		40
#define ERR_CH6_28VDC1_I		41
#define ERR_CH6_28VDC2_V		42
#define ERR_CH6_28VDC2_I		43
#define ERR_CH6_115V_T_V		44
#define ERR_CH6_115V_T_I		45
#define ERR_CH6_115V_S_V		46
#define ERR_CH6_115V_S_I		47

#define DEVICE_CHECK_FAILE		0
#define DEVICE_CHECK_SUCCESS	1
#define DEVICE_WORK_NORMAL		3
#define DEVICE_WORK_FAULT			4

typedef struct
{	
		int Dc28V1Ch1OverVoltageTransientThd;
		int Dc28V1Ch1OverCurrentTransientThd;
		int Dc28V2Ch1OverVoltageSteadyThd;
		int Dc28V2Ch1OverCurrentSteadyThd;
		int Ac115VCh1OverVoltageTransientThd;
		int Ac115VCh1OverCurrentTransientThd;
		int Ac115VCh1OverVoltageSteadyThd;
		int Ac115VCh1OverCurrentSteadyThd;
		
		int Dc28V1Ch2OverVoltageTransientThd;
		int Dc28V1Ch2OverCurrentTransientThd;
		int Dc28V2Ch2OverVoltageSteadyThd;
		int Dc28V2Ch2OverCurrentSteadyThd;
		int Ac115VCh2OverVoltageTransientThd;
		int Ac115VCh2OverCurrentTransientThd;
		int Ac115VCh2OverVoltageSteadyThd;
		int Ac115VCh2OverCurrentSteadyThd;
		
		int Dc28V1Ch3OverVoltageTransientThd;
		int Dc28V1Ch3OverCurrentTransientThd;
		int Dc28V2Ch3OverVoltageSteadyThd;
		int Dc28V2Ch3OverCurrentSteadyThd;
		int Ac115VCh3OverVoltageTransientThd;
		int Ac115VCh3OverCurrentTransientThd;
		int Ac115VCh3OverVoltageSteadyThd;
		int Ac115VCh3OverCurrentSteadyThd;
		
		int Dc28V1Ch4OverVoltageTransientThd;
		int Dc28V1Ch4OverCurrentTransientThd;
		int Dc28V2Ch4OverVoltageSteadyThd;
		int Dc28V2Ch4OverCurrentSteadyThd;
		int Ac115VCh4OverVoltageTransientThd;
		int Ac115VCh4OverCurrentTransientThd;
		int Ac115VCh4OverVoltageSteadyThd;
		int Ac115VCh4OverCurrentSteadyThd;
		
		int Dc28V1Ch5OverVoltageTransientThd;
		int Dc28V1Ch5OverCurrentTransientThd;
		int Dc28V2Ch5OverVoltageSteadyThd;
		int Dc28V2Ch5OverCurrentSteadyThd;
		int Ac115VCh5OverVoltageTransientThd;
		int Ac115VCh5OverCurrentTransientThd;
		int Ac115VCh5OverVoltageSteadyThd;
		int Ac115VCh5OverCurrentSteadyThd;
		
		int Dc28V1Ch6OverVoltageTransientThd;
		int Dc28V1Ch6OverCurrentTransientThd;
		int Dc28V2Ch6OverVoltageSteadyThd;
		int Dc28V2Ch6OverCurrentSteadyThd;
		int Ac115VCh6OverVoltageTransientThd;
		int Ac115VCh6OverCurrentTransientThd;
		int Ac115VCh6OverVoltageSteadyThd;
		int Ac115VCh6OverCurrentSteadyThd;
}T_ERROR_REG;
/**********************************************************************
* 函数名称： // ErrorDetectionTask
* 功能描述： // 故障检测任务
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
void ErrorDetectionTask(void);

/**********************************************************************
* 函数名称： // short ReadErrorCode(void)
* 功能描述： // 读故障代码
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 故障代码
* 其它说明： // 其它说明
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
unsigned long ReadErrorCode(void);

/**********************************************************************
* 函数名称： // char ReadErrorStatus(void)
* 功能描述： // 读故障代码
* 访问的表： //
* 修改的表： //
* 输入参数： // 无
* 输入参数： // 无
* 输入参数： // 
* 输入参数： // 
* 输出参数： // 
* 返 回 值： // 故障标志
* 其它说明： // 其它说明
* 修改日期       修改人	     修改内容
* -----------------------------------------------
* 2022/11/14	     0001	      XXX
***********************************************************************/
char ReadErrorStatus(void);

/**
	*读取最高优先级的故障码
	*/
char ReadFirstErrorStatus(void);
/**
	*	设置故障码
	*	@par errorID 故障码编号
	*/
void SetErrorCode(short errorID);

/**
	*	清空故障码
	*	@par errorID 故障码编号
	*/
void ResetErrorCode(int errorID);

/**
	* 获取故障值
	*/
T_ERROR_REG* ReadErrorReg(void);

/**
	* 设备工作状态
	*/
void DeviceWorkStatus(char status);

#endif   /*__ERRORCONTROL_H_*/
