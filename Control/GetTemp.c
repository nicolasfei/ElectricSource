#include "GetTemp.h"

static TEMP_VALUE tTempValue;

void TEMP1_OUT_DQ(void)
{  
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);
}

void TEMP1_IN_DQ(void)   
{
		gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_4);
}

void TEMP1_CLR_DQ(void)  
{
		gpio_bit_reset(GPIOC,GPIO_PIN_4);
}

void TEMP1_SET_DQ(void)  
{
		gpio_bit_set(GPIOC,GPIO_PIN_4);
}
 
unsigned char TEMP1_GET_DQ(void)
{
		return gpio_input_bit_get(GPIOC,GPIO_PIN_4);
}

void TEMP2_OUT_DQ(void)
{  
		gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);
		gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);
}

void TEMP2_IN_DQ(void)   
{
		gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_5);
}

void TEMP2_CLR_DQ(void)  
{
		gpio_bit_reset(GPIOC,GPIO_PIN_5);
}

void TEMP2_SET_DQ(void)  
{
		gpio_bit_set(GPIOC,GPIO_PIN_5);
}
 
unsigned char TEMP2_GET_DQ(void)
{
		return gpio_input_bit_get(GPIOC,GPIO_PIN_5);
}

void _delay_us(unsigned short us)
{
	uint32_t dy = us*72;
	while(--dy);
}

//-----复位-----
void ResetOnewire(TEMP_DQ *ptTemp_DQ) 
{
	ptTemp_DQ->TEMP_OUT_DQ();
	ptTemp_DQ->TEMP_CLR_DQ();
	_delay_us(750);
	ptTemp_DQ->TEMP_SET_DQ();
	_delay_us(15);//(100);
	ptTemp_DQ->TEMP_IN_DQ(); 
	while(!(ptTemp_DQ->TEMP_GET_DQ()));
	ptTemp_DQ->TEMP_SET_DQ();
}

//-----读数据-----
unsigned char ReadOnewire(TEMP_DQ *ptTemp_DQ)
{
	unsigned char data=0,i=0;
	 for(i=0;i<8;i++)
	{
		data=data>>1;
		ptTemp_DQ->TEMP_OUT_DQ();
		ptTemp_DQ->TEMP_CLR_DQ();
		ptTemp_DQ->TEMP_IN_DQ();
		if(ptTemp_DQ->TEMP_GET_DQ()) data|=0x80;
		else while(!(ptTemp_DQ->TEMP_GET_DQ()));
		_delay_us(60);
	}
	return(data);
}

//-----写数据-----
void WriteOnewire(TEMP_DQ *ptTemp_DQ,unsigned char data)
{
	unsigned char i=0;
	ptTemp_DQ->TEMP_OUT_DQ();
	for(i=0;i<8;i++)
	{
			ptTemp_DQ->TEMP_CLR_DQ();
			if(data&0x01)
			{
					ptTemp_DQ->TEMP_SET_DQ();
			}
			else
			{
					ptTemp_DQ->TEMP_CLR_DQ();
			}
			data=data>>1;
			_delay_us(60);  //65
			ptTemp_DQ->TEMP_SET_DQ();
	}
}

//------------DS18BB0读温度----------
TEMP_VALUE GetTempTask(unsigned char Chan) 
{ 
		short temp1=0,temp2=0;
		TEMP_DQ tTemp_DQ[2] = {
				{TEMP1_OUT_DQ,TEMP1_IN_DQ,TEMP1_CLR_DQ,TEMP1_SET_DQ,TEMP1_GET_DQ},
				{TEMP2_OUT_DQ,TEMP2_IN_DQ,TEMP2_CLR_DQ,TEMP2_SET_DQ,TEMP2_GET_DQ}
		};

		ResetOnewire(&tTemp_DQ[Chan]); 
		WriteOnewire(&tTemp_DQ[Chan],0xcc); 
		WriteOnewire(&tTemp_DQ[Chan],0x44);
		ResetOnewire(&tTemp_DQ[Chan]); 
		WriteOnewire(&tTemp_DQ[Chan],0xcc); 
		WriteOnewire(&tTemp_DQ[Chan],0xbe); 	
		temp1 = ReadOnewire(&tTemp_DQ[Chan]); 
		temp2 = ReadOnewire(&tTemp_DQ[Chan]); 
		if(0 == Chan)
		{
				tTempValue.Temp1 = ((temp2 << 8) | temp1)*0.0625;
		}
		else
		{
				tTempValue.Temp2 = ((temp2 << 8) | temp1)*0.0625;
		}
		return tTempValue;
}

TEMP_VALUE* ReadTemp(void)
{
		return &tTempValue;
}	








