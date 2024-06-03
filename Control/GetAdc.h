

#ifndef __GETADC_H
#define __GETADC_H


#include "filter.h"
#include "spi.h"

#define ADC_CHANNEL_NUM	(8)
#define ADC_CHENNEL_VAL_NUM	(11)

#define ZERO_DRIFT	0		//零飘测试

//ADC采集转换到真是值的转换系数---根据实测所得
#if ZERO_DRIFT

//115v根据3中不同源来单独校准
#define AC_115V_OUTV_ALL_380_A_FACTOR			(1)		
#define AC_115V_OUTV_ALL_380_B_FACTOR			(1)
#define AC_115V_OUTV_ALL_380_C_FACTOR			(1)

#define AC_115V_OUTV_ALL_220_A_FACTOR			(1)
#define AC_115V_OUTV_ALL_220_B_FACTOR			(1)
#define AC_115V_OUTV_ALL_220_C_FACTOR			(1)

#define AC_115V_OUTV_ALL_115_A_FACTOR			(1)
#define AC_115V_OUTV_ALL_115_B_FACTOR			(1)
#define AC_115V_OUTV_ALL_115_C_FACTOR			(1)

#define AC_115V_OUTV_ALL_380_A_B	(0)
#define AC_115V_OUTV_ALL_380_B_B	(0)
#define AC_115V_OUTV_ALL_380_C_B	(0)

#define AC_115V_OUTV_ALL_220_A_B	(0)
#define AC_115V_OUTV_ALL_220_B_B	(0)
#define AC_115V_OUTV_ALL_220_C_B	(0)

#define AC_115V_OUTV_ALL_115_A_B	(0)
#define AC_115V_OUTV_ALL_115_B_B	(0)
#define AC_115V_OUTV_ALL_115_C_B	(0)

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

//#define AC_115V_OUTV_ALL_A_FACTOR			(18.527)	//(17.152)
//#define AC_115V_OUTV_ALL_B_FACTOR			(18.468)	//(17.115)
//#define AC_115V_OUTV_ALL_C_FACTOR			(17.968)	//(16.647)

//#define AC_115V_OUTV_ALL_A_B			(-12784+200)	//(-11835+0)
//#define AC_115V_OUTV_ALL_B_B			(-12466+100)	//(-11553+0)
//#define AC_115V_OUTV_ALL_C_B			(-12129+180)	//(-11237+0)

//115v根据3种不同源来单独校准
#define AC_115V_OUTV_ALL_380_A_FACTOR			(32.356)		
#define AC_115V_OUTV_ALL_380_B_FACTOR			(31.306)
#define AC_115V_OUTV_ALL_380_C_FACTOR			(31.592)

#define AC_115V_OUTV_ALL_380_A_B					(-14949)
#define AC_115V_OUTV_ALL_380_B_B					(-14088)
#define AC_115V_OUTV_ALL_380_C_B					(-14596)

#define AC_115V_OUTV_ALL_220_A_FACTOR			(31.971)
#define AC_115V_OUTV_ALL_220_B_FACTOR			(31.111)
#define AC_115V_OUTV_ALL_220_C_FACTOR			(30.964)

#define AC_115V_OUTV_ALL_220_A_B					(-14387)
#define AC_115V_OUTV_ALL_220_B_B					(-13751)
#define AC_115V_OUTV_ALL_220_C_B					(-13872)

#define AC_115V_OUTV_ALL_115_A_FACTOR			(32.034)
#define AC_115V_OUTV_ALL_115_B_FACTOR			(32.000)
#define AC_115V_OUTV_ALL_115_C_FACTOR			(31.634)

#define AC_115V_OUTV_ALL_115_A_B					(-14415)
#define AC_115V_OUTV_ALL_115_B_B					(-14144)
#define AC_115V_OUTV_ALL_115_C_B					(-14172)

