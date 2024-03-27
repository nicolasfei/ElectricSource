

#ifndef __GETADC_H
#define __GETADC_H


#include "filter.h"
#include "spi.h"

#define ADC_CHANNEL_NUM	(8)
#define ADC_CHENNEL_VAL_NUM	(11)

#define ZERO_DRIFT	0		//零飘测试

//ADC采集转换到真是值的转换系数---根据实测所得
#if ZERO_DRIFT

#define AC_115V_OUTV_ALL_A_FACTOR			(1)
#define AC_115V_OUTV_ALL_B_FACTOR			(1)
#define AC_115V_OUTV_ALL_C_FACTOR			(1)

#define AC_115V_OUTV_CHANNEL_A_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_B_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_C_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_A_B			(0)
#define AC_115V_OUTV_CHANNEL_B_B			(0)
#define AC_115V_OUTV_CHANNEL_C_B			(0)

#define AC_115V_OUTI_ALL_A_FACTOR	(1)
#define AC_115V_OUTI_ALL_B_FACTOR	(1)
#define AC_115V_OUTI_ALL_C_FACTOR	(1)

#define AC_115V_OUTI_CH1_A_FACTOR	(1)
#define AC_115V_OUTI_CH1_B_FACTOR	(1)
#define AC_115V_OUTI_CH1_C_FACTOR	(1)

#define AC_115V_OUTI_CH2_A_FACTOR	(1)
#define AC_115V_OUTI_CH2_B_FACTOR	(1)
#define AC_115V_OUTI_CH2_C_FACTOR	(1)

#define AC_115V_OUTI_CH3_A_FACTOR	(1)
#define AC_115V_OUTI_CH3_B_FACTOR	(1)
#define AC_115V_OUTI_CH3_C_FACTOR	(1)

#define AC_115V_OUTI_CH4_A_FACTOR	(1)
#define AC_115V_OUTI_CH4_B_FACTOR	(1)
#define AC_115V_OUTI_CH4_C_FACTOR	(1)

#define AC_115V_OUTI_CH5_A_FACTOR	(1)
#define AC_115V_OUTI_CH5_B_FACTOR	(1)
#define AC_115V_OUTI_CH5_C_FACTOR	(1)

#define AC_115V_OUTI_CH6_A_FACTOR	(1)
#define AC_115V_OUTI_CH6_B_FACTOR	(1)
#define AC_115V_OUTI_CH6_C_FACTOR	(1)

#define AC_115V_INV_A_FACTOR	(1)
#define AC_115V_INV_B_FACTOR	(1)
#define AC_115V_INV_C_FACTOR	(1)

#define AC_115V_INI_A_FACTOR	(1)
#define AC_115V_INI_B_FACTOR	(1)
#define AC_115V_INI_C_FACTOR	(1)

#define AC_380V_INV_A_FACTOR	(1)
#define AC_380V_INV_B_FACTOR	(1)
#define AC_380V_INV_C_FACTOR	(1)
#define AC_380V_INI_A_FACTOR	(1)
#define AC_380V_INI_B_FACTOR	(1)
#define AC_380V_INI_C_FACTOR	(1)

#define AC_220V_INV_FACTOR		(1)
#define AC_220V_INI_FACTOR		(1)

//28VDC1 电压系数-K             
#define DC_28V1_OUTV_FACTOR			(1)
#define DC_28V1_OUTV_CH1_FACTOR	(1)
#define DC_28V1_OUTV_CH2_FACTOR	(1)
#define DC_28V1_OUTV_CH3_FACTOR	(1)
#define DC_28V1_OUTV_CH4_FACTOR	(1)
#define DC_28V1_OUTV_CH5_FACTOR	(1)
#define DC_28V1_OUTV_CH6_FACTOR	(1)

