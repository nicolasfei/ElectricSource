#include "gd32f4xx.h"
#include "spi.h"
#include "stdio.h"
#include "string.h"
#include "GetAdc.h"

#define SPI_CS_H     gpio_bit_set(GPIOF,GPIO_PIN_6)  
#define SPI_CS_L     gpio_bit_reset(GPIOF,GPIO_PIN_6)
#define SPI_CLK_H    gpio_bit_set(GPIOF,GPIO_PIN_7)  
#define SPI_CLK_L    gpio_bit_reset(GPIOF,GPIO_PIN_7)
#define SPI_MOSI_H   gpio_bit_set(GPIOF,GPIO_PIN_9)  
#define SPI_MOSI_L   gpio_bit_reset(GPIOF,GPIO_PIN_9)
#define GET_SPI_MISO gpio_input_bit_get(GPIOF,GPIO_PIN_8)  

#define SAMPL_TIMES	(10)

#define ONE_LPF		0
#define USE_SORT	1
#define USE_DATA_COUNT	2
#define SAMPL_COUNT	100					//��������
#define SAMPL_LOSS_COUNT	20			//���������ݸ���

static T_SPI_DATA spiData[SAMPL_COUNT] = {0};
static T_SPI_DATA spiTransientData={0};
static T_SPI_DATA spiSteadyData={0};
static uint8_t count = 0;

//ð������ĺ���
void BubbleSort(T_SPI_DATA *arr,	int arrLen){
	
	int j,i;
	int t;//��ʱ����	
		//��Ϊÿ�����򼸺�һ������ˣ����ǿ���ʹ��forѭ������
	for(i=0;i<arrLen-1;i++){
		for(j=0;j<arrLen-1-i;j++){		
		//���ǰ��������ڵĺ���������ͽ���
		if(arr[j].Data0>arr[j+1].Data0){
			t = arr[j].Data0;
			arr[j].Data0 = arr[j+1].Data0;
			arr[j+1].Data0 = t;
			}
		
		if(arr[j].Data1>arr[j+1].Data1){
			t = arr[j].Data1;
			arr[j].Data1 = arr[j+1].Data1;
			arr[j+1].Data1 = t;
			}
	
		if(arr[j].Data2>arr[j+1].Data2){
			t = arr[j].Data2;
			arr[j].Data2 = arr[j+1].Data2;
			arr[j+1].Data2 = t;
			}

		if(arr[j].Data3>arr[j+1].Data3){
			t = arr[j].Data3;
			arr[j].Data3 = arr[j+1].Data3;
			arr[j+1].Data3 = t;
			}
		
		if(arr[j].Data4>arr[j+1].Data4){
			t = arr[j].Data4;
			arr[j].Data4 = arr[j+1].Data4;
			arr[j+1].Data4 = t;
			}
		
		if(arr[j].Data5>arr[j+1].Data5){
			t = arr[j].Data5;
			arr[j].Data5 = arr[j+1].Data5;
			arr[j+1].Data5 = t;
			}
		
		if(arr[j].Data6>arr[j+1].Data6){
			t = arr[j].Data6;
			arr[j].Data6 = arr[j+1].Data6;
			arr[j+1].Data6 = t;
			}
		
		if(arr[j].Data7>arr[j+1].Data7){
			t = arr[j].Data7;
			arr[j].Data7 = arr[j+1].Data7;
			arr[j+1].Data7 = t;
			}
		
		if(arr[j].Data8>arr[j+1].Data8){
			t = arr[j].Data8;
			arr[j].Data8 = arr[j+1].Data8;
			arr[j+1].Data8 = t;
			}
		
		if(arr[j].Data9>arr[j+1].Data9){
			t = arr[j].Data9;
			arr[j].Data9 = arr[j+1].Data9;
			arr[j+1].Data9 = t;
			}
		
		if(arr[j].Data10>arr[j+1].Data10){
			t = arr[j].Data10;
			arr[j].Data10 = arr[j+1].Data10;
			arr[j+1].Data10 = t;
			}
		}
	}
}