#define AC_115V_OUTV_CHANNEL_A_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_B_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_C_FACTOR	(0)
#define AC_115V_OUTV_CHANNEL_A_B			(0)
#define AC_115V_OUTV_CHANNEL_B_B			(0)
#define AC_115V_OUTV_CHANNEL_C_B			(0)

#define AC_115V_OUTI_ALL_A_FACTOR			(0.6892)
#define AC_115V_OUTI_ALL_B_FACTOR			(0.6171)
#define AC_115V_OUTI_ALL_C_FACTOR			(0.6042)

#define AC_115V_OUTI_ALL_A_B					(-10.757+10)
#define AC_115V_OUTI_ALL_B_B					(-13.452+10)
#define AC_115V_OUTI_ALL_C_B					(-13.516+10)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~``
#define AC_115V_OUTI_CH1_A_FACTOR			(0.6688)
#define AC_115V_OUTI_CH1_B_FACTOR			(0.6635)
#define AC_115V_OUTI_CH1_C_FACTOR			(0.6735)

#define AC_115V_OUTI_CH1_A_B					(-11.903)
#define AC_115V_OUTI_CH1_B_B					(-7.6355)
#define AC_115V_OUTI_CH1_C_B					(-6.9398)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~``
#define AC_115V_OUTI_CH2_A_FACTOR			(0.6813)
#define AC_115V_OUTI_CH2_B_FACTOR			(0.6620)
#define AC_115V_OUTI_CH2_C_FACTOR			(0.6655)

#define AC_115V_OUTI_CH2_A_B					(-7.5732)
#define AC_115V_OUTI_CH2_B_B					(-4.3314)
#define AC_115V_OUTI_CH2_C_B					(-7.0154)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH3_A_FACTOR			(0.6804)
#define AC_115V_OUTI_CH3_B_FACTOR			(0.6946)
#define AC_115V_OUTI_CH3_C_FACTOR			(0.7011)

#define AC_115V_OUTI_CH3_A_B					(-15.092)
#define AC_115V_OUTI_CH3_B_B					(-19.474)
#define AC_115V_OUTI_CH3_C_B					(-12.422)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH4_A_FACTOR	(0.6354)
#define AC_115V_OUTI_CH4_B_FACTOR	(0.6853)
#define AC_115V_OUTI_CH4_C_FACTOR	(0.6935)

#define AC_115V_OUTI_CH4_A_B	(-8.9041)
#define AC_115V_OUTI_CH4_B_B	(-25.278)
#define AC_115V_OUTI_CH4_C_B	(-9.0479)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH5_A_FACTOR	(0.5972)
#define AC_115V_OUTI_CH5_B_FACTOR	(0.5991)
#define AC_115V_OUTI_CH5_C_FACTOR	(0.6383)

#define AC_115V_OUTI_CH5_A_B	(-5.584)
#define AC_115V_OUTI_CH5_B_B	(-5.5421)
#define AC_115V_OUTI_CH5_C_B	(-10.063)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AC_115V_OUTI_CH6_A_FACTOR	(0.5931)
#define AC_115V_OUTI_CH6_B_FACTOR	(0.5959)
#define AC_115V_OUTI_CH6_C_FACTOR	(0.6544)

#define AC_115V_OUTI_CH6_A_B	(-1.1417)
#define AC_115V_OUTI_CH6_B_B	(-1.1664)
#define AC_115V_OUTI_CH6_C_B	(-21.815)
//-----------------------------------------------------------------------
#define AC_115V_INV_A_FACTOR	(28.765)
#define AC_115V_INV_B_FACTOR	(27.871)
#define AC_115V_INV_C_FACTOR	(27.938)

#define AC_115V_INV_A_B		(-7766.7)
#define AC_115V_INV_B_B		(-7525.1)
#define AC_115V_INV_C_B		(-7543.2)

#define AC_115V_INI_A_FACTOR	(2.0798)
#define AC_115V_INI_B_FACTOR	(1.8334)
#define AC_115V_INI_C_FACTOR	(1.9690)