//28VDC2 电压系数-K      
#define DC_28V2_OUTV_FACTOR			(1)
#define DC_28V2_OUTV_CH1_FACTOR	(1)
#define DC_28V2_OUTV_CH2_FACTOR	(1)
#define DC_28V2_OUTV_CH3_FACTOR	(1)
#define DC_28V2_OUTV_CH4_FACTOR	(1)
#define DC_28V2_OUTV_CH5_FACTOR	(1)
#define DC_28V2_OUTV_CH6_FACTOR	(1)

//28VDC1 电流系数-K             
#define DC_28V1_OUTI_ALL_FACTOR	(1)
#define DC_28V1_OUTI_CH1_FACTOR	(1)
#define DC_28V1_OUTI_CH2_FACTOR	(1)
#define DC_28V1_OUTI_CH3_FACTOR	(1)
#define DC_28V1_OUTI_CH4_FACTOR	(1)
#define DC_28V1_OUTI_CH5_FACTOR	(1)
#define DC_28V1_OUTI_CH6_FACTOR	(1)

//28VDC1 电流系数-B
#define DC_28V1_OUTI_B				(0)
#define DC_28V1_OUTI_CH1_B		(0)
#define DC_28V1_OUTI_CH2_B		(0)
#define DC_28V1_OUTI_CH3_B		(0)
#define DC_28V1_OUTI_CH4_B		(0)
#define DC_28V1_OUTI_CH5_B		(0)
#define DC_28V1_OUTI_CH6_B		(0)

//28VDC2 电流系数-K
#define DC_28V2_OUTI_ALL_FACTOR	(1)
#define DC_28V2_OUTI_CH1_FACTOR	(1)
#define DC_28V2_OUTI_CH2_FACTOR	(1)
#define DC_28V2_OUTI_CH3_FACTOR	(1)
#define DC_28V2_OUTI_CH4_FACTOR	(1)
#define DC_28V2_OUTI_CH5_FACTOR	(1)
#define DC_28V2_OUTI_CH6_FACTOR	(1)

//28VDC2 电流系数-B
#define DC_28V2_OUTI_B				(0)
#define DC_28V2_OUTI_CH1_B		(0)
#define DC_28V2_OUTI_CH2_B		(0)
#define DC_28V2_OUTI_CH3_B		(0)
#define DC_28V2_OUTI_CH4_B		(0)
#define DC_28V2_OUTI_CH5_B		(0)
#define DC_28V2_OUTI_CH6_B		(0)

//28VDC3
#define DC_28V3_OUTV_FACTOR		(1)
#define DC_28V3_OUTI_FACTOR		(1)
#define DC_28V3_OUTV_B				(0)
#define DC_28V3_OUTI_B				(0)

//FAN
#define DC_FAN_I_FACTOR				(1)
#define DC_FAN_I_B						(0)

#define AC_115V_OUTV_ALL_A_B	(0)
#define AC_115V_OUTV_ALL_B_B	(0)
#define AC_115V_OUTV_ALL_C_B	(0)

#define AC_115V_OUTI_ALL_A_B	(0)
#define AC_115V_OUTI_ALL_B_B	(0)
#define AC_115V_OUTI_ALL_C_B	(0)

#define AC_115V_OUTI_CH1_A_B	(0)
#define AC_115V_OUTI_CH1_B_B	(0)
#define AC_115V_OUTI_CH1_C_B	(0)

#define AC_115V_OUTI_CH2_A_B	(0)
#define AC_115V_OUTI_CH2_B_B	(0)
#define AC_115V_OUTI_CH2_C_B	(0)

#define AC_115V_OUTI_CH3_A_B	(0)
#define AC_115V_OUTI_CH3_B_B	(0)
#define AC_115V_OUTI_CH3_C_B	(0)

#define AC_115V_OUTI_CH4_A_B	(0)
#define AC_115V_OUTI_CH4_B_B	(0)
#define AC_115V_OUTI_CH4_C_B	(0)

#define AC_115V_OUTI_CH5_A_B	(0)
#define AC_115V_OUTI_CH5_B_B	(0)
#define AC_115V_OUTI_CH5_C_B	(0)