/*******************************************************************************
* function name  : SPI1_Init
* brief          : SPI1 initialize
* param[in]      : None
* param[out]     : None
* retval         : None
* attention      : None
*******************************************************************************/
void XL2543_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOF);	//ʹ��PORTFʱ��
	
		/* SPI1_CLK(PF7), SPI1_MISO(PF8) and SPI1_MOSI(PF9) GPIO pin configuration */
		//����PF7���ŵ�ģʽ
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_7);//����Ϊ��������ģʽ
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_7);//����Ϊ����������ٶ�Ϊ50M
		//����PF9���ŵ�ģʽ
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_9);//����Ϊ��������ģʽ
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_9);//����Ϊ����������ٶ�Ϊ50M
		
		//����PF8���ŵ�ģʽ
		gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_8);//����Ϊ��������ģʽ
		/* SPI0_CS(PF6) GPIO pin configuration */
		//����PF6���ŵ�ģʽ
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_6);//����Ϊ��������ģʽ
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_6);//����Ϊ����������ٶ�Ϊ50M 
	
		//����PF10���ŵ�ģʽ
		gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_10);//����Ϊ��������ģʽ
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_10);//����Ϊ�������룬�ٶ�Ϊ50M
		
		SPI_CS_H;
		SPI_CLK_L;
}


void Delay_AD(volatile unsigned int time)
{  
		unsigned short i;
		while(time--) 
		{ 
				for(i=0;i<8;i++);
		}
}

/******************************************************************************* 
���ƣ�SPI_Send(unsigned char data) 
���ܣ�����SPI���� 
������unsigned char data 
ʱ�䣺2011.1.11 
�汾��1.0 
ע�⣺�� 
*******************************************************************************/  
void SPI_Send(unsigned char data)  
{  
    unsigned char i;  
    SPI_CS_L;       //����Ƭѡ�ź�  
    SPI_CLK_L;      //ʱ�ӿ���ʱΪ�͵�ƽ   
    SPI_MOSI_L;  
    __NOP(); 
    for(i = 0;i < 8;i++)  
    {  
        if(data&(0x80 >> i))//��λ��ǰ����λ��ǰ��Ϊ(0x01<<i)  
            SPI_MOSI_H;  
        else  
            SPI_MOSI_L;  
        __NOP(); 
        SPI_CLK_H;      //�������ظ�������  
        __NOP(); 
        SPI_CLK_L;  
    }  
    __NOP(); 
    SPI_CS_H;       //����Ƭѡ�����һ�����ݴ���  
}   
/******************************************************************************* 
���ƣ�unsigned char SPI_Get()  
���ܣ�����SPI���� 
����������data 
ʱ�䣺2011.1.11 
�汾��1.0 
ע�⣺�� 
*******************************************************************************/  
unsigned int SPI_Get()   
{  
    unsigned char i;  
    unsigned int data=0x000;  
    SPI_CS_L;       //����Ƭѡ�ź�  
    SPI_CLK_L;      //ʱ�ӿ���ʱΪ�͵�ƽ   
    SPI_MOSI_L;  
    __NOP(); 
    for(i = 0;i < 12;i++)//��ȡ12λadֵ  
    {  
        if(GET_SPI_MISO)  
            data |= (0x800 >> i);  
        __NOP(); 
        SPI_CLK_H;      //�������ظ�������  
        __NOP(); 
        SPI_CLK_L;  
    }  
    __NOP(); 
    SPI_CS_H;       //����Ƭѡ�����һ�����ݴ���  
    return data;  
}


