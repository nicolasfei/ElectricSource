#include "gd32f4xx.h"
#include "OutSwitch.h"
#include "GetAdc.h"
#include "ErrorControl.h"

void HC245_Set(void)
{
		rcu_periph_clock_enable(RCU_GPIOE);// πƒ‹PORTE ±÷”
	
		//≈‰÷√PE12“˝Ω≈µƒƒ£ Ω
		gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_12);//≈‰÷√Œ™œ¬¿≠ƒ£ Ω
		gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_12);//≈‰÷√Œ™Õ∆ÕÏ ‰≥ˆ£¨ÀŸ∂»Œ™50M
		
		//≈‰÷√PE13“˝Ω≈µƒƒ£ Ω
		gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_13);//≈‰÷√Œ™œ¬¿≠ƒ£ Ω
		gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_13);//≈‰÷√Œ™Õ∆ÕÏ ‰≥ˆ£¨ÀŸ∂»Œ™50M
	
		gpio_bit_set(GPIOE,GPIO_PIN_12);  //DIR
		gpio_bit_reset(GPIOE,GPIO_PIN_13);  //OE
}

/**
	*	÷±¡˜/Ωª¡˜µÁ‘¥øÿ÷∆
	*
	*/
void HC245_Power_Switch_Config()
{
	T_REG *s_tReg = ReadReg();
	if(s_tReg->RunMode == 1)		//µÁ‘¥  ≈‰∆˜π§◊˜ƒ£ Ω--0000H£∫ø’œ– 0001H£∫’˝≥£π§◊˜        ’˝≥£ƒ£ Ω≤≈ø…“‘»•≤Ÿ◊˜
	{		
		HC245_DC_Switch_Config(s_tReg->DcPowerControl);
		HC245_AC_Switch_Config(s_tReg->AcPowerControl);
		SetAcDcDio(s_tReg->AcPowerControl,s_tReg->DcPowerControl);
	}
	else		//ø’œ–ƒ£ Ω –Ë“™ªπ‘≠÷Æ«∞µƒ◊¥Ã¨
	{
		s_tReg->AcPowerControl = GetAcDioSet();
		s_tReg->DcPowerControl = GetDcDioSet();
	}
}

