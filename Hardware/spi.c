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
#define SAMPL_COUNT	100					//采样次数
#define SAMPL_LOSS_COUNT	20			//丢弃的数据个数

static T_SPI_DATA spiData[SAMPL_COUNT] = {0};
static T_SPI_DATA spiTransientData={0};
static T_SPI_DATA spiSteadyData={0};
static uint8_t count = 0;

//冒泡排序的函数
void BubbleSort(T_SPI_DATA *arr,	int arrLen){
	
	int j,i;
	int t;//临时变量	
		//因为每轮排序几乎一样，因此，我们可以使用for循环处理
	for(i=0;i<arrLen-1;i++){
		for(j=0;j<arrLen-1-i;j++){		
		//如果前面的数大于的后面的数，就交换
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
    rcu_periph_clock_enable(RCU_GPIOF);	//使能PORTF时钟
	
		/* SPI1_CLK(PF7), SPI1_MISO(PF8) and SPI1_MOSI(PF9) GPIO pin configuration */
		//配置PF7引脚的模式
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_7);//配置为复用上拉模式
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_7);//配置为推挽输出，速度为50M
		//配置PF9引脚的模式
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_9);//配置为复用上拉模式
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_9);//配置为推挽输出，速度为50M
		
		//配置PF8引脚的模式
		gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_8);//配置为复用上拉模式
		/* SPI0_CS(PF6) GPIO pin configuration */
		//配置PF6引脚的模式
		gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_6);//配置为复用上拉模式
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_6);//配置为推挽输出，速度为50M 
	
		//配置PF10引脚的模式
		gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_10);//配置为复用上拉模式
		gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ/*GPIO_OSPEED_50MHZ*/,GPIO_PIN_10);//配置为推挽输入，速度为50M
		
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
名称：SPI_Send(unsigned char data) 
功能：发送SPI数据 
参数：unsigned char data 
时间：2011.1.11 
版本：1.0 
注意：无 
*******************************************************************************/  
void SPI_Send(unsigned char data)  
{  
    unsigned char i;  
    SPI_CS_L;       //拉低片选信号  
    SPI_CLK_L;      //时钟空闲时为低电平   
    SPI_MOSI_L;  
    __NOP(); 
    for(i = 0;i < 8;i++)  
    {  
        if(data&(0x80 >> i))//高位在前，低位在前改为(0x01<<i)  
            SPI_MOSI_H;  
        else  
            SPI_MOSI_L;  
        __NOP(); 
        SPI_CLK_H;      //在上升沿更新数据  
        __NOP(); 
        SPI_CLK_L;  
    }  
    __NOP(); 
    SPI_CS_H;       //拉高片选，完成一次数据传输  
}   
/******************************************************************************* 
名称：unsigned char SPI_Get()  
功能：接收SPI数据 
参数：返回data 
时间：2011.1.11 
版本：1.0 
注意：无 
*******************************************************************************/  
unsigned int SPI_Get()   
{  
    unsigned char i;  
    unsigned int data=0x000;  
    SPI_CS_L;       //拉低片选信号  
    SPI_CLK_L;      //时钟空闲时为低电平   
    SPI_MOSI_L;  
    __NOP(); 
    for(i = 0;i < 12;i++)//读取12位ad值  
    {  
        if(GET_SPI_MISO)  
            data |= (0x800 >> i);  
        __NOP(); 
        SPI_CLK_H;      //在上升沿更新数据  
        __NOP(); 
        SPI_CLK_L;  
    }  
    __NOP(); 
    SPI_CS_H;       //拉高片选，完成一次数据传输  
    return data;  
}