/*******************************************************************************
* �� �� ��         : read2543
* ��������		     : TLC2543����ģ��
* ��    ��         : port		ͨ����
* ��    ��         : ad			ת��ֵ
* ˵    ��         ������TLC2543оƬ�ֲ���·�ע�����
*******************************************************************************/
#define SPI_BUS_DELAY	6
unsigned int read2543(unsigned char port)
{
		while(!XL2543_EOC_STATUS_GET){
		};
    unsigned int ad = 0, i;
		Delay_AD(SPI_BUS_DELAY);
    SPI_CLK_L;
		Delay_AD(SPI_BUS_DELAY);
    SPI_CS_L;
		Delay_AD(SPI_BUS_DELAY);
    port	<<= 4;                          /*ѡͨ��������λ����ADͨ��������λ�Զ���0 */
		port  &= 0xf0;
    /*�����for����ʵ����_CS��ͺ�ʱ��IO_Clock��Data_Inputʹ�ܣ�Data_Out�������״̬��
     * 12��ʱ���ź��������롣����ʱ���źŵ����룬�����ִ�Data_Inputһλһλ����ʱ���ź�������ʱ
     * ����TLC2543(ע�⣺��λ����)������Ŀ�������ͨ��ѡ��(port)����A0-A10��11��ͨ����
     * ���ֱ��Ӧ0000��1010������λ���Ǵ��ģ��ͨ������ѡ������ݣ�
     * ͬʱ����һ����ת����AD���ݣ���������ݼĴ����е����ݴ�Data_Outһλһλ���Ƴ����½���ʱ��
     * ����һ��_CS=0ʱ�����һλ�������ĸ���for�ڵ��½��������*/

    for ( i = 0; i < 12; i++ )              /* ����12�Σ�12λ������������ */
    {
        if(GET_SPI_MISO)
            ad |= 0x01;             /* �൱��ÿ�μ�����1ʱ�����λ�͸�1�������0 */
				
        if(port & 0x80)  /* �൱��ֻȡ���λ���������� */
				{SPI_MOSI_H;}
				else
				{SPI_MOSI_L;}
				
				Delay_AD(SPI_BUS_DELAY);
        SPI_CLK_H;                   /* ��ƽ̧�� */
        Delay_AD(SPI_BUS_DELAY);
        SPI_CLK_L;;                      /* ���͵�ƽ */
        Delay_AD(SPI_BUS_DELAY);                    /* ��ʱ�������Ǹ�һ���������ڵ����� */
        port	<<= 1;
        ad	<<= 1;                  /* ����һλ��Ϊ��һ��forѭ����׼�� */
    }
		
		Delay_AD(SPI_BUS_DELAY);
    SPI_CS_H;                            /* Ƭѡ���øߣ���IO_Clock��Data_Input��ֹ��Data_Out���裬EOC�ø� */
    ad	>>= 1;                          /*�������һ��forѭ��������һ�������ƻ��� */
    return(ad);                             /* ����ת��ֵ */
}


/******************************************************************************* 
���ƣ�unsigned int Read_SPI(unsigned char chan) 
���ܣ���ȡѡ��ͨ���ϵ�ADֵ 
�������������Ϊ��Ҫ��ȡ��ͨ��������ΪADֵ 
ʱ�䣺
�汾��1.0 
ע�⣺
*******************************************************************************/  
unsigned int Read_SPI(unsigned char chan)  
{  
    unsigned int adc_data;  
		adc_data = read2543(chan);
    return adc_data;  
}  

/******************************************************************************* 
���ƣ�unsigned int Read_SPI(void) 
���ܣ���ȡ����ͨ���ϵ�ADֵ 
����������Ϊ11��ͨ����ADCֵ 
ʱ�䣺
�汾��1.0 
ע�⣺
*******************************************************************************/  
#define SPI_READ_INTERVAL 1
T_SPI_DATA *ptSpiData;
void Read_SPI_All()  
{  
		ptSpiData = &spiData[count++];
		#if 1
		ptSpiData->Data0  = read2543(1);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data1  = read2543(2);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data2  = read2543(3);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data3  = read2543(4);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data4  = read2543(5);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data5  = read2543(6);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data6  = read2543(7);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data7  = read2543(8);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data8  = read2543(9);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data9  = read2543(10);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data10 = read2543(0);
		Delay_AD(SPI_READ_INTERVAL);
		#else
		ptSpiData->Data0  = read2543(0);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data1  = read2543(1);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data2  = read2543(2);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data3  = read2543(3);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data4  = read2543(4);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data5  = read2543(5);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data6  = read2543(6);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data7  = read2543(7);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data8  = read2543(8);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data9  = read2543(9);
		Delay_AD(SPI_READ_INTERVAL);
		ptSpiData->Data10 = read2543(10);
		Delay_AD(SPI_READ_INTERVAL);
		#endif
} 

/**
	*ADC�ɼ��������˲�
	*
	*/