#define AC_115V_OUTI_CH6_A_B	(0)
#define AC_115V_OUTI_CH6_B_B	(0)
#define AC_115V_OUTI_CH6_C_B	(0)

#define AC_115V_INV_A_B		(0)
#define AC_115V_INV_B_B		(0)
#define AC_115V_INV_C_B		(0)

#define AC_115V_INI_A_B		(0)
#define AC_115V_INI_B_B		(0)
#define AC_115V_INI_C_B		(0)

#define AC_380V_INV_A_B		(0)
#define AC_380V_INV_B_B		(0)
#define AC_380V_INV_C_B		(0)
#define AC_380V_INI_A_B		(0)
#define AC_380V_INI_B_B		(0)
#define AC_380V_INI_C_B		(0)

#define AC_220V_INV_B			(0)
#define AC_220V_INI_B			(0)

//28VDC1 电压系数-B          
#define DC_28V1_OUTV_B			(0)
#define DC_28V1_OUTV_CH1_B	(0)
#define DC_28V1_OUTV_CH2_B	(0)
#define DC_28V1_OUTV_CH3_B	(0)
#define DC_28V1_OUTV_CH4_B	(0)
#define DC_28V1_OUTV_CH5_B	(0)
#define DC_28V1_OUTV_CH6_B	(0)

//28VDC1 电压系数-B          
#define DC_28V2_OUTV_B			(0)
#define DC_28V2_OUTV_CH1_B	(0)
#define DC_28V2_OUTV_CH2_B	(0)
#define DC_28V2_OUTV_CH3_B	(0)
#define DC_28V2_OUTV_CH4_B	(0)
#define DC_28V2_OUTV_CH5_B	(0)
#define DC_28V2_OUTV_CH6_B	(0)


#else

#define AC_115V_OUTV_ALL_A_FACTOR			(18.527)	//(17.152)
#define AC_115V_OUTV_ALL_B_FACTOR			(18.468)	//(17.115)
#define AC_115V_OUTV_ALL_C_FACTOR			(17.968)	//(16.647)

#define AC_115V_OUTV_ALL_A_B	(-12784)	//(-11835+0)
#define AC_115V_OUTV_ALL_B_B	(-12466)	//(-11553+0)
#define AC_115V_OUTV_ALL_C_B	(-12129)	//(-11237+0)

#define AC_115V_OUTV_CHANNEL_A_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_B_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_C_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_A_B		(0)
#define AC_115V_OUTV_CHANNEL_B_B		(0)
#define AC_115V_OUTV_CHANNEL_C_B		(0)

#define AC_115V_OUTI_ALL_A_FACTOR		(1.2352)
#define AC_115V_OUTI_ALL_B_FACTOR		(1.1029)
#define AC_115V_OUTI_ALL_C_FACTOR		(1.0782)

#define AC_115V_OUTI_ALL_A_B	(-200.1)
#define AC_115V_OUTI_ALL_B_B	(-181.99)
#define AC_115V_OUTI_ALL_C_B	(-180.06)

#define AC_115V_OUTI_CH1_A_FACTOR	(1.1207)
#define AC_115V_OUTI_CH1_B_FACTOR	(1.1451)
#define AC_115V_OUTI_CH1_C_FACTOR	(1.1534)

#define AC_115V_OUTI_CH1_A_B	(-135.6)
#define AC_115V_OUTI_CH1_B_B	(-139.7)
#define AC_115V_OUTI_CH1_C_B	(-147.63)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~``
#define AC_115V_OUTI_CH2_A_FACTOR	(1.2165)
#define AC_115V_OUTI_CH2_B_FACTOR	(1.2397)
#define AC_115V_OUTI_CH2_C_FACTOR	(1.2177)

