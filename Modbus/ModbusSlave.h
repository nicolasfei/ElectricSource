/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // Modbus.h
* 文件标识： // 
* 内容摘要： // 串口数据处理程序
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
#ifndef __MODBUSSLAVE_H
#define __MODBUSSLAVE_H

#include "usart.h"

typedef struct
{
		unsigned char cSlaveId;
		unsigned char *pcRxData;
		unsigned char cRxFrameEndFlag;
		unsigned char *pcSlaveOnlineVal;
		unsigned char *pcCoilStatus;
		unsigned char *pcInputStatus;
		int *pwHoldReg;
		int *pwInputReg;
		unsigned short *pcRxCnt;
		unsigned short wStartAddr;
		unsigned int wUsartPeriph;
}MODBUS_SLAVE_PARAM;

void ModbusSlaveResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam);

#endif

