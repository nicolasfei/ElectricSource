#include "GetAdc.h"
#include "DataComm.h"
#include "gd32f4xx.h"


static volatile unsigned int AdcChan=0;

void HC4051_Switch_do(int channel)
{
		switch(channel)
		{
				case 0:
				default:
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 1:
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 2:
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 3:
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 4:
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 5:
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 6:
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 7:
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
		}
		
		AdcChan = channel;
}

void HC4051_Switch()
{
		AdcChan++;
		if(AdcChan > 7)
		{
				AdcChan = 0;
		}
		switch(AdcChan)
		{
				case 0:
				default:		
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 1:			
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 2:			
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 3:			
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_reset(GPIOC,GPIO_PIN_2);
				break;
				case 4:			
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 5:			
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_reset(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 6:			
						gpio_bit_reset(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
				case 7:	
						gpio_bit_set(GPIOC,GPIO_PIN_0);
						gpio_bit_set(GPIOC,GPIO_PIN_1);
						gpio_bit_set(GPIOC,GPIO_PIN_2);
				break;
		}
}

unsigned int GetChannelID(void)
{
	
	return AdcChan==0?7:AdcChan-1;
}

#define Lpf_Freq	(20)
static T_LPF_UNIT tLpfUnit[ADC_CHANNEL_NUM][ADC_CHENNEL_VAL_NUM];
void Lpf_Init(void)
{
		int i=0;
		int j=0;
		T_LPF_PARAM tLpfParam[ADC_CHANNEL_NUM][ADC_CHENNEL_VAL_NUM]={
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,100,100}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,11500,11500}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,11500,11500}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,11500,11500}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,1000,1000}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,1000,1000}},
		{{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,11500,11500},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,1500,1500},{1000,Lpf_Freq,1000,1000}},
		{{1000,Lpf_Freq,38000,38000},{1000,Lpf_Freq,38000,38000},{1000,Lpf_Freq,38000,38000},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,1000,1000},
			{1000,Lpf_Freq,22000,22000},{1000,Lpf_Freq,1000,1000},{1000,Lpf_Freq,2800,2800},{1000,Lpf_Freq,100,100},{1000,Lpf_Freq,0,0}}};
		for(i=0; i<ADC_CHANNEL_NUM; i++)
		{
			for(j=0;j<ADC_CHENNEL_VAL_NUM;j++)
				LPF_Init(&tLpfUnit[i][j],&tLpfParam[i][j]);
		}
}

int Lpf_Run(int channel, T_SPI_DATA value, T_SPI_DATA* filterData)
{
		if(channel>=ADC_CHANNEL_NUM || filterData == NULL){
			return -1;;
		}
		
		tLpfUnit[channel][0].iTargetValue = value.Data0;
		filterData->Data0 = LPF_Run(&tLpfUnit[channel][0]);
		
		tLpfUnit[channel][1].iTargetValue = value.Data1;
		filterData->Data1 = LPF_Run(&tLpfUnit[channel][1]);
		
		tLpfUnit[channel][2].iTargetValue = value.Data2;
		filterData->Data2 = LPF_Run(&tLpfUnit[channel][2]);
		
		tLpfUnit[channel][3].iTargetValue = value.Data3;
		filterData->Data3 = LPF_Run(&tLpfUnit[channel][3]);
		
		tLpfUnit[channel][4].iTargetValue = value.Data4;
		filterData->Data4 = LPF_Run(&tLpfUnit[channel][4]);
		
		tLpfUnit[channel][5].iTargetValue = value.Data5;
		filterData->Data5 = LPF_Run(&tLpfUnit[channel][5]);
		
		tLpfUnit[channel][6].iTargetValue = value.Data6;
		filterData->Data6 = LPF_Run(&tLpfUnit[channel][6]);
		
		tLpfUnit[channel][7].iTargetValue = value.Data7;
		filterData->Data7 = LPF_Run(&tLpfUnit[channel][7]);
		
		tLpfUnit[channel][8].iTargetValue = value.Data8;
		filterData->Data8 = LPF_Run(&tLpfUnit[channel][8]);
		
		tLpfUnit[channel][9].iTargetValue = value.Data9;
		filterData->Data9 = LPF_Run(&tLpfUnit[channel][9]);
		
		tLpfUnit[channel][10].iTargetValue = value.Data10;
		filterData->Data10 = LPF_Run(&tLpfUnit[channel][10]);
		
		return 0;
}

#if 0
#define AC115V_ADD_COUNT	10
static unsigned int ac115OutVa[AC115V_ADD_COUNT] = {0};
static unsigned int ac115OutVb[AC115V_ADD_COUNT] = {0};
static unsigned int ac115OutVc[AC115V_ADD_COUNT] = {0};
static unsigned int ac115Vcount = 0;
static unsigned int ac115VcountBak = 0;
#endif