#define AC_115V_OUTI_CH2_A_B	(-200.71)
#define AC_115V_OUTI_CH2_B_B	(-195.87)
#define AC_115V_OUTI_CH2_C_B	(-192.39)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH3_A_FACTOR	(1.0754)
#define AC_115V_OUTI_CH3_B_FACTOR	(1.1033)
#define AC_115V_OUTI_CH3_C_FACTOR	(1.1404)

#define AC_115V_OUTI_CH3_A_B	(-131.2)
#define AC_115V_OUTI_CH3_B_B	(-133.5)
#define AC_115V_OUTI_CH3_C_B	(-147.11)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH4_A_FACTOR	(1.114)
#define AC_115V_OUTI_CH4_B_FACTOR	(1.122)
#define AC_115V_OUTI_CH4_C_FACTOR	(1.167)

#define AC_115V_OUTI_CH4_A_B	(-142.59)
#define AC_115V_OUTI_CH4_B_B	(-135.76)
#define AC_115V_OUTI_CH4_C_B	(-141.21)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH5_A_FACTOR	(1.1036)
#define AC_115V_OUTI_CH5_B_FACTOR	(1.1509)
#define AC_115V_OUTI_CH5_C_FACTOR	(1.1761)

#define AC_115V_OUTI_CH5_A_B	(-135.74)
#define AC_115V_OUTI_CH5_B_B	(-139.26)
#define AC_115V_OUTI_CH5_C_B	(-134.08)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH6_A_FACTOR	(1.0646)
#define AC_115V_OUTI_CH6_B_FACTOR	(1.2418)
#define AC_115V_OUTI_CH6_C_FACTOR	(1.1144)

#define AC_115V_OUTI_CH6_A_B	(-123.5)
#define AC_115V_OUTI_CH6_B_B	(-144.05)
#define AC_115V_OUTI_CH6_C_B	(-129.28)
//-----------------------------------------------------------------------
#define AC_115V_INV_A_FACTOR	(13.099)
#define AC_115V_INV_B_FACTOR	(15.441)
#define AC_115V_INV_C_FACTOR	(23.944)

#define AC_115V_INV_A_B		(-7529)
#define AC_115V_INV_B_B		(-11780)
#define AC_115V_INV_C_B		(-24055)

#define AC_115V_INI_A_FACTOR	(1.136)
#define AC_115V_INI_B_FACTOR	(1.0415)
#define AC_115V_INI_C_FACTOR	(1.046)

#define AC_115V_INI_A_B		(-284.88)
#define AC_115V_INI_B_B		(-198.80)
#define AC_115V_INI_C_B		(-199.34)
//---------------------------------------------------------------------------
#define AC_380V_INV_A_FACTOR	(91.00)
#define AC_380V_INV_B_FACTOR	(95.909)
#define AC_380V_INV_C_FACTOR	(168.18)
#define AC_380V_INI_A_FACTOR	(1.0949)
#define AC_380V_INI_B_FACTOR	(0.8905)
#define AC_380V_INI_C_FACTOR	(1.4177)

#define AC_380V_INV_A_B		(-110654)
#define AC_380V_INV_B_B		(-119400)
#define AC_380V_INV_C_B		(-228485)
#define AC_380V_INI_A_B		(-64.662)
#define AC_380V_INI_B_B		(-78.012)
#define AC_380V_INI_C_B		(-90.717)
//-----------------------------------------------------------------------------
#define AC_220V_INV_FACTOR	(18.734)
#define AC_220V_INV_B		(-10761+4400)

#define AC_220V_INI_FACTOR	(2.8565)
#define AC_220V_INI_B		(439.89)
//---------------------------------------------------------------------------------

//28VDC1 电压系数-K
#define DC_28V1_OUTV_FACTOR			(1.4562)
#define DC_28V1_OUTV_CH1_FACTOR	(1.5192)
#define DC_28V1_OUTV_CH2_FACTOR	(1.5197)
#define DC_28V1_OUTV_CH3_FACTOR	(1.5202)
#define DC_28V1_OUTV_CH4_FACTOR	(1.5238)
#define DC_28V1_OUTV_CH5_FACTOR	(1.5213)
#define DC_28V1_OUTV_CH6_FACTOR	(1.5280)

