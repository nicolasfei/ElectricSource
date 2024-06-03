/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // DispParam.c 
* 文件标识： // 
* 内容摘要： // 显示参数滤波
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
#include <stdlib.h>
#include <stdio.h>
#include "DispParam.h"
#include "Filter.h"
#include "TM1640.h"
#include "ErrorControl.h"
#include "UserTimer.h"
#include "DataComm.h"

long long llBlinTime = 0;
char BlinSts   = 0;
char DispFlag = 0;
char ErrorFlag = 0;
const short SegCode[11] = {CODE_0,CODE_1,CODE_2,CODE_3,CODE_4,CODE_5,CODE_6,CODE_7,CODE_8,CODE_9,CODE_ALL_OFF};

unsigned short DisBuf[16] = {0}; 
unsigned short DisBuf1[16] = {0};
unsigned short DisBuf2[16] = {0};

short Disp_AVolt[7] = {0}; 
short Disp_AAmp[7] = {0}; 
short Disp_BVolt[7] = {0}; 
short Disp_BAmp[7] = {0}; 
short Disp_CVolt[7] = {0}; 
short Disp_CAmp[7] = {0}; 

short Disp_281Volt[7] = {0}; 
short Disp_281Amp[7] = {0}; 
short Disp_282Volt[7] = {0}; 
short Disp_282Amp[7] = {0}; 

/*-------------------------------------------------------------
函数名称: void DISP_Para(short Data,char AV_Flag,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 AV_Flag:电流电压表标志 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_Para(short Data,char AV_Flag,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
    char DigNum = 0;
    DigNum = AV_Flag << 2;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		if(Data >= 0)
    {
				Thousands = (DispData / 1000);
				if(!Thousands)
				{
						if(!Hundreds)
						{
								Hundreds = 10;
						}
						Thousands = 10;
				}
				DisBuf[DigNum + 0] = SegCode[Thousands];
				DisBuf[DigNum + 1] = SegCode[Hundreds];
				DisBuf[DigNum + 2] = SegCode[Tens] | Point;
				DisBuf[DigNum + 3] = SegCode[Ones];
		}
		else
		{
				if(Data < - 99)
				{
						DisBuf[DigNum + 0] = CODE_HYPHEN;
						DisBuf[DigNum + 1] = SegCode[Hundreds];
				}
				else
				{
						DisBuf[DigNum + 0] = CODE_ALL_OFF;
						DisBuf[DigNum + 1] = CODE_HYPHEN;
				}
		}
    DisBuf[DigNum + 2] = SegCode[Tens] | Point;
		DisBuf[DigNum + 3] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_A_Volt(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_A_Volt(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf[0] = SegCode[Thousands];
		DisBuf[1] = SegCode[Hundreds];
		DisBuf[2] = SegCode[Tens] | Point;
		DisBuf[3] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_B_Volt(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_B_Volt(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf[4] = SegCode[Thousands];
		DisBuf[5] = SegCode[Hundreds];
		DisBuf[6] = SegCode[Tens] | Point;
		DisBuf[7] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_C_Volt(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_C_Volt(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf[8] = SegCode[Thousands];
		DisBuf[9] = SegCode[Hundreds];
		DisBuf[10] = SegCode[Tens] | Point;
		DisBuf[11] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_A_Amp(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_A_Amp(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						//Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf1[0] = SegCode[Thousands];
		DisBuf1[1] = SegCode[Hundreds]| Point;
		DisBuf1[2] = SegCode[Tens];
		DisBuf1[3] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_B_Amp(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_B_Amp(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						//Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf1[4] = SegCode[Thousands];
		DisBuf1[5] = SegCode[Hundreds]| Point;
		DisBuf1[6] = SegCode[Tens] ;
		DisBuf1[7] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_C_Amp(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_C_Amp(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						//Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf1[8] = SegCode[Thousands];
		DisBuf1[9] = SegCode[Hundreds] | Point;
		DisBuf1[10] = SegCode[Tens];
		DisBuf1[11] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_281_Volt(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_281_Volt(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf2[0] = SegCode[Thousands];
		DisBuf2[1] = SegCode[Hundreds];
		DisBuf2[2] = SegCode[Tens] | Point;
		DisBuf2[3] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_282_Volt(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_282_Volt(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf2[4] = SegCode[Thousands];
		DisBuf2[5] = SegCode[Hundreds];
		DisBuf2[6] = SegCode[Tens] | Point;
		DisBuf2[7] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_281_Amp(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_281_Amp(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						//Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf2[8] = SegCode[Thousands];
		DisBuf2[9] = SegCode[Hundreds]| Point;
		DisBuf2[10] = SegCode[Tens] ;
		DisBuf2[11] = SegCode[Ones];
}

/*-------------------------------------------------------------
函数名称: void DISP_282_Amp(short Data,char Point)
函数功能: 数显表显示程序
参    数: Data：显示的数据值 Point:小数点
返 回 值: 无
-------------------------------------------------------------*/
void DISP_282_Amp(short Data,char Point)
{
    short Ones = 0;
		short Tens = 0;
		short Hundreds = 0;
		short Thousands = 0;
		short DispData = 0;
		DispData = abs(Data);
    Ones      = (DispData % 10);
    Tens      = (DispData / 10) % 10;
    Hundreds  = (DispData / 100) % 10;
		Thousands = (DispData / 1000);
		if(!Thousands)
		{
				if(!Hundreds)
				{
						//Hundreds = 10;
				}
				Thousands = 10;
		}
		DisBuf2[12] = SegCode[Thousands];
		DisBuf2[13] = SegCode[Hundreds]| Point;
		DisBuf2[14] = SegCode[Tens] ;
		DisBuf2[15] = SegCode[Ones];
}

