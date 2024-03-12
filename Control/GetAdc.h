

#ifndef __GETADC_H
#define __GETADC_H


#include "filter.h"
#include "spi.h"

#define ADC_CHANNEL_NUM	(8)
#define ADC_CHENNEL_VAL_NUM	(11)

//ADC采集转换到真是值的转换系数---根据实测所得
#if 0
#define AC_115V_OUTV_ALL_FACTOR			(10.598)
#define AC_115V_OUTV_CHANNEL_FACTOR	(11.698)
#define AC_115V_OUTI_ALL_FACTOR			(0.7895)
#define AC_115V_OUTI_CHANNEL_FACTOR	(0.8012)

#define AC_115V_INV_FACTOR	(7.81)
#define AC_115V_INI_FACTOR	(1)
#define AC_380V_INV_FACTOR	(27.11)
#define AC_380V_INI_FACTOR	(1)
#define AC_220V_INV_FACTOR	(16.5)
#define AC_220V_INI_FACTOR	(1)

#define DC_28V1_OUTV_FACTOR	(0.88)
#define DC_28V1_OUTI_FACTOR	(0.96)
#define DC_28V2_OUTV_FACTOR	(0.88)
#define DC_28V2_OUTI_FACTOR	(0.96)
#define DC_28V3_OUTV_FACTOR	(0.88)
#define DC_28V3_OUTI_FACTOR	(0.96)

#define AC_115V_OUTV_ALL_B			(-2260)
#define AC_115V_OUTV_CHANNEL_A_B	(-4007)
#define AC_115V_OUTV_CHANNEL_B_B	(-4007)
#define AC_115V_OUTV_CHANNEL_C_B	(-4007)
#define AC_115V_OUTI_ALL_B			(91)
#define AC_115V_OUTI_CHANNEL_A_B	(132)
#define AC_115V_OUTI_CHANNEL_B_B	(132)
#define AC_115V_OUTI_CHANNEL_C_B	(132)

#define AC_115V_INV_B		(0)
#define AC_115V_INI_B		(0)
#define AC_380V_INV_B		(-900)
#define AC_380V_INI_B		(0)
#define AC_220V_INV_B		(-1190)
#define AC_220V_INI_B		(0)

#define DC_28V1_OUTV_B	(-797)
#define DC_28V1_OUTI_B	(72)
#define DC_28V1_OUTV_CHANNEL_B	(20)
#define DC_28V1_OUTI_CHANNEL_B	(72)
#define DC_28V2_OUTV_B	(20)
#define DC_28V2_OUTI_B	(72)
#define DC_28V2_OUTV_CHANNEL_B	(20)
#define DC_28V2_OUTI_CHANNEL_B	(72)
#define DC_28V3_OUTV_B	(80)
#define DC_28V3_OUTI_B	(72)

#define AC_115V_OUTI_ZERO	(10)
#define AC_115V_OUTU_ZERO	(3000)
#define AC_115V_OUTU_ALL_ZERO	(3800)

#else

#define AC_115V_OUTV_ALL_FACTOR			(1)
#define AC_115V_OUTV_CHANNEL_FACTOR	(1)
#define AC_115V_OUTI_ALL_FACTOR			(1)
#define AC_115V_OUTI_CHANNEL_FACTOR	(1)

#define AC_115V_INV_FACTOR	(1)
#define AC_115V_INI_FACTOR	(1)

#define AC_380V_INV_FACTOR	(5.5)
#define AC_380V_INI_FACTOR	(1)

#define AC_220V_INV_FACTOR	(24)
#define AC_220V_INI_FACTOR	(1)

#define DC_28V1_OUTV_FACTOR	(1)
#define DC_28V1_OUTI_FACTOR	(1)
#define DC_28V2_OUTV_FACTOR	(1)
#define DC_28V2_OUTI_FACTOR	(1)
#define DC_28V3_OUTV_FACTOR	(1)
#define DC_28V3_OUTI_FACTOR	(1)