//28VDC1 电压系数-B
#define DC_28V1_OUTV_B			(-722.71-10)
#define DC_28V1_OUTV_CH1_B	(-859.60-70)
#define DC_28V1_OUTV_CH2_B	(-858.16-70)
#define DC_28V1_OUTV_CH3_B	(-866.00-70)
#define DC_28V1_OUTV_CH4_B	(-858.78-70)
#define DC_28V1_OUTV_CH5_B	(-849.89-70)
#define DC_28V1_OUTV_CH6_B	(-867.24-70)

//28VDC1 电流系数-K
#define DC_28V1_OUTI_ALL_FACTOR	(1.4409)
#define DC_28V1_OUTI_CH1_FACTOR	(10)
#define DC_28V1_OUTI_CH2_FACTOR	(6.7335)
#define DC_28V1_OUTI_CH3_FACTOR	(12.046)
#define DC_28V1_OUTI_CH4_FACTOR	(8.903)
#define DC_28V1_OUTI_CH5_FACTOR	(9.8874)
#define DC_28V1_OUTI_CH6_FACTOR	(12.63)

//28VDC1 电流系数-B
#define DC_28V1_OUTI_B			(-968.81)
#define DC_28V1_OUTI_CH1_B	(-7270)
#define DC_28V1_OUTI_CH2_B	(-4557.6)
#define DC_28V1_OUTI_CH3_B	(-8526.4)
#define DC_28V1_OUTI_CH4_B	(-6108.1)
#define DC_28V1_OUTI_CH5_B	(-6862.3)
#define DC_28V1_OUTI_CH6_B	(-8775.6)
//------------------------------------------------------------------//
//28VDC2 电压系数-K
#define DC_28V2_OUTV_FACTOR			(1.5573)
#define DC_28V2_OUTV_CH1_FACTOR	(1.5951)
#define DC_28V2_OUTV_CH2_FACTOR	(1.5882)
#define DC_28V2_OUTV_CH3_FACTOR	(1.5957)
#define DC_28V2_OUTV_CH4_FACTOR	(1.5704)
#define DC_28V2_OUTV_CH5_FACTOR	(1.5682)
#define DC_28V2_OUTV_CH6_FACTOR	(1.5709)

//28VDC2 电压系数-B
#define DC_28V2_OUTV_B			(-1041.30-20)
#define DC_28V2_OUTV_CH1_B	(-1116.60-10)
#define DC_28V2_OUTV_CH2_B	(-1119.60-10)
#define DC_28V2_OUTV_CH3_B	(-1109.00-10)
#define DC_28V2_OUTV_CH4_B	(-1043.90-10)
#define DC_28V2_OUTV_CH5_B	(-1059.60-10)
#define DC_28V2_OUTV_CH6_B	(-1081.70-10)

//28VDC2 电流系数-K
#define DC_28V2_OUTI_ALL_FACTOR	(1.073)
#define DC_28V2_OUTI_CH1_FACTOR	(5.7577)
#define DC_28V2_OUTI_CH2_FACTOR	(4.024)
#define DC_28V2_OUTI_CH3_FACTOR	(6.0595)
#define DC_28V2_OUTI_CH4_FACTOR	(6.0921)
#define DC_28V2_OUTI_CH5_FACTOR	(6.1521)
#define DC_28V2_OUTI_CH6_FACTOR	(7.2403)

