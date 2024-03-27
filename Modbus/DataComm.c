#include <string.h>
#include "usart.h"
#include "ModbusSlave.h"
#include "DataComm.h"
#include "Pinout.h"

static unsigned char s_cPresetStatus[PRESET_STATUS_NUM] = {0};
static unsigned char s_cFeedbackStatus[FEEDBACK_STATUS_NUM] = {0};

static int s_iHoldReg[HOLD_REG_NUM];
static int s_iInputReg[INPUT_REG_NUM];

static unsigned char s_cOnLineVal = 0;

static T_REG s_tReg = {0};

static int AC_DO_SET=0;
static int DC_DO_SET=0;

void ModbusResponseTask(void)
{
		MODBUS_SLAVE_PARAM tModbusParam;
		
		//寄存器0--88,154--156为只读寄存器, 其他为RW。这里只拷贝R的寄存器
		memcpy(s_iHoldReg,&s_tReg, 92*4);
		memcpy(&s_iHoldReg[154], &s_tReg.Ac380VaOutputVoltage, 3*4);
		memcpy(&s_iHoldReg[158], &s_tReg.FanControlFeedback, 3*4);
		tModbusParam.wUsartPeriph     = USART1;
		tModbusParam.cSlaveId         = SLAVE_ADDR;
	
		tModbusParam.pcRxData         = ReadUsart1RxData();
		tModbusParam.pcRxCnt          = ReadUsart1RxCnt();
		tModbusParam.cRxFrameEndFlag  = CheckUsart1RxFrameEnd();
		
		tModbusParam.pcSlaveOnlineVal = &s_cOnLineVal;
		tModbusParam.pcInputStatus    = s_cFeedbackStatus;
		tModbusParam.pcCoilStatus     = s_cPresetStatus;
		tModbusParam.pwInputReg       = s_iInputReg;
		tModbusParam.pwHoldReg        = s_iHoldReg;
		ModbusSlaveResponse(&tModbusParam);
		
		//寄存器0--88,154--156为只读寄存器, 其他为RW。这里只拷贝RW的寄存器
		memcpy(&(s_tReg.RunMode), &s_iHoldReg[89], 65*4);
		//by bruce 01/27 增加了风机控制寄存器，需要于RunMode联动，RunMode为1时,且FanControlValue>2才有用
		memcpy(&(s_tReg.FanControlValue), &s_iHoldReg[157], 1*4);
}

void SetAcDcDio(int ac, int dc)
{
	AC_DO_SET = ac;
	DC_DO_SET = dc;
}

int GetAcDioSet(void)
{
	return AC_DO_SET;
}

int GetDcDioSet(void)
{
	return DC_DO_SET;
}

T_REG *ReadReg(void)
{
		return &s_tReg;
}

unsigned char* ReadOnLineVal(void)
{
		return &s_cOnLineVal;
}

void ModbusRegInit(void)
{
		s_tReg.RunMode = 1;		//默认为工作模式			by bruce 2024/03/06
		s_tReg.FanControlValue=0;
		//软件版本号赋值
		s_tReg.Version = 100;
}
