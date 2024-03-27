#include "gd32f4xx.h"
#include "OutSwitch.h"
#include "GetAdc.h"
#include "ErrorControl.h"

void HC245_Set(void)
{
		rcu_periph_clock_enable(RCU_GPIOE);//使能PORTE时钟
	
		//配置PE12引脚的模式
		gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_12);//配置为下拉模式
		gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_12);//配置为推挽输出，速度为50M
		
		//配置PE13引脚的模式
		gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_13);//配置为下拉模式
		gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_13);//配置为推挽输出，速度为50M
	
		gpio_bit_set(GPIOE,GPIO_PIN_12);  //DIR
		gpio_bit_reset(GPIOE,GPIO_PIN_13);  //OE
}

/**
	*	直流/交流电源控制
	*
	*/
void HC245_Power_Switch_Config()
{
	T_REG *s_tReg = ReadReg();
	if(s_tReg->RunMode == 1)		//电源适配器工作模式--0000H：空闲 0001H：正常工作        正常模式才可以去操作
	{		
		HC245_DC_Switch_Config(s_tReg->DcPowerControl);
		HC245_AC_Switch_Config(s_tReg->AcPowerControl);
		SetAcDcDio(s_tReg->AcPowerControl,s_tReg->DcPowerControl);
	}
	else		//空闲模式 需要还原之前的状态
	{
		s_tReg->AcPowerControl = GetAcDioSet();
		s_tReg->DcPowerControl = GetDcDioSet();
	}
}

/**
	* 直流电源控制
	*	
	*	@par value 控制值--按位
	*/