#define AC_115V_OUTV_ALL_B			(0)
#define AC_115V_OUTV_CHANNEL_A_B	(0)
#define AC_115V_OUTV_CHANNEL_B_B	(0)
#define AC_115V_OUTV_CHANNEL_C_B	(0)
#define AC_115V_OUTI_ALL_B			(0)
#define AC_115V_OUTI_CHANNEL_A_B	(0)
#define AC_115V_OUTI_CHANNEL_B_B	(0)
#define AC_115V_OUTI_CHANNEL_C_B	(0)

#define AC_115V_INV_B		(0)
#define AC_115V_INI_B		(0)

#define AC_380V_INV_B		(833.28)
#define AC_380V_INI_B		(0)

#define AC_220V_INV_B		(-12608)
#define AC_220V_INI_B		(0)

#define DC_28V1_OUTV_B	(0)
#define DC_28V1_OUTI_B	(0)
#define DC_28V1_OUTV_CHANNEL_B	(0)
#define DC_28V1_OUTI_CHANNEL_B	(0)
#define DC_28V2_OUTV_B	(0)
#define DC_28V2_OUTI_B	(0)
#define DC_28V2_OUTV_CHANNEL_B	(0)
#define DC_28V2_OUTI_CHANNEL_B	(0)
#define DC_28V3_OUTV_B	(0)
#define DC_28V3_OUTI_B	(0)

#define AC_115V_OUTI_ZERO	(0)
#define AC_115V_OUTU_ZERO	(0)
#define AC_115V_OUTU_ALL_ZERO	(0)

#endif