void FilterSpiData()
{
	int i=0;
	T_SPI_DATA tmp;
	memset(&tmp, 0, sizeof(T_SPI_DATA));
	memset(&spiTransientData, 0, sizeof(T_SPI_DATA));
	
	float factor[11] = {0};
	float B[11] = {0};
	switch(GetChannelID()){
		case 0:
			factor[0] = factor[1] = factor[2] = AC_115V_OUTV_ALL_FACTOR;
			factor[3] = factor[4] = factor[5] = AC_115V_OUTI_ALL_FACTOR;
			factor[6] = DC_28V1_OUTV_FACTOR;
			factor[7] = DC_28V1_OUTI_FACTOR;
			factor[8] = DC_28V2_OUTV_FACTOR;
			factor[9] = DC_28V2_OUTI_FACTOR;
			factor[10]=0;
		
			B[0] = B[1] = B[2] = AC_115V_OUTV_ALL_B;
			B[3] = B[4] = B[5] = AC_115V_OUTI_ALL_B;
			B[6] = DC_28V1_OUTV_B;
			B[7] = DC_28V1_OUTI_B;
			B[8] = DC_28V2_OUTV_B;
			B[9] = DC_28V2_OUTI_B;
			B[10]=0;
			break;
		case 1:
		case 2:
		case 3:
			factor[0] = factor[1] = factor[2] = AC_115V_OUTV_CHANNEL_FACTOR;
			factor[3] = factor[4] = factor[5] = AC_115V_OUTI_CHANNEL_FACTOR;
			factor[6] = DC_28V1_OUTV_FACTOR;
			factor[7] = DC_28V1_OUTI_FACTOR;
			factor[8] = DC_28V2_OUTV_FACTOR;
			factor[9] = DC_28V2_OUTI_FACTOR;
			factor[10]=	AC_115V_INV_FACTOR;
		
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			B[3] = AC_115V_OUTI_CHANNEL_A_B;
			B[4] = AC_115V_OUTI_CHANNEL_A_B;
			B[5] = AC_115V_OUTI_CHANNEL_A_B;
			B[6] = DC_28V1_OUTV_CHANNEL_B;
			B[7] = DC_28V1_OUTI_CHANNEL_B;
			B[8] = DC_28V2_OUTV_CHANNEL_B;
			B[9] = DC_28V2_OUTI_CHANNEL_B;
			B[10]=	AC_115V_INV_B;		
			break;
		case 4:
		case 5:
		case 6:
			factor[0] = factor[1] = factor[2] = AC_115V_OUTV_CHANNEL_FACTOR;
			factor[3] = factor[4] = factor[5] = AC_115V_OUTI_CHANNEL_FACTOR;
			factor[6] = DC_28V1_OUTV_FACTOR;
			factor[7] = DC_28V1_OUTI_FACTOR;
			factor[8] = DC_28V2_OUTV_FACTOR;
			factor[9] = DC_28V2_OUTI_FACTOR;
			factor[10]=	AC_115V_INI_FACTOR;
		
			
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			B[3] = AC_115V_OUTI_CHANNEL_A_B;
			B[4] = AC_115V_OUTI_CHANNEL_A_B;
			B[5] = AC_115V_OUTI_CHANNEL_A_B;
			B[6] = DC_28V1_OUTV_CHANNEL_B;
			B[7] = DC_28V1_OUTI_CHANNEL_B;
			B[8] = DC_28V2_OUTV_CHANNEL_B;
			B[9] = DC_28V2_OUTI_CHANNEL_B;
			B[10]=	AC_115V_INI_B;
			break;
		case 7:
			factor[0] = factor[1] = factor[2] = AC_380V_INV_FACTOR;
			factor[3] = factor[4] = factor[5] = AC_380V_INI_FACTOR;
			factor[6] = AC_220V_INV_FACTOR;
			factor[7] = AC_220V_INI_FACTOR;
			factor[8] = DC_28V3_OUTV_FACTOR;
			factor[9] = DC_28V3_OUTI_FACTOR;
			factor[10]=	0;
		
			B[0] = B[1] = B[2] = AC_380V_INV_B;
			B[3] = B[4] = B[5] = AC_380V_INI_B;
			B[6] = AC_220V_INV_B;
			B[7] = AC_220V_INI_B;
			B[8] = DC_28V3_OUTV_B;
			B[9] = DC_28V3_OUTI_B;
			B[10]=	0;
			break;
		default:
			break;
	}
#if USE_SORT
	//ȡ�м�USE_DATA_COUNT�βɼ�������ð������
	//BubbleSort(&spiData[0], SAMPL_COUNT-0);
#endif
	//ȥ��ͷβ��2�����ݣ�ʣ�µ�2����Ϊ��Чֵ
	for(i=SAMPL_LOSS_COUNT; i<SAMPL_COUNT; i++)
	{
		//ȡ���ֵ
		spiTransientData.Data0 = (spiTransientData.Data0>spiData[i].Data0)?(spiTransientData.Data0):(spiData[i].Data0);
		spiTransientData.Data1 = (spiTransientData.Data1>spiData[i].Data1)?(spiTransientData.Data1):(spiData[i].Data1);
		spiTransientData.Data2 = (spiTransientData.Data2>spiData[i].Data2)?(spiTransientData.Data2):(spiData[i].Data2);
		spiTransientData.Data3 = (spiTransientData.Data3>spiData[i].Data3)?(spiTransientData.Data3):(spiData[i].Data3);
		spiTransientData.Data4 = (spiTransientData.Data4>spiData[i].Data4)?(spiTransientData.Data4):(spiData[i].Data4);
		spiTransientData.Data5 = (spiTransientData.Data5>spiData[i].Data5)?(spiTransientData.Data5):(spiData[i].Data5);
		spiTransientData.Data6 = (spiTransientData.Data6>spiData[i].Data6)?(spiTransientData.Data6):(spiData[i].Data6);
		spiTransientData.Data7 = (spiTransientData.Data7>spiData[i].Data7)?(spiTransientData.Data7):(spiData[i].Data7);
		spiTransientData.Data8 = (spiTransientData.Data8>spiData[i].Data8)?(spiTransientData.Data8):(spiData[i].Data8);
		spiTransientData.Data9 = (spiTransientData.Data9>spiData[i].Data9)?(spiTransientData.Data9):(spiData[i].Data9);
		spiTransientData.Data10 = (spiTransientData.Data10>spiData[i].Data10)?(spiTransientData.Data10):(spiData[i].Data10);
		
		//ȡƽ��ֵ
		tmp.Data0 += (spiData[i].Data0);
		tmp.Data1 += (spiData[i].Data1);
		tmp.Data2 += (spiData[i].Data2);
		tmp.Data3 += (spiData[i].Data3);
		tmp.Data4 += (spiData[i].Data4);
		tmp.Data5 += (spiData[i].Data5);
		tmp.Data6 += (spiData[i].Data6);
		tmp.Data7 += (spiData[i].Data7);
		tmp.Data8 += (spiData[i].Data8);
		tmp.Data9 += (spiData[i].Data9);
		tmp.Data10 += (spiData[i].Data10);
	}
	
	spiTransientData.Data0 = spiTransientData.Data0*factor[0]+B[0];
	spiTransientData.Data1 = spiTransientData.Data1*factor[1]+B[1];
	spiTransientData.Data2 = spiTransientData.Data2*factor[2]+B[2];
	spiTransientData.Data3 = spiTransientData.Data3*factor[3]+B[3];
	spiTransientData.Data4 = spiTransientData.Data4*factor[4]+B[4];
	spiTransientData.Data5 = spiTransientData.Data5*factor[5]+B[5];
	spiTransientData.Data6 = spiTransientData.Data6*factor[6]+B[6];
	spiTransientData.Data7 = spiTransientData.Data7*factor[7]+B[7];
	spiTransientData.Data8 = spiTransientData.Data8*factor[8]+B[8];
	spiTransientData.Data9 = spiTransientData.Data9*factor[9]+B[9];
	spiTransientData.Data10 = spiTransientData.Data10*factor[10]+B[10];
	

	tmp.Data0 = tmp.Data0/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data1 = tmp.Data1/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data2 = tmp.Data2/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data3 = tmp.Data3/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data4 = tmp.Data4/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data5 = tmp.Data5/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data6 = tmp.Data6/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data7 = tmp.Data7/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data8 = tmp.Data8/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data9 = tmp.Data9/(SAMPL_COUNT-SAMPL_LOSS_COUNT);
	tmp.Data10 = tmp.Data10/(SAMPL_COUNT-SAMPL_LOSS_COUNT);

#if ONE_LPF
	//channel = GetChannelID();
	Lpf_Run(channel, tmp, &spiSteadyData);		//һ���˲�	by bruce
	
	spiSteadyData.Data0 = (spiSteadyData.Data0*factor[0]+B[0]);///100*100;
	spiSteadyData.Data1 = (spiSteadyData.Data1*factor[1]+B[1]);///100*100;
	spiSteadyData.Data2 = (spiSteadyData.Data2*factor[2]+B[2]);///100*100;
	spiSteadyData.Data3 = (spiSteadyData.Data3*factor[3]+B[3]);///100*100;
	spiSteadyData.Data4 = (spiSteadyData.Data4*factor[4]+B[4]);///100*100;
	spiSteadyData.Data5 = (spiSteadyData.Data5*factor[5]+B[5]);///100*100;
	spiSteadyData.Data6 = (spiSteadyData.Data6*factor[6]+B[6]);///100*100;
	spiSteadyData.Data7 = (spiSteadyData.Data7*factor[7]+B[7]);///100*100;
	spiSteadyData.Data8 = (spiSteadyData.Data8*factor[8]+B[8]);///100*100;
	spiSteadyData.Data9 = (spiSteadyData.Data9*factor[9]+B[9]);///100*100;
	spiSteadyData.Data10 = (spiSteadyData.Data10*factor[10]+B[10]);///100*100;
	
//	//ȥ����Ư
//	switch(channel){
//		case 0:
//			//AC 115V �������ѹ--(A,B,C��)
//			if(spiSteadyData.Data0<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data0=0;
//			if(spiSteadyData.Data1<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data1=0;
//			if(spiSteadyData.Data2<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data2=0;
//			
//			//AC 115V ���������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 1:
//			//AC 115V CH1�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 2:
//			//AC 115V CH2�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 3:
//			//AC 115V CH3�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 4:
//			//AC 115V CH4�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 5:
//			//AC 115V CH5�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 6:
//			//AC 115V CH6�������--(A,B,C��)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 7:
//			break;
//	}
#else
	spiSteadyData.Data0 = (tmp.Data0*factor[0]+B[0]);///100*100;
	spiSteadyData.Data1 = (tmp.Data1*factor[1]+B[1]);///100*100;
	spiSteadyData.Data2 = (tmp.Data2*factor[2]+B[2]);///100*100;
	spiSteadyData.Data3 = (tmp.Data3*factor[3]+B[3]);///100*100;
	spiSteadyData.Data4 = (tmp.Data4*factor[4]+B[4]);///100*100;
	spiSteadyData.Data5 = (tmp.Data5*factor[5]+B[5]);///100*100;
	spiSteadyData.Data6 = (tmp.Data6*factor[6]+B[6]);///100*100;
	spiSteadyData.Data7 = (tmp.Data7*factor[7]+B[7]);///100*100;
	spiSteadyData.Data8 = (tmp.Data8*factor[8]+B[8]);///100*100;
	spiSteadyData.Data9 = (tmp.Data9*factor[9]+B[9]);///100*100;
	spiSteadyData.Data10 = (tmp.Data10*factor[10]+B[10]);///100*100;
#endif

	count = 0;
}

/**
	*��ȡSPI����������
	*
	*/
T_SPI_DATA* getSpiData()
{
	return spiData;
}

/**
	*��ȡADC�ɼ���˲ʱֵ
	*
	*/
T_SPI_DATA GetSpiTransientData()
{
	return spiTransientData;
}

/**
	*��ȡADC�ɼ�����ֵ̬
	*
	*/
T_SPI_DATA GetSpiSteadyData()
{
	return spiSteadyData;
}


/**
	*���ADC�ɼ�����ֵ̬
	*
	*/
void ClearSpiSteadyData()
{
	memset(&spiSteadyData, 0 ,sizeof(T_SPI_DATA));
}