/**
	* ÷±¡˜µÁ‘¥øÿ÷∆
	*	
	*	@par value øÿ÷∆÷µ--∞¥Œª
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
		//«Âø’π ’œ¬Î
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
	* Ωª¡˜µÁ‘¥øÿ÷∆
	*	
	*	@par value øÿ÷∆÷µ--∞¥Œª
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
	**	∏˘æ›≤…ºØµΩµƒADC ˝æ›£®À≤ ±÷µ£¨Œ»∂®÷µ(¬À≤®÷µ)£©¿¥≈–∂œ£¨Ω¯––ø™πÿµƒ≤Ÿ◊˜
	**	@par channel ADCÕ®µ¿
	**	@par tSpiData	≤…ºØµΩµƒ ˝æ›
	**	@par tFilterData	¬À≤®∫Ûµƒ ˝æ›
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
void CheckAdcDataBak()
{
	T_REG *s_tReg = ReadReg();
	//T_ERROR_REG *v_eReg = ReadErrorReg();
	
	//J1-------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh1OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageTransientThd ||
						s_tReg->Ac115VbCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageTransientThd ||
							s_tReg->Ac115VcCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageTransientThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh1OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh1OutputVoltage > s_tReg->Ac115VCh1OverVoltageSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh1OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentTransientThd ||
									s_tReg->Ac115VbCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentTransientThd ||
										s_tReg->Ac115VcCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentTransientThd)
				{
							DO_AC_CH1_OFF;
							SetErrorCode(ERR_CH1_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh1OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh1OutputCurrent > s_tReg->Ac115VCh1OverCurrentSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_CH1_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch1OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch1OutputVoltage > s_tReg->Dc28V1Ch1OverVoltageTransientThd)
				{
					DO_DC1_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch1OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch1OutputCurrent > s_tReg->Dc28V1Ch1OverCurrentTransientThd)
				{
					DO_DC1_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_CH1_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch1OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch1OutputVoltage > s_tReg->Dc28V2Ch1OverVoltageSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch1OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch1OutputCurrent > s_tReg->Dc28V2Ch1OverCurrentSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
	
	//J2-------------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh2OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageTransientThd ||
						s_tReg->Ac115VbCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageTransientThd ||
							s_tReg->Ac115VcCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageTransientThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh2OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh2OutputVoltage > s_tReg->Ac115VCh2OverVoltageSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh2OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentTransientThd ||
									s_tReg->Ac115VbCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentTransientThd ||
										s_tReg->Ac115VcCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentTransientThd)
				{
							DO_AC_CH2_OFF;
							SetErrorCode(ERR_CH2_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh2OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh2OutputCurrent > s_tReg->Ac115VCh2OverCurrentSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_Ch2_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch2OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch2OutputVoltage > s_tReg->Dc28V1Ch2OverVoltageTransientThd)
				{
					DO_DC1_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch2OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch2OutputCurrent > s_tReg->Dc28V1Ch2OverCurrentTransientThd)
				{
					DO_DC1_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_Ch2_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch2OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch2OutputVoltage > s_tReg->Dc28V2Ch2OverVoltageSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch2OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch2OutputCurrent > s_tReg->Dc28V2Ch2OverCurrentSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
	
	//J3-------------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh3OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageTransientThd ||
						s_tReg->Ac115VbCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageTransientThd ||
							s_tReg->Ac115VcCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageTransientThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh3OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh3OutputVoltage > s_tReg->Ac115VCh3OverVoltageSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh3OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentTransientThd ||
									s_tReg->Ac115VbCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentTransientThd ||
										s_tReg->Ac115VcCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentTransientThd)
				{
							DO_AC_CH3_OFF;
							SetErrorCode(ERR_CH3_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh3OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh3OutputCurrent > s_tReg->Ac115VCh3OverCurrentSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_Ch3_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch3OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch3OutputVoltage > s_tReg->Dc28V1Ch3OverVoltageTransientThd)
				{
					DO_DC1_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch3OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch3OutputCurrent > s_tReg->Dc28V1Ch3OverCurrentTransientThd)
				{
					DO_DC1_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_Ch3_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch3OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch3OutputVoltage > s_tReg->Dc28V2Ch3OverVoltageSteadyThd)
				{
					DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch3OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch3OutputCurrent > s_tReg->Dc28V2Ch3OverCurrentSteadyThd)
				{
					DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
	
	//J4-------------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh4OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageTransientThd ||
						s_tReg->Ac115VbCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageTransientThd ||
							s_tReg->Ac115VcCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageTransientThd)
				{
					DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh4OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh4OutputVoltage > s_tReg->Ac115VCh4OverVoltageSteadyThd)
				{
					DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh4OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentTransientThd ||
									s_tReg->Ac115VbCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentTransientThd ||
										s_tReg->Ac115VcCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentTransientThd)
				{
							DO_AC_CH4_OFF;
							SetErrorCode(ERR_CH4_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh4OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh4OutputCurrent > s_tReg->Ac115VCh4OverCurrentSteadyThd)
				{
					DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_Ch4_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch4OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch4OutputVoltage > s_tReg->Dc28V1Ch4OverVoltageTransientThd)
				{
					DO_DC1_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch4OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch4OutputCurrent > s_tReg->Dc28V1Ch4OverCurrentTransientThd)
				{
					DO_DC1_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_Ch4_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch4OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch4OutputVoltage > s_tReg->Dc28V2Ch4OverVoltageSteadyThd)
				{
					DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch4OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch4OutputCurrent > s_tReg->Dc28V2Ch4OverCurrentSteadyThd)
				{
					DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
	
	//J5-------------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh5OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageTransientThd ||
						s_tReg->Ac115VbCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageTransientThd ||
							s_tReg->Ac115VcCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageTransientThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh5OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh5OutputVoltage > s_tReg->Ac115VCh5OverVoltageSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh5OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentTransientThd ||
									s_tReg->Ac115VbCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentTransientThd ||
										s_tReg->Ac115VcCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentTransientThd)
				{
							DO_AC_CH5_OFF;
							SetErrorCode(ERR_CH5_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh5OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh5OutputCurrent > s_tReg->Ac115VCh5OverCurrentSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_Ch5_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch5OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch5OutputVoltage > s_tReg->Dc28V1Ch5OverVoltageTransientThd)
				{
					DO_DC1_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch5OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch5OutputCurrent > s_tReg->Dc28V1Ch5OverCurrentTransientThd)
				{
					DO_DC1_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_Ch5_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch5OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch5OutputVoltage > s_tReg->Dc28V2Ch5OverVoltageSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch5OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch5OutputCurrent > s_tReg->Dc28V2Ch5OverCurrentSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}		
	
	//J6-------------------------------------------------------------------------------------------------------
			//µÁ—π
			//À≤Ã¨
			if(s_tReg->Ac115VCh6OverVoltageTransientThd>0)
			{
				if(s_tReg->Ac115VaCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageTransientThd ||
						s_tReg->Ac115VbCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageTransientThd ||
							s_tReg->Ac115VcCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageTransientThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_T_V);			//…Ë÷√π ’œ¬Î
				}			
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh6OverVoltageSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
						s_tReg->Ac115VbCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
							s_tReg->Ac115VcCh6OutputVoltage > s_tReg->Ac115VCh6OverVoltageSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
			if(s_tReg->Ac115VCh6OverCurrentTransientThd>0)
			{
				if(s_tReg->Ac115VaCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentTransientThd ||
									s_tReg->Ac115VbCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentTransientThd ||
										s_tReg->Ac115VcCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentTransientThd)
				{
							DO_AC_CH6_OFF;
							SetErrorCode(ERR_CH6_115V_T_I);		//…Ë÷√π ’œ¬Î
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh6OverCurrentSteadyThd>0)
			{
				if(s_tReg->Ac115VaCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
						s_tReg->Ac115VbCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
							s_tReg->Ac115VcCh6OutputCurrent > s_tReg->Ac115VCh6OverCurrentSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
		
			
			//28_Ch6_V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch6OverVoltageTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch6OutputVoltage > s_tReg->Dc28V1Ch6OverVoltageTransientThd)
				{
					DO_DC1_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC1_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch6OverCurrentTransientThd>0)
			{
				if(s_tReg->Dc28V1Ch6OutputCurrent > s_tReg->Dc28V1Ch6OverCurrentTransientThd)
				{
					DO_DC1_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC1_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28_Ch6_V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch6OverVoltageSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch6OutputVoltage > s_tReg->Dc28V2Ch6OverVoltageSteadyThd)
				{
					DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch6OverCurrentSteadyThd>0)
			{
				if(s_tReg->Dc28V2Ch6OutputCurrent > s_tReg->Dc28V2Ch6OverCurrentSteadyThd)
				{
					DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
}


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
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH1_115V_T_V);			//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh1OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh1OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh1OverVoltageSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tFilterData.Data0 > s_tReg->Ac115VCh1OverVoltageSteadyThd){
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data0;
					}else if(tFilterData.Data1 > s_tReg->Ac115VCh1OverVoltageSteadyThd){
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data1;
					}else{
						v_eReg->Ac115VCh1OverVoltageSteadyThd = tFilterData.Data2;
					}
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH1_115V_T_I);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh1OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh1OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh1OverCurrentSteadyThd)
				{
					DO_AC_CH1_OFF;
					SetErrorCode(ERR_CH1_115V_S_I);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tSpiData.Data3 > s_tReg->Ac115VCh1OverCurrentSteadyThd){
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh1OverCurrentSteadyThd){
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh1OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
		
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch1OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch1OverVoltageTransientThd)
				{
						DC1_CH1_V_count++;
						if(DC1_CH1_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH1_OFF;
							SetErrorCode(ERR_CH1_28VDC1_V);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
							v_eReg->Dc28V1Ch1OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH1_V_count=0;
						}
				}
				else
				{
					DC1_CH1_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch1OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch1OverCurrentTransientThd)
				{
						DC1_CH1_I_count++;
						if(DC1_CH1_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH1_OFF;
							SetErrorCode(ERR_CH1_28VDC1_I);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
							v_eReg->Dc28V1Ch1OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH1_I_count=0;
						}
				}
				else
				{
					DC1_CH1_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch1OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch1OverVoltageSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					v_eReg->Dc28V2Ch1OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch1OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch1OverCurrentSteadyThd)
				{
					DO_DC2_CH1_OFF;
					SetErrorCode(ERR_CH1_28VDC2_I);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					v_eReg->Dc28V2Ch1OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 7:
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH2_115V_T_V);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh2OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh2OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh2OverVoltageSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tSpiData.Data0 > s_tReg->Ac115VCh2OverVoltageSteadyThd){
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data0;
					}else if(tSpiData.Data1 > s_tReg->Ac115VCh2OverVoltageSteadyThd){
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data1;
					}else{
						v_eReg->Ac115VCh2OverVoltageSteadyThd = tSpiData.Data2;
					}
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH2_115V_T_I);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh2OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh2OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh2OverCurrentSteadyThd)
				{
					DO_AC_CH2_OFF;
					SetErrorCode(ERR_CH2_115V_S_I);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tSpiData.Data3 > s_tReg->Ac115VCh2OverCurrentSteadyThd){
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh2OverCurrentSteadyThd){
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh2OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch2OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch2OverVoltageTransientThd)
				{
						DC1_CH2_V_count++;
						if(DC1_CH2_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH1_OFF;
							SetErrorCode(ERR_CH2_28VDC1_V);		//…Ë÷√π ’œ¬Î
							v_eReg->Dc28V1Ch2OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH2_V_count=0;
						}
				}
				else
				{
					DC1_CH2_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch2OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch2OverCurrentTransientThd)
				{
						DC1_CH2_I_count++;
						if(DC1_CH2_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH2_OFF;
							SetErrorCode(ERR_CH2_28VDC1_I);		//…Ë÷√π ’œ¬Î
							v_eReg->Dc28V1Ch2OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH2_I_count=0;
						}
				}
				else
				{
					DC1_CH2_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch2OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch2OverVoltageSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_V);		//…Ë÷√π ’œ¬Î
					v_eReg->Dc28V2Ch2OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch2OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch2OverCurrentSteadyThd)
				{
					DO_DC2_CH2_OFF;
					SetErrorCode(ERR_CH2_28VDC2_I);		//…Ë÷√π ’œ¬Î
					v_eReg->Dc28V2Ch2OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 5:
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH3_115V_T_V);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh3OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh3OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh3OverVoltageSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tSpiData.Data0 > s_tReg->Ac115VCh3OverVoltageSteadyThd){
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data0;
					}else if(tSpiData.Data1 > s_tReg->Ac115VCh3OverVoltageSteadyThd){
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data1;
					}else{
						v_eReg->Ac115VCh3OverVoltageSteadyThd = tSpiData.Data2;
					}
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH3_115V_T_I);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh3OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh3OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh3OverCurrentSteadyThd)
				{
					DO_AC_CH3_OFF;
					SetErrorCode(ERR_CH3_115V_S_I);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					if(tSpiData.Data3 > s_tReg->Ac115VCh3OverCurrentSteadyThd){
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data3;
					}else if(tSpiData.Data4 > s_tReg->Ac115VCh3OverCurrentSteadyThd){
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data4;
					}else{
						v_eReg->Ac115VCh3OverCurrentSteadyThd = tSpiData.Data5;
					}
				}
			}
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch3OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch3OverVoltageTransientThd)
				{
						DC1_CH3_V_count++;
						if(DC1_CH3_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH3_OFF;
							SetErrorCode(ERR_CH3_28VDC1_V);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
							v_eReg->Dc28V1Ch3OverVoltageTransientThd = tSpiData.Data6;
							DC1_CH3_V_count=0;
						}
				}
				else
				{
					DC1_CH3_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch3OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch3OverCurrentTransientThd)
				{
						DC1_CH3_I_count++;
						if(DC1_CH3_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH3_OFF;
							SetErrorCode(ERR_CH3_28VDC1_I);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
							v_eReg->Dc28V1Ch3OverCurrentTransientThd = tSpiData.Data7;
							DC1_CH3_I_count=0;
						}
				}
				else
				{
					DC1_CH3_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch3OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch3OverVoltageSteadyThd)
				{
						DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					v_eReg->Dc28V2Ch3OverVoltageSteadyThd = tSpiData.Data8;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch3OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch3OverCurrentSteadyThd)
				{
					DO_DC2_CH3_OFF;
					SetErrorCode(ERR_CH3_28VDC2_V);		//…Ë÷√π ’œ¬Î
					//…Ë÷√π ’œ÷µ
					v_eReg->Dc28V2Ch3OverCurrentSteadyThd = tSpiData.Data9;
				}
			}
			break;
		case 0:
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH4_115V_T_V);		//…Ë÷√π ’œ¬Î
							//…Ë÷√π ’œ÷µ
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
			//Œ»Ã¨
			if(s_tReg->Ac115VCh4OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh4OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh4OverVoltageSteadyThd)
				{
						DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH4_115V_T_I);		//…Ë÷√π ’œ¬Î
							AC_CH4_I_count=0;
						}
				}
				else
				{
					AC_CH4_I_count=0;
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh4OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh4OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh4OverCurrentSteadyThd)
				{
						DO_AC_CH4_OFF;
					SetErrorCode(ERR_CH4_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch4OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch4OverVoltageTransientThd)
				{
						DC1_CH4_V_count++;
						if(DC1_CH4_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH4_OFF;
							SetErrorCode(ERR_CH4_28VDC1_V);		//…Ë÷√π ’œ¬Î
							DC1_CH4_V_count=0;
						}
				}
				else
				{
					DC1_CH4_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch4OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch4OverCurrentTransientThd)
				{
						DC1_CH4_I_count++;
						if(DC1_CH4_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH4_OFF;
							SetErrorCode(ERR_CH4_28VDC1_I);		//…Ë÷√π ’œ¬Î
							DC1_CH4_I_count=0;
						}
				}
				else
				{
					DC1_CH4_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch4OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch4OverVoltageSteadyThd)
				{
						DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch4OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch4OverCurrentSteadyThd)
				{
						DO_DC2_CH4_OFF;
					SetErrorCode(ERR_CH4_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
			break;
		case 2:
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH5_115V_T_V);		//…Ë÷√π ’œ¬Î
							AC_CH5_V_count=0;
						}
				}
				else
				{
					AC_CH5_V_count=0;
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh5OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh5OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh5OverVoltageSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH5_115V_T_I);		//…Ë÷√π ’œ¬Î
							AC_CH5_I_count=0;
						}
				}
				else
				{
					AC_CH5_I_count=0;
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh5OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh5OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh5OverCurrentSteadyThd)
				{
					DO_AC_CH5_OFF;
					SetErrorCode(ERR_CH5_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch5OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch5OverVoltageTransientThd)
				{
						DC1_CH5_V_count++;
						if(DC1_CH5_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH5_OFF;
							SetErrorCode(ERR_CH5_28VDC1_V);		//…Ë÷√π ’œ¬Î
							DC1_CH5_V_count=0;
						}
				}
				else
				{
					DC1_CH5_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch5OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch5OverCurrentTransientThd)
				{
						DC1_CH5_I_count++;
						if(DC1_CH5_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH5_OFF;
							SetErrorCode(ERR_CH5_28VDC1_I);		//…Ë÷√π ’œ¬Î
							DC1_CH5_I_count=0;
						}
				}
				else
				{
					DC1_CH5_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch5OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch5OverVoltageSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch5OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch5OverCurrentSteadyThd)
				{
					DO_DC2_CH5_OFF;
					SetErrorCode(ERR_CH5_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
			break;
		case 1:
			//µÁ—π
			//À≤Ã¨
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
							SetErrorCode(ERR_CH6_115V_T_V);		//…Ë÷√π ’œ¬Î
							AC_CH6_V_count=0;
						}
				}
				else
				{
					AC_CH6_V_count=0;
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh6OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data0 > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
						tFilterData.Data1 > s_tReg->Ac115VCh6OverVoltageSteadyThd ||
							tFilterData.Data2 > s_tReg->Ac115VCh6OverVoltageSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			//À≤Ã¨
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
							SetErrorCode(ERR_CH6_115V_T_I);		//…Ë÷√π ’œ¬Î
							AC_CH6_I_count=0;
						}
				}
				else
				{
					AC_CH6_I_count=0;
				}
			}
			//Œ»Ã¨
			if(s_tReg->Ac115VCh6OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data3 > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
						tFilterData.Data4 > s_tReg->Ac115VCh6OverCurrentSteadyThd ||
							tFilterData.Data5 > s_tReg->Ac115VCh6OverCurrentSteadyThd)
				{
					DO_AC_CH6_OFF;
					SetErrorCode(ERR_CH6_115V_S_I);		//…Ë÷√π ’œ¬Î
				}
			}
			
			//28V1--À≤Ã¨
			//µÁ—π
			if(s_tReg->Dc28V1Ch6OverVoltageTransientThd>0)
			{
				if(tSpiData.Data6 > s_tReg->Dc28V1Ch6OverVoltageTransientThd)
				{
						DC1_CH6_V_count++;
						if(DC1_CH6_V_count > TRANSIENT_COUNT_UP)
						{
							DO_DC2_CH6_OFF;
							SetErrorCode(ERR_CH6_28VDC1_V);		//…Ë÷√π ’œ¬Î
							DC1_CH6_V_count=0;
						}
				}
				else
				{
					DC1_CH6_V_count=0;
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V1Ch6OverCurrentTransientThd>0)
			{
				if(tSpiData.Data7 > s_tReg->Dc28V1Ch6OverCurrentTransientThd)
				{
						DC1_CH6_I_count++;
						if(DC1_CH6_I_count > TRANSIENT_COUNT_UP)
						{
							DO_DC1_CH6_OFF;
							SetErrorCode(ERR_CH6_28VDC1_I);		//…Ë÷√π ’œ¬Î
							DC1_CH6_I_count=0;
						}
				}
				else
				{
					DC1_CH6_I_count=0;
				}
			}
			
			//28V2--Œ»Ã¨
			//µÁ—π
			if(s_tReg->Dc28V2Ch6OverVoltageSteadyThd>0)
			{
				if(tFilterData.Data8 > s_tReg->Dc28V2Ch6OverVoltageSteadyThd)
				{
						DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_V);		//…Ë÷√π ’œ¬Î
				}
			}
			//µÁ¡˜
			if(s_tReg->Dc28V2Ch6OverCurrentSteadyThd>0)
			{
				if(tFilterData.Data9 > s_tReg->Dc28V2Ch6OverCurrentSteadyThd)
				{
						DO_DC2_CH6_OFF;
					SetErrorCode(ERR_CH6_28VDC2_I);		//…Ë÷√π ’œ¬Î
				}
			}
			break;
		case 3:
			break;
		default:
			break;
		}
}
