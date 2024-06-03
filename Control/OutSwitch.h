

#ifndef __OUTSWITCH_H
#define __OUTSWITCH_H

#include "DataComm.h"
#include "Pinout.h"

void HC245_Set(void);

/**
	*	ֱ��/������Դ����
	*
	*/
void HC245_Power_Switch_Config(void);
/**
	* ֱ����Դ����
	*	
	*	@par value ����ֵ--��λ
	*/
void HC245_DC_Switch_Config(int value);

/**
	* ������Դ����
	*	
	*	@par value ����ֵ--��λ
	*/
void HC245_AC_Switch_Config(int value);

/**
	**	���ݲɼ�����ADC���ݣ�˲ʱֵ���ȶ�ֵ(�˲�ֵ)�����жϣ����п��صĲ���
	*/
void CheckAdcData(void);
void CheckAdcDataBak(void);

#endif   /*__OUTSWITCH_H_*/