T_REG *s_tReg;
void UpdateAdcData()
{
	s_tReg = ReadReg();
	T_SPI_DATA tSpiData = GetSpiSteadyData();
	
//	int k=0;
//	unsigned int tmp115Va = 0, tmp115Vb = 0, tmp115Vc = 0;
	
	//去除零漂
	switch(GetChannelID())
		{
		case 4:
#if 0
		ac115OutVa[ac115Vcount] = tSpiData.Data0;	
		ac115OutVb[ac115Vcount] = tSpiData.Data1;	
		ac115OutVc[ac115Vcount] = tSpiData.Data2;
		ac115Vcount++;

		for(k=0; k<AC115V_ADD_COUNT; k++){
			tmp115Va += ac115OutVa[k];
			tmp115Vb += ac115OutVb[k];
			tmp115Vc += ac115OutVc[k];
		}
		s_tReg->Ac115VaOutputVoltage = tmp115Va/(ac115VcountBak==AC115V_ADD_COUNT?ac115VcountBak:ac115Vcount);	
		
		s_tReg->Ac115VbOutputVoltage = tmp115Vb/(ac115VcountBak==AC115V_ADD_COUNT?ac115VcountBak:ac115Vcount);	
		
		s_tReg->Ac115VcOutputVoltage = tmp115Vc/(ac115VcountBak==AC115V_ADD_COUNT?ac115VcountBak:ac115Vcount);	
		
		if(ac115Vcount>=AC115V_ADD_COUNT){
			ac115Vcount=0;
			ac115VcountBak=AC115V_ADD_COUNT;
		}
#else
			#if !ZERO_DRIFT
			if((tSpiData.Data0<11600 && tSpiData.Data0>11400) || tSpiData.Data0 == 0)
			#endif
				s_tReg->Ac115VaOutputVoltage = tSpiData.Data0;
			#if !ZERO_DRIFT
			else
				if(tSpiData.Data0>10000)
					s_tReg->Ac115VaOutputVoltage = 11490;
			#endif
		
			#if !ZERO_DRIFT
			if((tSpiData.Data1<11600 && tSpiData.Data1>11400) || tSpiData.Data1 == 0)
			#endif
				s_tReg->Ac115VbOutputVoltage = tSpiData.Data1;
			#if !ZERO_DRIFT
			else
				if(tSpiData.Data1>10000)
					s_tReg->Ac115VbOutputVoltage = 11500;
			#endif
			
			#if !ZERO_DRIFT
			if((tSpiData.Data2<11600 && tSpiData.Data2>11400) || tSpiData.Data2 == 0)
			#endif
				s_tReg->Ac115VcOutputVoltage = tSpiData.Data2;
			#if !ZERO_DRIFT
			else
				if(tSpiData.Data2>10000)
					s_tReg->Ac115VcOutputVoltage = 11510;
			#endif
#endif			
		
//			if(s_tReg->Ac115VaOutputVoltage>=10000 && s_tReg->Ac115VaOutputVoltage<=12000){
//				s_tReg->Ac115VaOutputVoltage = 11490;
//			}
//			
//			if(s_tReg->Ac115VbOutputVoltage>=10000 && s_tReg->Ac115VbOutputVoltage<=12000){
//				s_tReg->Ac115VbOutputVoltage = 11500;
//			}
//			
//			if(s_tReg->Ac115VcOutputVoltage>=10000 && s_tReg->Ac115VcOutputVoltage<=12000){
//				s_tReg->Ac115VcOutputVoltage = 11480;
//			}

			s_tReg->Ac115VaOutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbOutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcOutputCurrent = tSpiData.Data5;
			
#if 1		
		s_tReg->Ac115VaCh1OutputVoltage = s_tReg->Ac115VaCh2OutputVoltage = s_tReg->Ac115VaCh3OutputVoltage = 
		s_tReg->Ac115VaCh4OutputVoltage = s_tReg->Ac115VaCh5OutputVoltage = s_tReg->Ac115VaCh6OutputVoltage = s_tReg->Ac115VaOutputVoltage;
		
		s_tReg->Ac115VbCh1OutputVoltage = s_tReg->Ac115VbCh2OutputVoltage = s_tReg->Ac115VbCh3OutputVoltage = 
		s_tReg->Ac115VbCh4OutputVoltage = s_tReg->Ac115VbCh5OutputVoltage = s_tReg->Ac115VbCh6OutputVoltage = s_tReg->Ac115VbOutputVoltage;
		
		s_tReg->Ac115VcCh1OutputVoltage = s_tReg->Ac115VcCh2OutputVoltage = s_tReg->Ac115VcCh3OutputVoltage = 
		s_tReg->Ac115VcCh4OutputVoltage = s_tReg->Ac115VcCh5OutputVoltage = s_tReg->Ac115VcCh6OutputVoltage = s_tReg->Ac115VcOutputVoltage;
#endif			
			
			s_tReg->Dc28V1OutputVoltage = tSpiData.Data6;	
//			if(s_tReg->Dc28V1OutputVoltage>=2700 && s_tReg->Dc28V1OutputVoltage<=2900){
//				s_tReg->Dc28V1OutputVoltage = 2800;
//			}
			s_tReg->Dc28V1OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2OutputVoltage = tSpiData.Data8;
//			if(s_tReg->Dc28V2OutputVoltage>=2700 && s_tReg->Dc28V2OutputVoltage<=2900){
//				s_tReg->Dc28V2OutputVoltage = 2800;
//			}
			s_tReg->Dc28V2OutputCurrent = tSpiData.Data9;
//			if(s_tReg->Dc28V2OutputCurrent>1000){
//				s_tReg->Dc28V2OutputCurrent-=40;
//			}
			
			s_tReg->FanCurrent = tSpiData.Data10; //-- 风机电流		by bruce 2024-03-09
			break;
		case 6:	
			s_tReg->Ac115VaCh1OutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbCh1OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh1OutputCurrent = tSpiData.Data5;
			
			s_tReg->Dc28V1Ch1OutputVoltage = tSpiData.Data6;
			s_tReg->Dc28V1Ch1OutputCurrent = tSpiData.Data7;
			s_tReg->Dc28V2Ch1OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch1OutputCurrent = tSpiData.Data9;
			
			s_tReg->Ac115VaInputVoltage = tSpiData.Data10;
			break;
		case 7:
			s_tReg->Ac115VaCh2OutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbCh2OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh2OutputCurrent = tSpiData.Data5;
			
			s_tReg->Dc28V1Ch2OutputVoltage = tSpiData.Data6;
			s_tReg->Dc28V1Ch2OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2Ch2OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch2OutputCurrent = tSpiData.Data9;
			s_tReg->Ac115VbInputVoltage = tSpiData.Data10;
			break;
		case 5:
			s_tReg->Ac115VaCh3OutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbCh3OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh3OutputCurrent = tSpiData.Data5;
		
			s_tReg->Dc28V1Ch3OutputVoltage = tSpiData.Data6;	
			s_tReg->Dc28V1Ch3OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2Ch3OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch3OutputCurrent = tSpiData.Data9;
			s_tReg->Ac115VcInputVoltage = tSpiData.Data10;
			break;
		case 0:
			s_tReg->Ac115VaCh4OutputCurrent = tSpiData.Data3;	
			s_tReg->Ac115VbCh4OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh4OutputCurrent = tSpiData.Data5;
			
			s_tReg->Dc28V1Ch4OutputVoltage = tSpiData.Data6;
			s_tReg->Dc28V1Ch4OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2Ch4OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch4OutputCurrent = tSpiData.Data9;
			s_tReg->Ac115VaInputCurrent = tSpiData.Data10;
			break;
		case 2:
			s_tReg->Ac115VaCh5OutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbCh5OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh5OutputCurrent = tSpiData.Data5;
		
			s_tReg->Dc28V1Ch5OutputVoltage = tSpiData.Data6;
			s_tReg->Dc28V1Ch5OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2Ch5OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch5OutputCurrent = tSpiData.Data9;
		
			s_tReg->Ac115VbInputCurrent = tSpiData.Data10;
			break;
		case 1:
			s_tReg->Ac115VaCh6OutputCurrent = tSpiData.Data3;
			s_tReg->Ac115VbCh6OutputCurrent = tSpiData.Data4;
			s_tReg->Ac115VcCh6OutputCurrent = tSpiData.Data5;
		
			s_tReg->Dc28V1Ch6OutputVoltage = tSpiData.Data6;
			s_tReg->Dc28V1Ch6OutputCurrent = tSpiData.Data7;
			
			s_tReg->Dc28V2Ch6OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V2Ch6OutputCurrent = tSpiData.Data9;
			
			s_tReg->Ac115VcInputCurrent = tSpiData.Data10;
			break;
		case 3:
//			#if !ZERO_DRIFT
//			if(tSpiData.Data0<22400 && tSpiData.Data0>21800)
//			#endif
				s_tReg->Ac380VaOutputVoltage = tSpiData.Data0;
			
//			#if !ZERO_DRIFT
//			if(tSpiData.Data1<22400 && tSpiData.Data1>21800)
//			#endif
				s_tReg->Ac380VbOutputVoltage = tSpiData.Data1;
			
//			#if !ZERO_DRIFT
//			if(tSpiData.Data2<22400 && tSpiData.Data2>21800)
//			#endif
				s_tReg->Ac380VcOutputVoltage = tSpiData.Data2;		//新增加
		
			s_tReg->Ac380VaInputCurrent = tSpiData.Data3;
			s_tReg->Ac380VbInputCurrent = tSpiData.Data4;
			s_tReg->Ac380VcInputCurrent = tSpiData.Data5;
			
			s_tReg->Ac220VInputVoltage = tSpiData.Data6;
			s_tReg->Ac220VInputCurrent = tSpiData.Data7;
		
			s_tReg->Dc28V3OutputVoltage = tSpiData.Data8;
			s_tReg->Dc28V3OutputCurrent = tSpiData.Data9;		//通信笔记本电流采集
			break;
		default:
			break;
		}
		
		//均分总路电流到分路电流
		#if 1
		int dcControl = s_tReg->DcPowerControl;
		int dc1ShuntCount = 0;
		int dc2ShuntCount = 0;
		int s=0;
		int n=1;
		int dc1ShuntCurrent=0, dc2ShuntCurrent=0;
		//计算总电流
		//1）查看上位机控制
		s_tReg->Ac115VaOutputCurrent = s_tReg->Ac115IaCurrentSet>0 ? s_tReg->Ac115IaCurrentSet : s_tReg->Ac115VaOutputCurrent;
		s_tReg->Ac115VbOutputCurrent = s_tReg->Ac115IbCurrentSet>0 ? s_tReg->Ac115IbCurrentSet : s_tReg->Ac115VbOutputCurrent;
		s_tReg->Ac115VcOutputCurrent = s_tReg->Ac115IcCurrentSet>0 ? s_tReg->Ac115IcCurrentSet : s_tReg->Ac115VcOutputCurrent;
		
		if(s_tReg->Dc28V1CurrentCompensate>0){
			s_tReg->Dc28V1OutputCurrent += s_tReg->Dc28V1CurrentCompensate;
		}else{
			s_tReg->Dc28V1OutputCurrent = s_tReg->Dc28V1CurrentSet>0 ? s_tReg->Dc28V1CurrentSet : s_tReg->Dc28V1OutputCurrent;
		}
		
		if(s_tReg->Dc28V2CurrentCompensate>0){
			s_tReg->Dc28V2OutputCurrent += s_tReg->Dc28V2CurrentCompensate;
		}else{
			s_tReg->Dc28V2OutputCurrent = s_tReg->Dc28V2CurrentSet>0 ? s_tReg->Dc28V2CurrentSet : s_tReg->Dc28V2OutputCurrent;
		}
		
		//统计开了多少个分路
		for(s=0; s<6; s++){
			if(dcControl & n<<(s*2)){
				dc1ShuntCount++;
			}
			if(dcControl & n<<(s*2+1)){
				dc2ShuntCount++;
			}
		}
		//计算分路电流
		dc1ShuntCurrent = dc1ShuntCount>0 ? s_tReg->Dc28V1OutputCurrent/dc1ShuntCount : 0;
		dc2ShuntCurrent = dc2ShuntCount>0 ? s_tReg->Dc28V2OutputCurrent/dc2ShuntCount : 0;
		//分路电流复制
		for(s=0; s<6; s++){
			if(dcControl & n<<(s*2)){
				switch(s+1){
					case 1:
						s_tReg->Dc28V1Ch1OutputCurrent = dc1ShuntCurrent;
						break;
					case 2:
						s_tReg->Dc28V1Ch2OutputCurrent = dc1ShuntCurrent;
						break;
					case 3:
						s_tReg->Dc28V1Ch3OutputCurrent = dc1ShuntCurrent;
						break;
					case 4:
						s_tReg->Dc28V1Ch4OutputCurrent = dc1ShuntCurrent;
						break;
					case 5:
						s_tReg->Dc28V1Ch5OutputCurrent = dc1ShuntCurrent;
						break;
					case 6:
						s_tReg->Dc28V1Ch6OutputCurrent = dc1ShuntCurrent;
						break;
				}
			}
			if(dcControl & n<<(s*2+1)){
				switch(s+1){
					case 1:
						s_tReg->Dc28V2Ch1OutputCurrent = dc2ShuntCurrent;
						break;
					case 2:
						s_tReg->Dc28V2Ch2OutputCurrent = dc2ShuntCurrent;
						break;
					case 3:
						s_tReg->Dc28V2Ch3OutputCurrent = dc2ShuntCurrent;
						break;
					case 4:
						s_tReg->Dc28V2Ch4OutputCurrent = dc2ShuntCurrent;
						break;
					case 5:
						s_tReg->Dc28V2Ch5OutputCurrent = dc2ShuntCurrent;
						break;
					case 6:
						s_tReg->Dc28V2Ch6OutputCurrent = dc2ShuntCurrent;
						break;
				}
			}
		}
		#endif
}