void CLEAR_Error()
{
	DisBuf2[8] = CODE_ALL_OFF;
	DisBuf2[9] = CODE_ALL_OFF;
	DisBuf2[10] = CODE_ALL_OFF;
	DisBuf2[11] = CODE_ALL_OFF;
	
	DisBuf2[12] = CODE_ALL_OFF;
	DisBuf2[13] = CODE_ALL_OFF;
	DisBuf2[14] = CODE_ALL_OFF;
	DisBuf2[15] = CODE_ALL_OFF;
}

/*-------------------------------------------------------------
函数名称: void DISP_Error(short ErrorCode,char BlinSts)
函数功能: 故障代码显示程序
参    数: ErrorCode：故障代码
返 回 值: 无
-------------------------------------------------------------*/
void DISP_Error(short ErrorCode, char BlinSts)
{
    short Ones = 0;
		short Tens = 0;
    Ones      = (ErrorCode % 10);
    Tens      = (ErrorCode / 10) % 10;
	
		if(!BlinSts)
		{
			DisBuf2[8] = CODE_ALL_OFF;
			DisBuf2[9] = CODE_E;
			DisBuf2[10] = SegCode[Tens];
			DisBuf2[11] = SegCode[Ones];
		}
		else
		{
			DisBuf2[8] = CODE_ALL_OFF;
			DisBuf2[9] = CODE_ALL_OFF;
			DisBuf2[10] = CODE_ALL_OFF;
			DisBuf2[11] = CODE_ALL_OFF;
		}
}

void DispFull(void)
{
		//115V 28V1 28V2 的电压电流
		DISP_A_Volt(8888,POINT);
		DISP_B_Volt(8888,POINT);
		DISP_C_Volt(8888,POINT);
	
		DISP_A_Amp(8888,POINT);
		DISP_B_Amp(8888,POINT);
		DISP_C_Amp(8888,POINT);
	
		DISP_281_Volt(8888,POINT);
		DISP_282_Volt(8888,POINT);
	
		DISP_281_Amp(8888,POINT);
		DISP_282_Amp(8888,POINT);
	
		TM1640_Disp_Update(0,DisBuf);
		TM1640_Disp_Update(1,DisBuf1);
		TM1640_Disp_Update(2,DisBuf2);
}