typedef struct
{
		/*R*/
		T_LPF_UNIT SelfInspectionStatus;
		
		//T_LPF_UNIT Ac380VaOutputVoltage;		//by bruce
		//T_LPF_UNIT Ac380VbOutputVoltage;
		//T_LPF_UNIT Ac380VcOutputVoltage;
		T_LPF_UNIT Ac380VaInputCurrent;		//by bruce
		T_LPF_UNIT Ac380VbInputCurrent;
		T_LPF_UNIT Ac380VcInputCurrent;
		T_LPF_UNIT Ac220VInputVoltage;
		T_LPF_UNIT Ac220VInputCurrent;
		T_LPF_UNIT Ac115VaInputVoltage;
		T_LPF_UNIT Ac115VbInputVoltage;
		T_LPF_UNIT Ac115VcInputVoltage;
		T_LPF_UNIT Ac115VaInputCurrent;
		T_LPF_UNIT Ac115VbInputCurrent;
		T_LPF_UNIT Ac115VcInputCurrent;
	
		T_LPF_UNIT Ac115VaOutputVoltage;
		T_LPF_UNIT Ac115VbOutputVoltage;
		T_LPF_UNIT Ac115VcOutputVoltage;
		T_LPF_UNIT Ac115VaOutputCurrent;
		T_LPF_UNIT Ac115VbOutputCurrent;
		T_LPF_UNIT Ac115VcOutputCurrent;
		T_LPF_UNIT Dc28V1OutputVoltage;
		T_LPF_UNIT Dc28V1OutputCurrent;
		T_LPF_UNIT Dc28V2OutputVoltage;
		T_LPF_UNIT Dc28V2OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch1OutputVoltage;
		T_LPF_UNIT Dc28V1Ch1OutputCurrent;
		T_LPF_UNIT Dc28V2Ch1OutputVoltage;
		T_LPF_UNIT Dc28V2Ch1OutputCurrent;
		T_LPF_UNIT Ac115VaCh1OutputVoltage;
		T_LPF_UNIT Ac115VbCh1OutputVoltage;
		T_LPF_UNIT Ac115VcCh1OutputVoltage;
		T_LPF_UNIT Ac115VaCh1OutputCurrent;
		T_LPF_UNIT Ac115VbCh1OutputCurrent;
		T_LPF_UNIT Ac115VcCh1OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch2OutputVoltage;
		T_LPF_UNIT Dc28V1Ch2OutputCurrent;
		T_LPF_UNIT Dc28V2Ch2OutputVoltage;
		T_LPF_UNIT Dc28V2Ch2OutputCurrent;
		T_LPF_UNIT Ac115VaCh2OutputVoltage;
		T_LPF_UNIT Ac115VbCh2OutputVoltage;
		T_LPF_UNIT Ac115VcCh2OutputVoltage;
		T_LPF_UNIT Ac115VaCh2OutputCurrent;
		T_LPF_UNIT Ac115VbCh2OutputCurrent;
		T_LPF_UNIT Ac115VcCh2OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch3OutputVoltage;
		T_LPF_UNIT Dc28V1Ch3OutputCurrent;
		T_LPF_UNIT Dc28V2Ch3OutputVoltage;
		T_LPF_UNIT Dc28V2Ch3OutputCurrent;
		T_LPF_UNIT Ac115VaCh3OutputVoltage;
		T_LPF_UNIT Ac115VbCh3OutputVoltage;
		T_LPF_UNIT Ac115VcCh3OutputVoltage;
		T_LPF_UNIT Ac115VaCh3OutputCurrent;
		T_LPF_UNIT Ac115VbCh3OutputCurrent;
		T_LPF_UNIT Ac115VcCh3OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch4OutputVoltage;
		T_LPF_UNIT Dc28V1Ch4OutputCurrent;
		T_LPF_UNIT Dc28V2Ch4OutputVoltage;
		T_LPF_UNIT Dc28V2Ch4OutputCurrent;
		T_LPF_UNIT Ac115VaCh4OutputVoltage;
		T_LPF_UNIT Ac115VbCh4OutputVoltage;
		T_LPF_UNIT Ac115VcCh4OutputVoltage;
		T_LPF_UNIT Ac115VaCh4OutputCurrent;
		T_LPF_UNIT Ac115VbCh4OutputCurrent;
		T_LPF_UNIT Ac115VcCh4OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch5OutputVoltage;
		T_LPF_UNIT Dc28V1Ch5OutputCurrent;
		T_LPF_UNIT Dc28V2Ch5OutputVoltage;
		T_LPF_UNIT Dc28V2Ch5OutputCurrent;
		T_LPF_UNIT Ac115VaCh5OutputVoltage;
		T_LPF_UNIT Ac115VbCh5OutputVoltage;
		T_LPF_UNIT Ac115VcCh5OutputVoltage;
		T_LPF_UNIT Ac115VaCh5OutputCurrent;
		T_LPF_UNIT Ac115VbCh5OutputCurrent;
		T_LPF_UNIT Ac115VcCh5OutputCurrent;
		
		T_LPF_UNIT Dc28V1Ch6OutputVoltage;
		T_LPF_UNIT Dc28V1Ch6OutputCurrent;
		T_LPF_UNIT Dc28V2Ch6OutputVoltage;
		T_LPF_UNIT Dc28V2Ch6OutputCurrent;
		T_LPF_UNIT Ac115VaCh6OutputVoltage;
		T_LPF_UNIT Ac115VbCh6OutputVoltage;
		T_LPF_UNIT Ac115VcCh6OutputVoltage;
		T_LPF_UNIT Ac115VaCh6OutputCurrent;
		T_LPF_UNIT Ac115VbCh6OutputCurrent;
		T_LPF_UNIT Ac115VcCh6OutputCurrent;
		
		T_LPF_UNIT Dc28V3OutputVoltage;
		T_LPF_UNIT Dc28V3OutputCurrent;
		T_LPF_UNIT Discrete5Voltage;
		T_LPF_UNIT Com1553B5Voltage;
}T_FILTER_UNIT;

unsigned int GetChannelID(void);
void HC4051_Switch_do(int channel);
void HC4051_Switch(void);
void Lpf_Init(void);
int Lpf_Run(int channel, T_SPI_DATA value, T_SPI_DATA* filterData);
/**
	**	??????ADC???modbus?????
	**	@par channel ADC??
	**	@par tSpiData	??????
	*/
void UpdateAdcData(void);

#endif   /*__ERRORCONTROL_H_*/
