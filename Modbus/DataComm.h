/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // Modbus.h
* 文件标识： // 
* 内容摘要： // 外部串口数据处理程序
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

#ifndef __DATACOMM_H
#define __DATACOMM_H

#include "gd32f4xx.h"
#include "spi.h"

#define SLAVE_ADDR          0x06
#define START_ADDR          0x00

#define PRESET_STATUS_NUM   10 
#define FEEDBACK_STATUS_NUM 10

#define HOLD_REG_NUM        (168)
#define INPUT_REG_NUM       10

typedef struct
{
		/*R*/
		int SelfInspectionStatus;
		int Ac380VaInputCurrent;		//by bruce
		int Ac380VbInputCurrent;
		int Ac380VcInputCurrent;
		int Ac220VInputVoltage;
		int Ac220VInputCurrent;
		int Ac115VaInputVoltage;
		int Ac115VbInputVoltage;
		int Ac115VcInputVoltage;
		int Ac115VaInputCurrent;
		int Ac115VbInputCurrent;
		int Ac115VcInputCurrent;
	
		int Ac115VaOutputVoltage;
		int Ac115VbOutputVoltage;
		int Ac115VcOutputVoltage;
		int Ac115VaOutputCurrent;
		int Ac115VbOutputCurrent;
		int Ac115VcOutputCurrent;
		int Dc28V1OutputVoltage;
		int Dc28V1OutputCurrent;
		int Dc28V2OutputVoltage;
		int Dc28V2OutputCurrent;
		
		int Dc28V1Ch1OutputVoltage;
		int Dc28V1Ch1OutputCurrent;
		int Dc28V2Ch1OutputVoltage;
		int Dc28V2Ch1OutputCurrent;
		int Ac115VaCh1OutputVoltage;
		int Ac115VbCh1OutputVoltage;
		int Ac115VcCh1OutputVoltage;
		int Ac115VaCh1OutputCurrent;
		int Ac115VbCh1OutputCurrent;
		int Ac115VcCh1OutputCurrent;
		
		int Dc28V1Ch2OutputVoltage;
		int Dc28V1Ch2OutputCurrent;
		int Dc28V2Ch2OutputVoltage;
		int Dc28V2Ch2OutputCurrent;
		int Ac115VaCh2OutputVoltage;
		int Ac115VbCh2OutputVoltage;
		int Ac115VcCh2OutputVoltage;
		int Ac115VaCh2OutputCurrent;
		int Ac115VbCh2OutputCurrent;
		int Ac115VcCh2OutputCurrent;
		
		int Dc28V1Ch3OutputVoltage;
		int Dc28V1Ch3OutputCurrent;
		int Dc28V2Ch3OutputVoltage;
		int Dc28V2Ch3OutputCurrent;
		int Ac115VaCh3OutputVoltage;
		int Ac115VbCh3OutputVoltage;
		int Ac115VcCh3OutputVoltage;
		int Ac115VaCh3OutputCurrent;
		int Ac115VbCh3OutputCurrent;
		int Ac115VcCh3OutputCurrent;
		
		int Dc28V1Ch4OutputVoltage;
		int Dc28V1Ch4OutputCurrent;
		int Dc28V2Ch4OutputVoltage;
		int Dc28V2Ch4OutputCurrent;
		int Ac115VaCh4OutputVoltage;
		int Ac115VbCh4OutputVoltage;
		int Ac115VcCh4OutputVoltage;
		int Ac115VaCh4OutputCurrent;
		int Ac115VbCh4OutputCurrent;
		int Ac115VcCh4OutputCurrent;
		
		int Dc28V1Ch5OutputVoltage;
		int Dc28V1Ch5OutputCurrent;
		int Dc28V2Ch5OutputVoltage;
		int Dc28V2Ch5OutputCurrent;
		int Ac115VaCh5OutputVoltage;
		int Ac115VbCh5OutputVoltage;
		int Ac115VcCh5OutputVoltage;
		int Ac115VaCh5OutputCurrent;
		int Ac115VbCh5OutputCurrent;
		int Ac115VcCh5OutputCurrent;
		
		int Dc28V1Ch6OutputVoltage;
		int Dc28V1Ch6OutputCurrent;
		int Dc28V2Ch6OutputVoltage;
		int Dc28V2Ch6OutputCurrent;
		int Ac115VaCh6OutputVoltage;
		int Ac115VbCh6OutputVoltage;
		int Ac115VcCh6OutputVoltage;
		int Ac115VaCh6OutputCurrent;
		int Ac115VbCh6OutputCurrent;
		int Ac115VcCh6OutputCurrent;
		
		int Dc28V3OutputVoltage;
		int Dc28V3OutputCurrent;
		int Discrete5Voltage;
		int Com1553B5Voltage;
		
		int Temperature;
		int Version;
		int CableStatus;
		
		/*RW*/
		//int Reserved1;		//2024/1/13  remove
		int RunMode;
		int DcPowerControl;
		int AcPowerControl;
		
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
		
		int Dc28V1Ch1SetVoltage;
		int Dc28VC2h1SetVoltage;
		
		int Dc28V1Ch2SetVoltage;
		int Dc28VC2h2SetVoltage;
		
		int Dc28V1Ch3SetVoltage;
		int Dc28VC2h3SetVoltage;
		
		int Dc28V1Ch4SetVoltage;
		int Dc28VC2h4SetVoltage;
		
		int Dc28V1Ch5SetVoltage;
		int Dc28VC2h5SetVoltage;
		
		int Dc28V1Ch6SetVoltage;
		int Dc28VC2h6SetVoltage;
		
		int PowerOff;
		int Reserved2;
		
		int Ac380VaOutputVoltage;		//by bruce--新增加
		int Ac380VbOutputVoltage;
		int Ac380VcOutputVoltage;
		int FanControlValue;				//by bruce--手动控制风机，RunMode运行模式为工作模式（1）且FanControlValue>0的时候，才由本寄存器控制
		int FanControlFeedback;			//by bruce--风机PWM设定值反馈
		int FanCurrent;							//by bruce--风机电流
		int FanTemperature;					//by bruce--风机温度
		
		//新增2024-06-03
		int Dc28V1CurrentSet;				//输出28VDC1 总电流设定
		int Dc28V2CurrentSet;				//输出28VDC2 总电流设定
		
		int Ac115IaCurrentSet;			//输出115V A相 总电流设定
		int Ac115IbCurrentSet;			//输出115V B相 总电流设定
		int Ac115IcCurrentSet;			//输出115V C相 总电流设定
		
		int Dc28V1CurrentCompensate;				//输出28VDC1 总电流补偿
		int Dc28V2CurrentCompensate;				//输出28VDC2 总电流补偿
}T_REG;

void ModbusResponseTask(void);
void ModbusRegInit(void);
T_REG* ReadReg(void);
unsigned char* ReadOnLineVal(void);
void SetAcDcDio(int ac, int dc);
int GetAcDioSet(void);
int GetDcDioSet(void);

#endif