void DispRunParam(void)
{
		T_REG *s_tReg = 0;
	
		s_tReg = ReadReg();
		//115V 28V1 28V2 的电压电流
		DISP_A_Volt(s_tReg->Ac115VaOutputVoltage/10,POINT);
		DISP_B_Volt(s_tReg->Ac115VbOutputVoltage/10,POINT);
		DISP_C_Volt(s_tReg->Ac115VcOutputVoltage/10,POINT);
	
		DISP_A_Amp(s_tReg->Ac115VaOutputCurrent,POINT);
		DISP_B_Amp(s_tReg->Ac115VbOutputCurrent,POINT);
		DISP_C_Amp(s_tReg->Ac115VcOutputCurrent,POINT);
	
		DISP_281_Volt(s_tReg->Dc28V1OutputVoltage/10,POINT);
		DISP_282_Volt(s_tReg->Dc28V2OutputVoltage/10,POINT);
	
		DISP_281_Amp(s_tReg->Dc28V1OutputCurrent,POINT);
		DISP_282_Amp(s_tReg->Dc28V2OutputCurrent,POINT);
	
//		//故障显示区域
//		
//		
//		//故障码显示
//		err = ReadFirstErrorStatus();
//		if(err>0)
//		{
//			DISP_Error(err, BlinStatus);
//			BlinStatus = ~BlinStatus;
//		
//			int errValue=0;
//			switch(err)
//			{
//				case ERR_CH1_28VDC1_V: 
//					errValue = s_tReg->Dc28V1Ch1OutputVoltage;	
//				break;//0
//				case ERR_CH1_28VDC1_I: 
//					errValue = s_tReg->Dc28V1Ch1OutputCurrent;	
//				break;//1
//				case ERR_CH1_28VDC2_V: 
//					errValue = s_tReg->Dc28V2Ch1OutputVoltage;		
//				break;//2
//				case ERR_CH1_28VDC2_I: 
//					errValue = s_tReg->Dc28V2Ch1OutputCurrent;	
//				break;//3
//				case ERR_CH1_115V_T_V: 
//					errValue = s_tReg->Ac115VaCh1OutputVoltage;	
//				break;//4
//				case ERR_CH1_115V_T_I: 
//					errValue = s_tReg->Ac115VaCh1OutputCurrent;		
//				break;//5
//				case ERR_CH1_115V_S_V: 
//					errValue = s_tReg->Ac115VaCh1OutputVoltage;		
//				break;//6
//				case ERR_CH1_115V_S_I: 
//					errValue = s_tReg->Ac115VaCh1OutputCurrent;		
//				break;//7

//				case ERR_CH2_28VDC1_V: break;//8
//				case ERR_CH2_28VDC1_I: break;//9
//				case ERR_CH2_28VDC2_V: break;//10
//				case ERR_CH2_28VDC2_I: break;//11
//				case ERR_CH2_115V_T_V: break;//12
//				case ERR_CH2_115V_T_I: break;//13
//				case ERR_CH2_115V_S_V: break;//14
//				case ERR_CH2_115V_S_I: break;//15

//				case ERR_CH3_28VDC1_V: break;//16
//				case ERR_CH3_28VDC1_I: break;//17
//				case ERR_CH3_28VDC2_V: break;//18
//				case ERR_CH3_28VDC2_I: break;//19
//				case ERR_CH3_115V_T_V: break;//20
//				case ERR_CH3_115V_T_I: break;//21
//				case ERR_CH3_115V_S_V: break;//22
//				case ERR_CH3_115V_S_I: break;//23

//				case ERR_CH4_28VDC1_V: break;//24
//				case ERR_CH4_28VDC1_I: break;//25
//				case ERR_CH4_28VDC2_V: break;//26
//				case ERR_CH4_28VDC2_I: break;//27
//				case ERR_CH4_115V_T_V: break;//28
//				case ERR_CH4_115V_T_I: break;//29
//				case ERR_CH4_115V_S_V: break;//30
//				case ERR_CH4_115V_S_I: break;//31

//				case ERR_CH5_28VDC1_V: break;//32
//				case ERR_CH5_28VDC1_I: break;//33
//				case ERR_CH5_28VDC2_V: break;//34
//				case ERR_CH5_28VDC2_I: break;//35
//				case ERR_CH5_115V_T_V: break;//36
//				case ERR_CH5_115V_T_I: break;//37
//				case ERR_CH5_115V_S_V: break;//38
//				case ERR_CH5_115V_S_I: break;//39

//				case ERR_CH6_28VDC1_V: break;//40
//				case ERR_CH6_28VDC1_I: break;//41
//				case ERR_CH6_28VDC2_V: break;//42
//				case ERR_CH6_28VDC2_I: break;//43
//				case ERR_CH6_115V_T_V: break;//44
//				case ERR_CH6_115V_T_I: break;//45
//				case ERR_CH6_115V_S_V: break;//46
//				case ERR_CH6_115V_S_I: break;//47
//			}
//			DISP_282_Amp(errValue/10,POINT);
//		}else{
//			CLEAR_Error();
//		}
}

void DispUpdateTask(void)
{
		//初始化一次，为了应对数码管黑屏现象
		//TM1640_IO_Init();
		TM1640_Disp_Init();
		
		//显示电压电流数据
		DispRunParam(); 
		TM1640_Disp_Update(0,DisBuf);
		TM1640_Disp_Update(1,DisBuf1);
		TM1640_Disp_Update(2,DisBuf2);
		
		//更新错误状态
		char err = ReadErrorStatus();
		if(err>0)
		{
			DeviceWorkStatus(DEVICE_WORK_FAULT);
		}
		else
		{
			DeviceWorkStatus(DEVICE_WORK_NORMAL);
		}
}