void HC245_DC_Switch_Config(int value)
{
	int i=0;
	int mask = 1;
	T_REG *s_tReg = ReadReg();
	
	
	if((value & mask<<i)>0)
		DO_DC1_CH1_ON;
	else
	{
		DO_DC1_CH1_OFF;
		//清空故障码
		ResetErrorCode(ERR_CH1_28VDC1_I);
		ResetErrorCode(ERR_CH1_28VDC1_V);
	}	
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH1_ON;
	else
	{
		DO_DC2_CH1_OFF;
		ResetErrorCode(ERR_CH1_28VDC2_I);
		ResetErrorCode(ERR_CH1_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC1_CH2_ON;
	else
	{
		DO_DC1_CH2_OFF;
		ResetErrorCode(ERR_CH2_28VDC1_I);
		ResetErrorCode(ERR_CH2_28VDC1_V);
	}	
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH2_ON;
	else
	{
		DO_DC2_CH2_OFF;
		ResetErrorCode(ERR_CH2_28VDC2_I);
		ResetErrorCode(ERR_CH2_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC1_CH3_ON;
	else
	{
		DO_DC1_CH3_OFF;
		ResetErrorCode(ERR_CH3_28VDC1_I);
		ResetErrorCode(ERR_CH3_28VDC1_V);
	}	
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH3_ON;
	else
	{
		DO_DC2_CH3_OFF;
		ResetErrorCode(ERR_CH3_28VDC2_I);
		ResetErrorCode(ERR_CH3_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC1_CH4_ON;
	else
	{
		DO_DC1_CH4_OFF;
		ResetErrorCode(ERR_CH4_28VDC1_I);
		ResetErrorCode(ERR_CH4_28VDC1_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH4_ON;
	else
	{
		DO_DC2_CH4_OFF;
		ResetErrorCode(ERR_CH4_28VDC2_I);
		ResetErrorCode(ERR_CH4_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC1_CH5_ON;
	else
	{
		DO_DC1_CH5_OFF;
		ResetErrorCode(ERR_CH5_28VDC1_I);
		ResetErrorCode(ERR_CH5_28VDC1_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH5_ON;
	else
	{
		DO_DC2_CH5_OFF;
		ResetErrorCode(ERR_CH5_28VDC2_I);
		ResetErrorCode(ERR_CH5_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC1_CH6_ON;
	else
	{
		DO_DC1_CH6_OFF;
		ResetErrorCode(ERR_CH6_28VDC1_I);
		ResetErrorCode(ERR_CH6_28VDC1_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC2_CH6_ON;
	else
	{
		DO_DC2_CH6_OFF;
		ResetErrorCode(ERR_CH6_28VDC2_I);
		ResetErrorCode(ERR_CH6_28VDC2_V);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_DC3_ON;                                          
	else
		DO_DC3_OFF;
	i++;
	
	if((value & mask<<i)>0)
		DO_LS1_ON;
	else
		DO_LS1_OFF;
	i++;
	
	if((value & mask<<i)>0)
		DO_LS2_ON;
	else
		DO_LS2_OFF;
	i++;
	
	if((value & mask<<i)>0)
		DO_1553B_ON;
	else
		DO_1553B_OFF;
	i++;
}

/**
	* 交流电源控制
	*	
	*	@par value 控制值--按位
	*/
void HC245_AC_Switch_Config(int value)
{
	int i=0;
	int mask = 1;
	T_REG *s_tReg = ReadReg();
	
	if((value & mask<<i)>0)
		DO_AC_CH1_ON;
	else
	{
		DO_AC_CH1_OFF;
		ResetErrorCode(ERR_CH1_115V_T_V);
		ResetErrorCode(ERR_CH1_115V_T_I);
		ResetErrorCode(ERR_CH1_115V_S_V);
		ResetErrorCode(ERR_CH1_115V_S_I);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_AC_CH2_ON;
	else
	{
		DO_AC_CH2_OFF;
		ResetErrorCode(ERR_CH2_115V_T_V);
		ResetErrorCode(ERR_CH2_115V_T_I);
		ResetErrorCode(ERR_CH2_115V_S_V);
		ResetErrorCode(ERR_CH2_115V_S_I);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_AC_CH3_ON;
	else
	{
		DO_AC_CH3_OFF;
		ResetErrorCode(ERR_CH3_115V_T_V);
		ResetErrorCode(ERR_CH3_115V_T_I);
		ResetErrorCode(ERR_CH3_115V_S_V);
		ResetErrorCode(ERR_CH3_115V_S_I);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_AC_CH4_ON;
	else
	{
		DO_AC_CH4_OFF;
		ResetErrorCode(ERR_CH4_115V_T_V);
		ResetErrorCode(ERR_CH4_115V_T_I);
		ResetErrorCode(ERR_CH4_115V_S_V);
		ResetErrorCode(ERR_CH4_115V_S_I);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_AC_CH5_ON;
	else
	{
		DO_AC_CH5_OFF;
		ResetErrorCode(ERR_CH5_115V_T_V);
		ResetErrorCode(ERR_CH5_115V_T_I);
		ResetErrorCode(ERR_CH5_115V_S_V);
		ResetErrorCode(ERR_CH5_115V_S_I);
	}
	i++;
	
	if((value & mask<<i)>0)
		DO_AC_CH6_ON;
	else
	{
		DO_AC_CH6_OFF;
		ResetErrorCode(ERR_CH6_115V_T_V);
		ResetErrorCode(ERR_CH6_115V_T_I);
		ResetErrorCode(ERR_CH6_115V_S_V);
		ResetErrorCode(ERR_CH6_115V_S_I);
	}
	i++;
}

/**
	**	根据采集到的ADC数据（瞬时值，稳定值(滤波值)）来判断，进行开关的操作
	**	@par channel ADC通道
	**	@par tSpiData	采集到的数据
	**	@par tFilterData	滤波后的数据
	*/
#define TRANSIENT_COUNT_UP	(3)
static int AC_CH1_V_count=0;
static int AC_CH1_I_count=0;
static int AC_CH2_V_count=0;
static int AC_CH2_I_count=0;
static int AC_CH3_V_count=0;
static int AC_CH3_I_count=0;
static int AC_CH4_V_count=0;
static int AC_CH4_I_count=0;
static int AC_CH5_V_count=0;
static int AC_CH5_I_count=0;
static int AC_CH6_V_count=0;
static int AC_CH6_I_count=0;

static int DC1_CH1_V_count=0;
static int DC1_CH1_I_count=0;

static int DC1_CH2_V_count=0;
static int DC1_CH2_I_count=0;

static int DC1_CH3_V_count=0;
static int DC1_CH3_I_count=0;

static int DC1_CH4_V_count=0;
static int DC1_CH4_I_count=0;

static int DC1_CH5_V_count=0;
static int DC1_CH5_I_count=0;

static int DC1_CH6_V_count=0;
static int DC1_CH6_I_count=0;

/*
static int DC2_CH1_V_count=0;
static int DC2_CH1_I_count=0;

static int DC2_CH2_V_count=0;
static int DC2_CH2_I_count=0;

static int DC2_CH3_V_count=0;
static int DC2_CH3_I_count=0;

static int DC2_CH4_V_count=0;
static int DC2_CH4_I_count=0;

static int DC2_CH5_V_count=0;
static int DC2_CH5_I_count=0;

static int DC2_CH6_V_count=0;
static int DC2_CH6_I_count=0;


static int DO_DC3_count=0;
static int DO_1553B_count=0;
static int DO_LS1_count=0;
static int DO_LS2_count=0;
static int DO_LS3_count=0;
static int DO_LS4_count=0;
*/
void CheckAdcData()
{
	T_REG *s_tReg = ReadReg();
	T_ERROR_REG *v_eReg = ReadErrorReg();
	T_SPI_DATA tSpiData = GetSpiSteadyData();//GetSpiTransientData();
	T_SPI_DATA tFilterData = GetSpiSteadyData();
	switch(GetChannelID())
		{
		case 4:
			break;
		case 6:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh1OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh1OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh1OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh1OverVoltageTransientThd)
				{
						AC_CH1_V_count++;
						if(AC_CH1_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH1_OFF;
							SetErrorCode(ERR_CH1_115V_T_V);			//设置故障码
							//设置故障值
							if(tSpiData.Data0 > s_tReg->Ac115VCh1OverVoltageTransientThd){
								v_eReg->Ac115VCh1OverVoltageTransientThd = tSpiData.Data0;
							}else if(tSpiData.Data1 > s_tReg->Ac115VCh1OverVoltageTransientThd){
								v_eReg->Ac115VCh1OverVoltageTransientThd = tSpiData.Data1;
							}else{
								v_eReg->Ac115VCh1OverVoltageTransientThd = tSpiData.Data2;
							}
							AC_CH1_V_count=0;
						}
				}
				else
				{
					AC_CH1_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh1OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh1OverVoltageSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_V);		//设置故障码
					//设置故障值
					if(tFilterData.Data0 > s_tReg->Ac115VCh1OverVoltageSteadyThd){
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data0;
					}else if(tFilterData.Data1 > s_tReg->Ac115VCh1OverVoltageSteadyThd){
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data1;
					}else{
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data2;
					}
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh1OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh1OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh1OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh1OverCurrentTransientThd)
				{
						AC_CH1_I_count++;
						if(AC_CH1_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH1_OFF;
							SetErrorCode(ERR_CH1_115V_T_I);		//设置故障码
							//设置故障值
							if(tSpiData.Data3 > s_tReg->Ac115VCh1OverCurrentTransientThd){
								v_eReg->Ac115VCh1OverCurrentTransientThd = tSpiData.Data3;
							}else if(tSpiData.Data4 > s_tReg->Ac115VCh1OverCurrentTransientThd){
								v_eReg->Ac115VCh1OverCurrentTransientThd = tSpiData.Data4;
							}else{
								v_eReg->Ac115VCh1OverCurrentTransientThd = tSpiData.Data5;
							}
							AC_CH1_I_count=0;
						}
				}
				else
				{
					AC_CH1_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh1OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh1OverCurrentSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_I);		//设置故障码
					//设置故障值
					if(tSpiData.Data3 > s_tReg->Ac115VCh1OverCurrentSteadyThd){
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh1OverCurrentSteadyThd){
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
		
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch1OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch1OverVoltageTransientThd)
				{
						DC1_CH1_V_count++;
						if(DC1_CH1_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH1_OFF;
							SetErrorCode(ERR_CH1_28VDC1_V);		//设置故障码
							//设置故障值
							v_eReg->Dc28V1Ch1OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH1_V_count=0;
						}
				}
				else
				{
					DC1_CH1_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch1OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch1OverCurrentTransientThd)
				{
						DC1_CH1_I_count++;
						if(DC1_CH1_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH1_OFF;
							SetErrorCode(ERR_CH1_28VDC1_I);		//设置故障码
							//设置故障值
							v_eReg->Dc28V1Ch1OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH1_I_count=0;
						}
				}
				else
				{
					DC1_CH1_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch1OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch1OverVoltageSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_V);		//设置故障码
					//设置故障值
					v_eReg->Dc28V2Ch1OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch1OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch1OverCurrentSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_I);		//设置故障码
					//设置故障值
					v_eReg->Dc28V2Ch1OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 7:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh2OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh2OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh2OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh2OverVoltageTransientThd)
				{
						AC_CH2_V_count++;
						if(AC_CH2_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH2_OFF;
							SetErrorCode(ERR_CH2_115V_T_V);		//设置故障码
							//设置故障值
							if(tSpiData.Data0 > s_tReg->Ac115VCh2OverVoltageTransientThd){
								v_eReg->Ac115VCh2OverVoltageTransientThd = tSpiData.Data0;
							}else if(tSpiData.Data1 > s_tReg->Ac115VCh2OverVoltageTransientThd){
								v_eReg->Ac115VCh2OverVoltageTransientThd = tSpiData.Data1;
							}else{
								v_eReg->Ac115VCh2OverVoltageTransientThd = tSpiData.Data2;
							}
							AC_CH2_V_count=0;
						}
				}
				else
				{
					AC_CH2_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh2OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh2OverVoltageSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_V);		//设置故障码
					//设置故障值
					if(tSpiData.Data0 > s_tReg->Ac115VCh2OverVoltageSteadyThd){
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data0;
					}else if(tSpiData.Data1 > s_tReg->Ac115VCh2OverVoltageSteadyThd){
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data1;
					}else{
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data2;
					}
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh2OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh2OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh2OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh2OverCurrentTransientThd)
				{
						AC_CH2_I_count++;
						if(AC_CH2_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH2_OFF;
							SetErrorCode(ERR_CH2_115V_T_I);		//设置故障码
							//设置故障值
							if(tSpiData.Data3 > s_tReg->Ac115VCh2OverCurrentTransientThd){
								v_eReg->Ac115VCh2OverCurrentTransientThd = tSpiData.Data3;
							}else if(tSpiData.Data4 > s_tReg->Ac115VCh2OverCurrentTransientThd){
								v_eReg->Ac115VCh2OverCurrentTransientThd = tSpiData.Data4;
							}else{
								v_eReg->Ac115VCh2OverCurrentTransientThd = tSpiData.Data5;
							}
							AC_CH2_I_count=0;
						}
				}
				else
				{
					AC_CH2_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh2OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh2OverCurrentSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_I);		//设置故障码
					//设置故障值
					if(tSpiData.Data3 > s_tReg->Ac115VCh2OverCurrentSteadyThd){
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh2OverCurrentSteadyThd){
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch2OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch2OverVoltageTransientThd)
				{
						DC1_CH2_V_count++;
						if(DC1_CH2_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH1_OFF;
							SetErrorCode(ERR_CH2_28VDC1_V);		//设置故障码
							v_eReg->Dc28V1Ch2OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH2_V_count=0;
						}
				}
				else
				{
					DC1_CH2_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch2OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch2OverCurrentTransientThd)
				{
						DC1_CH2_I_count++;
						if(DC1_CH2_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH2_OFF;
							SetErrorCode(ERR_CH2_28VDC1_I);		//设置故障码
							v_eReg->Dc28V1Ch2OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH2_I_count=0;
						}
				}
				else
				{
					DC1_CH2_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch2OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch2OverVoltageSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_V);		//设置故障码
					v_eReg->Dc28V2Ch2OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch2OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch2OverCurrentSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_I);		//设置故障码
					v_eReg->Dc28V2Ch2OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 5:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh3OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh3OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh3OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh3OverVoltageTransientThd)
				{
						AC_CH3_V_count++;
						if(AC_CH3_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH3_OFF;
							SetErrorCode(ERR_CH3_115V_T_V);		//设置故障码
							//设置故障值
							if(tSpiData.Data0 > s_tReg->Ac115VCh3OverVoltageTransientThd){
								v_eReg->Ac115VCh3OverVoltageTransientThd = tSpiData.Data0;
							}else if(tSpiData.Data1 > s_tReg->Ac115VCh3OverVoltageTransientThd){
								v_eReg->Ac115VCh3OverVoltageTransientThd = tSpiData.Data1;
							}else{
								v_eReg->Ac115VCh3OverVoltageTransientThd = tSpiData.Data2;
							}
							AC_CH3_V_count=0;
						}
				}
				else
				{
					AC_CH3_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh3OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh3OverVoltageSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_V);		//设置故障码
					//设置故障值
					if(tSpiData.Data0 > s_tReg->Ac115VCh3OverVoltageSteadyThd){
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data0;
					}else if(tSpiData.Data1 > s_tReg->Ac115VCh3OverVoltageSteadyThd){
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data1;
					}else{
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data2;
					}
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh3OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh3OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh3OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh3OverCurrentTransientThd)
				{
						AC_CH3_I_count++;
						if(AC_CH3_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH3_OFF;
							SetErrorCode(ERR_CH3_115V_T_I);		//设置故障码
							//设置故障值
							if(tSpiData.Data3 > s_tReg->Ac115VCh3OverCurrentTransientThd){
								v_eReg->Ac115VCh3OverCurrentTransientThd = tSpiData.Data3;
							}else if(tSpiData.Data4 > s_tReg->Ac115VCh3OverCurrentTransientThd){
								v_eReg->Ac115VCh3OverCurrentTransientThd = tSpiData.Data4;
							}else{
								v_eReg->Ac115VCh3OverCurrentTransientThd = tSpiData.Data5;
							}
							AC_CH3_I_count=0;
						}
				}
				else
				{
					AC_CH3_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh3OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh3OverCurrentSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_I);		//设置故障码
					//设置故障值
					if(tSpiData.Data3 > s_tReg->Ac115VCh3OverCurrentSteadyThd){
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh3OverCurrentSteadyThd){
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch3OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch3OverVoltageTransientThd)
				{
						DC1_CH3_V_count++;
						if(DC1_CH3_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH3_OFF;
							SetErrorCode(ERR_CH3_28VDC1_V);		//设置故障码
							//设置故障值
							v_eReg->Dc28V1Ch3OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH3_V_count=0;
						}
				}
				else
				{
					DC1_CH3_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch3OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch3OverCurrentTransientThd)
				{
						DC1_CH3_I_count++;
						if(DC1_CH3_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH3_OFF;
							SetErrorCode(ERR_CH3_28VDC1_I);		//设置故障码
							//设置故障值
							v_eReg->Dc28V1Ch3OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH3_I_count=0;
						}
				}
				else
				{
					DC1_CH3_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch3OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch3OverVoltageSteadyThd)
				{
						DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_V);		//设置故障码
					//设置故障值
					v_eReg->Dc28V2Ch3OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch3OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch3OverCurrentSteadyThd)
				{
					DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_V);		//设置故障码
					//设置故障值
					v_eReg->Dc28V2Ch3OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 0:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh4OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh4OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh4OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh4OverVoltageTransientThd)
				{
						AC_CH4_V_count++;
						if(AC_CH4_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH4_OFF;
							SetErrorCode(ERR_CH4_115V_T_V);		//设置故障码
							//设置故障值
							if(tSpiData.Data0 > s_tReg->Ac115VCh4OverVoltageTransientThd){
								v_eReg->Ac115VCh4OverVoltageTransientThd = tSpiData.Data0;
							}else if(tSpiData.Data1 > s_tReg->Ac115VCh4OverVoltageTransientThd){
								v_eReg->Ac115VCh4OverVoltageTransientThd = tSpiData.Data1;
							}else{
								v_eReg->Ac115VCh4OverVoltageTransientThd = tSpiData.Data2;
							}
							AC_CH4_V_count=0;
						}
				}
				else
				{
					AC_CH4_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh4OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh4OverVoltageSteadyThd)
				{
						DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_V);		//设置故障码
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh4OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh4OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh4OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh4OverCurrentTransientThd)
				{
						AC_CH4_I_count++;
						if(AC_CH4_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH4_OFF;
							SetErrorCode(ERR_CH4_115V_T_I);		//设置故障码
							AC_CH4_I_count=0;
						}
				}
				else
				{
					AC_CH4_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh4OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh4OverCurrentSteadyThd)
				{
						DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_I);		//设置故障码
				}
			}
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch4OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch4OverVoltageTransientThd)
				{
						DC1_CH4_V_count++;
						if(DC1_CH4_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH4_OFF;
							SetErrorCode(ERR_CH4_28VDC1_V);		//设置故障码
							DC1_CH4_V_count=0;
						}
				}
				else
				{
					DC1_CH4_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch4OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch4OverCurrentTransientThd)
				{
						DC1_CH4_I_count++;
						if(DC1_CH4_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH4_OFF;
							SetErrorCode(ERR_CH4_28VDC1_I);		//设置故障码
							DC1_CH4_I_count=0;
						}
				}
				else
				{
					DC1_CH4_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch4OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch4OverVoltageSteadyThd)
				{
						DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_V);		//设置故障码
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch4OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch4OverCurrentSteadyThd)
				{
						DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_I);		//设置故障码
				}
			}
			break;
		case 2:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh5OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh5OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh5OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh5OverVoltageTransientThd)
				{
						AC_CH5_V_count++;
						if(AC_CH5_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH5_OFF;
							SetErrorCode(ERR_CH5_115V_T_V);		//设置故障码
							AC_CH5_V_count=0;
						}
				}
				else
				{
					AC_CH5_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh5OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh5OverVoltageSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_V);		//设置故障码
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh5OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh5OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh5OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh5OverCurrentTransientThd)
				{
						AC_CH5_I_count++;
						if(AC_CH5_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH5_OFF;
							SetErrorCode(ERR_CH5_115V_T_I);		//设置故障码
							AC_CH5_I_count=0;
						}
				}
				else
				{
					AC_CH5_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh5OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh5OverCurrentSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_I);		//设置故障码
				}
			}
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch5OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch5OverVoltageTransientThd)
				{
						DC1_CH5_V_count++;
						if(DC1_CH5_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH5_OFF;
							SetErrorCode(ERR_CH5_28VDC1_V);		//设置故障码
							DC1_CH5_V_count=0;
						}
				}
				else
				{
					DC1_CH5_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch5OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch5OverCurrentTransientThd)
				{
						DC1_CH5_I_count++;
						if(DC1_CH5_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH5_OFF;
							SetErrorCode(ERR_CH5_28VDC1_I);		//设置故障码
							DC1_CH5_I_count=0;
						}
				}
				else
				{
					DC1_CH5_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch5OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch5OverVoltageSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_V);		//设置故障码
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch5OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch5OverCurrentSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_I);		//设置故障码
				}
			}
			break;
		case 1:
			//电压
			//瞬态
			if(s_tReg->Ac115VCh6OverVoltageTransientThd>0)
			{
				if(tSpiData.Data0 > s_tReg->Ac115VCh6OverVoltageTransientThd ||
						tSpiData.Data1 > s_tReg->Ac115VCh6OverVoltageTransientThd ||
							tSpiData.Data2 > s_tReg->Ac115VCh6OverVoltageTransientThd)
				{
						AC_CH6_V_count++;
						if(AC_CH6_V_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH6_OFF;
							SetErrorCode(ERR_CH6_115V_T_V);		//设置故障码
							AC_CH6_V_count=0;
						}
				}
				else
				{
					AC_CH6_V_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh6OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh6OverVoltageSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_V);		//设置故障码
				}
			}
			//电流
			//瞬态
			if(s_tReg->Ac115VCh6OverCurrentTransientThd>0)
			{
				if(tSpiData.Data3 > s_tReg->Ac115VCh6OverCurrentTransientThd ||
									tSpiData.Data4 > s_tReg->Ac115VCh6OverCurrentTransientThd ||
										tSpiData.Data5 > s_tReg->Ac115VCh6OverCurrentTransientThd)
				{
						AC_CH6_I_count++;
						if(AC_CH6_I_count > TRANSIENT_COUNT_UP)
						{
							DO_AC_CH6_OFF;
							SetErrorCode(ERR_CH6_115V_T_I);		//设置故障码
							AC_CH6_I_count=0;
						}
				}
				else
				{
					AC_CH6_I_count=0;
				}
			}
			//稳态
			if(s_tReg->Ac115VCh6OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh6OverCurrentSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_I);		//设置故障码
				}
			}
			
			//28V1--瞬态
			//电压
			if(s_tReg->Dc28V1Ch6OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch6OverVoltageTransientThd)
				{
						DC1_CH6_V_count++;
						if(DC1_CH6_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH6_OFF;
							SetErrorCode(ERR_CH6_28VDC1_V);		//设置故障码
							DC1_CH6_V_count=0;
						}
				}
				else
				{
					DC1_CH6_V_count=0;
				}
			}
			//电流
			if(s_tReg->Dc28V1Ch6OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch6OverCurrentTransientThd)
				{
						DC1_CH6_I_count++;
						if(DC1_CH6_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH6_OFF;
							SetErrorCode(ERR_CH6_28VDC1_I);		//设置故障码
							DC1_CH6_I_count=0;
						}
				}
				else
				{
					DC1_CH6_I_count=0;
				}
			}
			
			//28V2--稳态
			//电压
			if(s_tReg->Dc28V2Ch6OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch6OverVoltageSteadyThd)
				{
						DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_V);		//设置故障码
				}
			}
			//电流
			if(s_tReg->Dc28V2Ch6OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch6OverCurrentSteadyThd)
				{
						DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_I);		//设置故障码
				}
			}
			break;
		case 3:
			break;
		default:
			break;
		}
}
