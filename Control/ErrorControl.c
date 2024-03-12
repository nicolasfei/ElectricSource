/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // ErrorControl.c
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
#include "ErrorControl.h"
#include "DataComm.h"

static unsigned long s_wErrorCode = 0;
static short s_wDlyError = 0;
static T_ERROR_REG v_ErrReg = {0};
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
void ErrorDetectionTask(void)
{
//		if(1 == ReadOverHeatStatus())
//		{
//				s_wErrorCode = ERR_OH_IGBT;
//				s_wDlyError = 20;
//		}

		if(s_wDlyError)
    {
        s_wDlyError --;
    }
		else
		{
				s_wErrorCode = NOERR;
		}
}

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
unsigned long ReadErrorCode(void)
{
		return s_wErrorCode;
}

/**
	*读取最高优先级的故障码
	*/
char ReadFirstErrorStatus(void)
{
	int i=0;
	int mask=1;
	char code=0;
	for(i=0; i<64; i++)
	{
		if(s_wErrorCode | (mask<<i))
		{
			code = i;
			break;
		}
	}
	return code;
}

/**
	* 设备工作状态
	*/
void DeviceWorkStatus(char status)
{
	T_REG *s_tReg=0;
	
	s_tReg = ReadReg();
	s_tReg->SelfInspectionStatus = status;	//设备状态
}

/**
	*	设置故障码
	*	@par errorID 故障码编号
	*/
void SetErrorCode(short errorID)
{
	unsigned long i=1;
	
	s_wErrorCode = s_wDlyError | (i<<errorID);
	//故障寄存器
	if(s_wErrorCode>0){
		DeviceWorkStatus(DEVICE_WORK_FAULT);
	}
}

/**
	*	清空故障码
	*	@par errorID 故障码编号
	*/
void ResetErrorCode(int errorID)
{
	unsigned long i=1;
	
	s_wErrorCode = s_wDlyError & (~(i<<errorID));
	//故障寄存器
	if(s_wErrorCode==0){
		DeviceWorkStatus(DEVICE_WORK_NORMAL);
	}
}

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
char ReadErrorStatus(void)
{
		if(s_wErrorCode != 0)
		{
				return 1;
		}
		else
		{
				return 0;
		}
}


/**
	* 获取故障值
	*/
T_ERROR_REG* ReadErrorReg(void)
{
	return &v_ErrReg;
}