#define AC_115V_INI_A_B		(-55.439)
#define AC_115V_INI_B_B		(-35.174)
#define AC_115V_INI_C_B		(-40.993)
//---------------------------------------------------------------------------
#define AC_380V_INV_A_FACTOR	(38.596)
#define AC_380V_INV_B_FACTOR	(38.596)
#define AC_380V_INV_C_FACTOR	(38.596)

#define AC_380V_INV_A_B		(-2701.8)
#define AC_380V_INV_B_B		(-2701.8)
#define AC_380V_INV_C_B		(-2701.8)

#define AC_380V_INI_A_FACTOR	(2.1389)
#define AC_380V_INI_B_FACTOR	(2.1389)
#define AC_380V_INI_C_FACTOR	(2.1150)

#define AC_380V_INI_A_B		(-99.219)
#define AC_380V_INI_B_B		(-99.219)
#define AC_380V_INI_C_B		(-77.385)
//-----------------------------------------------------------------------------
#define AC_220V_INV_FACTOR	(18.917)
#define AC_220V_INV_B		(-14093)

#define AC_220V_INI_FACTOR	(5.4377)
#define AC_220V_INI_B		(216.94)
//---------------------------------------------------------------------------------

//28VDC1 电压系数-K
#define DC_28V1_OUTV_FACTOR			(1.1209)
#define DC_28V1_OUTV_CH1_FACTOR	(1.1359)
#define DC_28V1_OUTV_CH2_FACTOR	(1.1401)
#define DC_28V1_OUTV_CH3_FACTOR	(1.1304)
#define DC_28V1_OUTV_CH4_FACTOR	(1.1401)
#define DC_28V1_OUTV_CH5_FACTOR	(1.1382)
#define DC_28V1_OUTV_CH6_FACTOR	(1.1523)

//28VDC1 电压系数-B
#define DC_28V1_OUTV_B			(-818.25+10)
#define DC_28V1_OUTV_CH1_B	(-829.21)
#define DC_28V1_OUTV_CH2_B	(-832.25)
#define DC_28V1_OUTV_CH3_B	(-833.10)
#define DC_28V1_OUTV_CH4_B	(-828.83)
#define DC_28V1_OUTV_CH5_B	(-819.51)
#define DC_28V1_OUTV_CH6_B	(-845.76)

//28VDC1 电流系数-K
#define DC_28V1_OUTI_ALL_FACTOR	(1.8163)
#define DC_28V1_OUTI_ALL_4_FACTOR	(1.6822)				//~~~~~~~~~~~~~456通道系数
#define DC_28V1_OUTI_ALL_14_FACTOR	(0.9002)			//~~~~~~~~~~~~~~~123456混用通道系数
#define DC_28V1_OUTI_CH1_FACTOR	(1.7504)
#define DC_28V1_OUTI_CH2_FACTOR	(1.7112)
#define DC_28V1_OUTI_CH3_FACTOR	(1.7036)
#define DC_28V1_OUTI_CH4_FACTOR	(1.6893)
#define DC_28V1_OUTI_CH5_FACTOR	(1.6399)
#define DC_28V1_OUTI_CH6_FACTOR	(1.6451)

//28VDC1 电流系数-B
#define DC_28V1_OUTI_B			(-1.9415-3)
#define DC_28V1_OUTI_4_B			(-2.5822)					//~~~~~~~~~~~~~~~456通道系数
#define DC_28V1_OUTI_14_B			(-0.6214)					//~~~~~~~~~~~~~~~123456混用通道系数
#define DC_28V1_OUTI_CH1_B	(-2.6271)
#define DC_28V1_OUTI_CH2_B	(-2.2917)
#define DC_28V1_OUTI_CH3_B	(-0.5417)
#define DC_28V1_OUTI_CH4_B	(-1.2271)
#define DC_28V1_OUTI_CH5_B	(-9.2893)
#define DC_28V1_OUTI_CH6_B	(-4.7800)
//------------------------------------------------------------------//
//28VDC2 电压系数-K
#define DC_28V2_OUTV_FACTOR			(2.2581)
#define DC_28V2_OUTV_CH1_FACTOR	(2.2635)
#define DC_28V2_OUTV_CH2_FACTOR	(2.2581)
#define DC_28V2_OUTV_CH3_FACTOR	(2.2727)
#define DC_28V2_OUTV_CH4_FACTOR	(2.2838)
#define DC_28V2_OUTV_CH5_FACTOR	(2.2581)
#define DC_28V2_OUTV_CH6_FACTOR	(2.2709)