/*******************************************************************************
* 函 数 名         : read2543
* 函数功能		     : TLC2543驱动模块
* 输    入         : port		通道号
* 输    出         : ad			转换值
* 说    明         ：请结合TLC2543芯片手册和下方注释理解
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
    port	<<= 4;                          /*选通道。高四位代表AD通道，低四位自动补0 */
		port  &= 0xf0;
    /*这里的for，其实就算_CS变低后，时钟IO_Clock和Data_Input使能，Data_Out脱离高阻状态。
     * 12个时钟信号依次输入。随着时钟信号的输入，控制字从Data_Input一位一位地在时钟信号上升沿时
     * 送入TLC2543(注意：高位先入)，这里的控制字是通道选择(port)，从A0-A10共11个通道，
     * （分别对应0000至1010，高四位就是存放模拟通道输入选择的数据）
     * 同时，上一周期转换的AD数据，即输出数据寄存器中的数据从Data_Out一位一位地移出（下降沿时）
     * （第一次_CS=0时输出第一位，其他的跟着for内的下降沿输出）*/

    for ( i = 0; i < 12; i++ )              /* 进行12次（12位）的数据推送 */
    {
        if(GET_SPI_MISO)
            ad |= 0x01;             /* 相当于每次检出输出1时。最低位就给1，否则给0 */
				
        if(port & 0x80)  /* 相当于只取最高位进行与运算 */
				{SPI_MOSI_H;}
				else
				{SPI_MOSI_L;}
				
				Delay_AD(SPI_BUS_DELAY);
        SPI_CLK_H;                   /* 电平抬高 */
        Delay_AD(SPI_BUS_DELAY);
        SPI_CLK_L;;                      /* 给低电平 */
        Delay_AD(SPI_BUS_DELAY);                    /* 延时。这里是给一个完整周期的脉冲 */
        port	<<= 1;
        ad	<<= 1;                  /* 左移一位，为下一次for循环做准备 */
    }
		
		Delay_AD(SPI_BUS_DELAY);
    SPI_CS_H;                            /* 片选端置高，则IO_Clock和Data_Input禁止，Data_Out高阻，EOC置高 */
    ad	>>= 1;                          /*上面最后一次for循环多移了一次现在移回来 */
    return(ad);                             /* 返回转换值 */
}


/******************************************************************************* 
名称：unsigned int Read_SPI(unsigned char chan) 
功能：读取选定通道上的AD值 
参数：输入参数为需要读取的通道，返回为AD值 
时间：
版本：1.0 
注意：
*******************************************************************************/  
unsigned int Read_SPI(unsigned char chan)  
{  
    unsigned int adc_data;  
		adc_data = read2543(chan);
    return adc_data;  
}  

/******************************************************************************* 
名称：unsigned int Read_SPI(void) 
功能：读取所有通道上的AD值 
参数：返回为11个通道上ADC值 
时间：
版本：1.0 
注意：
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
	*ADC采集的数据滤波
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
	//取中间USE_DATA_COUNT次采集的数据冒泡排序
	//BubbleSort(&spiData[0], SAMPL_COUNT-0);
#endif
	//去除头尾的2个数据，剩下的2个作为有效值
	for(i=SAMPL_LOSS_COUNT; i<SAMPL_COUNT; i++)
	{
		//取最大值
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
		
		//取平均值
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
	Lpf_Run(channel, tmp, &spiSteadyData);		//一阶滤波	by bruce
	
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
	
//	//去除零漂
//	switch(channel){
//		case 0:
//			//AC 115V 总输出电压--(A,B,C相)
//			if(spiSteadyData.Data0<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data0=0;
//			if(spiSteadyData.Data1<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data1=0;
//			if(spiSteadyData.Data2<AC_115V_OUTU_ALL_ZERO)
//				spiSteadyData.Data2=0;
//			
//			//AC 115V 总输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 1:
//			//AC 115V CH1输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 2:
//			//AC 115V CH2输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 3:
//			//AC 115V CH3输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 4:
//			//AC 115V CH4输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 5:
//			//AC 115V CH5输出电流--(A,B,C相)
//			if(spiSteadyData.Data3<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data3=0;
//			if(spiSteadyData.Data4<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data4=0;
//			if(spiSteadyData.Data5<AC_115V_OUTI_ZERO)
//				spiSteadyData.Data5=0;
//			break;
//		case 6:
//			//AC 115V CH6输出电流--(A,B,C相)
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
	*获取SPI读到的数据
	*
	*/
T_SPI_DATA* getSpiData()
{
	return spiData;
}

/**
	*获取ADC采集的瞬时值
	*
	*/
T_SPI_DATA GetSpiTransientData()
{
	return spiTransientData;
}

/**
	*获取ADC采集的稳态值
	*
	*/
T_SPI_DATA GetSpiSteadyData()
{
	return spiSteadyData;
}


/**
	*清空ADC采集的稳态值
	*
	*/
void ClearSpiSteadyData()
{
	memset(&spiSteadyData, 0 ,sizeof(T_SPI_DATA));
}

