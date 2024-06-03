

#ifndef __OUTSWITCH_H
#define __OUTSWITCH_H

#include "DataComm.h"
#include "Pinout.h"

void HC245_Set(void);

/**
	*	直流/交流电源控制
	*
	*/
void HC245_Power_Switch_Config(void);
/**
	* 直流电源控制
	*	
	*	@par value 控制值--按位
	*/
void HC245_DC_Switch_Config(int value);

/**
	* 交流电源控制
	*	
	*	@par value 控制值--按位
	*/
void HC245_AC_Switch_Config(int value);

/**
	**	根据采集到的ADC数据（瞬时值，稳定值(滤波值)）来判断，进行开关的操作
	*/
void CheckAdcData(void);
void CheckAdcDataBak(void);

#endif   /*__OUTSWITCH_H_*/