//28VDC2 电流系数-B
#define DC_28V2_OUTI_B			(-1243.20)
#define DC_28V2_OUTI_CH1_B	(-6355.2)
#define DC_28V2_OUTI_CH2_B	(-4226.6)
#define DC_28V2_OUTI_CH3_B	(-6810.8)
#define DC_28V2_OUTI_CH4_B	(-7073.3)
#define DC_28V2_OUTI_CH5_B	(-7036.3)
#define DC_28V2_OUTI_CH6_B	(-8194.2)
//------------------------------------------------------------------------
//28VDC3
#define DC_28V3_OUTV_FACTOR	(1.5347)
#define DC_28V3_OUTV_B			(-974.58)

#define DC_28V3_OUTI_FACTOR	(0.5556)
#define DC_28V3_OUTI_B			(-626.11)

//FAN
#define DC_FAN_I_FACTOR			(0.6142)
#define DC_FAN_I_B					(-692.87)
//------------------------------------------------------------------------------

#endif

#if ZERO_DRIFT

//交流零飘
#define AC380U_ZERO_DRIFT_A			0
#define AC380U_ZERO_DRIFT_B			0
#define AC380U_ZERO_DRIFT_C			0

#define AC115U_IN_ZERO_DRIFT_A	0
#define AC115U_IN_ZERO_DRIFT_B	0
#define AC115U_IN_ZERO_DRIFT_C	0

#define AC115U_OUT_ZERO_DRIFT_A	0
#define AC115U_OUT_ZERO_DRIFT_B	0
#define AC115U_OUT_ZERO_DRIFT_C	0

#define AC220U_ZERO_DRIFT				0	

//直流零飘
#define DC28V1_ZERO_DRIFT				0
#define DC28V1_CH1_ZERO_DRIFT		0
#define DC28V1_CH2_ZERO_DRIFT		0
#define DC28V1_CH3_ZERO_DRIFT		0
#define DC28V1_CH4_ZERO_DRIFT		0
#define DC28V1_CH5_ZERO_DRIFT		0
#define DC28V1_CH6_ZERO_DRIFT		0

#define DC28V2_ZERO_DRIFT				0
#define DC28V2_CH1_ZERO_DRIFT		0
#define DC28V2_CH2_ZERO_DRIFT		0
#define DC28V2_CH3_ZERO_DRIFT		0
#define DC28V2_CH4_ZERO_DRIFT		0
#define DC28V2_CH5_ZERO_DRIFT		0
#define DC28V2_CH6_ZERO_DRIFT		0

#define DC28V3_ZERO_DRIFT		0

#else

//交流零飘
#define AC380U_ZERO_DRIFT_A			600
#define AC380U_ZERO_DRIFT_B			600
#define AC380U_ZERO_DRIFT_C			600

#define AC115U_IN_ZERO_DRIFT_A	800
#define AC115U_IN_ZERO_DRIFT_B	800
#define AC115U_IN_ZERO_DRIFT_C	800

#define AC115U_OUT_ZERO_DRIFT_A	600
#define AC115U_OUT_ZERO_DRIFT_B	600
#define AC115U_OUT_ZERO_DRIFT_C	600

#define AC220U_ZERO_DRIFT				600

//直流零飘
#define DC28V1_ZERO_DRIFT				750
#define DC28V1_CH1_ZERO_DRIFT		750
#define DC28V1_CH2_ZERO_DRIFT		750
#define DC28V1_CH3_ZERO_DRIFT		750
#define DC28V1_CH4_ZERO_DRIFT		750
#define DC28V1_CH5_ZERO_DRIFT		750
#define DC28V1_CH6_ZERO_DRIFT		750

#define DC28V2_ZERO_DRIFT				800
#define DC28V2_CH1_ZERO_DRIFT		800
#define DC28V2_CH2_ZERO_DRIFT		800
#define DC28V2_CH3_ZERO_DRIFT		800
#define DC28V2_CH4_ZERO_DRIFT		800
#define DC28V2_CH5_ZERO_DRIFT		800
#define DC28V2_CH6_ZERO_DRIFT		800

#define DC28V3_ZERO_DRIFT				600
#endif

typedef struct
{
		/*R*/
		//T_LPF_UNIT SelfInspectionStatus;
		
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