//28VDC2 电压系数-B
#define DC_28V2_OUTV_B			(-812.90+4)
#define DC_28V2_OUTV_CH1_B	(-814.87)
#define DC_28V2_OUTV_CH2_B	(-812.90)
#define DC_28V2_OUTV_CH3_B	(-809.09)
#define DC_28V2_OUTV_CH4_B	(-803.92)
#define DC_28V2_OUTV_CH5_B	(-812.90)
#define DC_28V2_OUTV_CH6_B	(-833.41)

//28VDC2 电流系数-K
#define DC_28V2_OUTI_ALL_FACTOR	(1.3180)
#define DC_28V2_OUTI_ALL_4_FACTOR	(1.5545)				//~~~~~~~~~~~~~456通道系数
#define DC_28V2_OUTI_ALL_14_FACTOR	(0.9002)			//~~~~~~~~~~~~~~~123456混用通道系数
#define DC_28V2_OUTI_CH1_FACTOR	(1.4864)
#define DC_28V2_OUTI_CH2_FACTOR	(1.4202)
#define DC_28V2_OUTI_CH3_FACTOR	(1.3964)
#define DC_28V2_OUTI_CH4_FACTOR	(1.3990)
#define DC_28V2_OUTI_CH5_FACTOR	(1.3834)
#define DC_28V2_OUTI_CH6_FACTOR	(1.3803)

//28VDC2 电流系数-B
#define DC_28V2_OUTI_B			(3.7234-8)
#define DC_28V2_OUTI_4_B			(-3.2884)					//~~~~~~~~~~~~~~~456通道系数
#define DC_28V2_OUTI_14_B			(-0.6214)					//~~~~~~~~~~~~~~~123456混用通道系数
#define DC_28V2_OUTI_CH1_B	(3.4052)
#define DC_28V2_OUTI_CH2_B	(3.4494)
#define DC_28V2_OUTI_CH3_B	(1.3625)
#define DC_28V2_OUTI_CH4_B	(-3.3496)
#define DC_28V2_OUTI_CH5_B	(-9.1781)
#define DC_28V2_OUTI_CH6_B	(-7.3577)
//------------------------------------------------------------------------
//28VDC3
#define DC_28V3_OUTV_FACTOR	(2.7211)
#define DC_28V3_OUTV_B			(-1523.80)

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

#define AC115I_OUT_ZERO_DRIFT_A	0
#define AC115I_OUT_ZERO_DRIFT_B	0
#define AC115I_OUT_ZERO_DRIFT_C	0

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
#define AC380U_ZERO_DRIFT_A			500
#define AC380U_ZERO_DRIFT_B			500
#define AC380U_ZERO_DRIFT_C			500

#define AC115U_IN_ZERO_DRIFT_A	500
#define AC115U_IN_ZERO_DRIFT_B	500
#define AC115U_IN_ZERO_DRIFT_C	500

#define AC115U_OUT_ZERO_DRIFT_A	500
#define AC115U_OUT_ZERO_DRIFT_B	500
#define AC115U_OUT_ZERO_DRIFT_C	500

#define AC115I_OUT_ZERO_DRIFT_A	68
#define AC115I_OUT_ZERO_DRIFT_B	68
#define AC115I_OUT_ZERO_DRIFT_C	68

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
