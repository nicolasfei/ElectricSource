#include "gd32f4xx.h"
#include "spi.h"
#include "stdio.h"
#include "string.h"
#include "GetAdc.h"
#include "DataComm.h"

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
#define ZERO_REDUCE	0
#define USE_DATA_COUNT	2
#define SAMPL_COUNT	100						//采样次数
#define SAMPL_LOSS_FIRST_COUNT	30		//丢弃的前面的数据个数
#define SAMPL_LOSS_END_COUNT	30			//丢弃的后面的数据个数

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

static T_SPI_DATA zero[8] = {0};
//static int zeroCheck[8] = {0};

//根据不同的源（380/220/115）来校准对于的115V电压
void check115OutForDifPower()
{

}

static int ZeroCheckCount = 0;

/**
	*ADC采集的数据滤波
	*
	*/
void FilterSpiData()
{
	int i=0;
	T_REG *s_tReg = ReadReg();
	T_SPI_DATA tmp = {0};
	memset(&tmp, 0, sizeof(T_SPI_DATA));
	memset(&spiTransientData, 0, sizeof(T_SPI_DATA));
	
	float factor[11] = {0};
	float B[11] = {0};
	
#if USE_SORT
	//取中间USE_DATA_COUNT次采集的数据冒泡排序
	BubbleSort(&spiData[0], SAMPL_COUNT-0);
#endif
	//计算数据---（平均法）去除头尾的2个数据，剩下的2个作为有效值
	for(i=SAMPL_LOSS_FIRST_COUNT; i<SAMPL_COUNT - SAMPL_LOSS_END_COUNT; i++)
	{
		//取最大值--求瞬态值
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
		
		//求累加值--求稳态值
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
	
	//取平均值--求稳态值
	tmp.Data0 = tmp.Data0/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data1 = tmp.Data1/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data2 = tmp.Data2/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data3 = tmp.Data3/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data4 = tmp.Data4/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data5 = tmp.Data5/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data6 = tmp.Data6/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data7 = tmp.Data7/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data8 = tmp.Data8/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data9 = tmp.Data9/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	tmp.Data10 = tmp.Data10/(SAMPL_COUNT-SAMPL_LOSS_FIRST_COUNT-SAMPL_LOSS_END_COUNT);
	
	int s_channel = GetChannelID();
	if(ZeroCheckCount<10)			//第一次运行 需要采样零飘值
	{
		zero[s_channel].Data0 = zero[s_channel].Data0 > tmp.Data0 ? zero[s_channel].Data0 : tmp.Data0;
		zero[s_channel].Data1 = zero[s_channel].Data1 > tmp.Data1 ? zero[s_channel].Data1 : tmp.Data1;
		zero[s_channel].Data2 = zero[s_channel].Data2 > tmp.Data2 ? zero[s_channel].Data2 : tmp.Data2;
		zero[s_channel].Data3 = zero[s_channel].Data3 > tmp.Data3 ? zero[s_channel].Data3 : tmp.Data3;
		zero[s_channel].Data4 = zero[s_channel].Data4 > tmp.Data4 ? zero[s_channel].Data4 : tmp.Data4;
		zero[s_channel].Data5 = zero[s_channel].Data5 > tmp.Data5 ? zero[s_channel].Data5 : tmp.Data5;
		zero[s_channel].Data6 = zero[s_channel].Data6 > tmp.Data6 ? zero[s_channel].Data6 : tmp.Data6;
		zero[s_channel].Data7 = zero[s_channel].Data7 > tmp.Data7 ? zero[s_channel].Data7 : tmp.Data7;
		zero[s_channel].Data8 = zero[s_channel].Data8 > tmp.Data8 ? zero[s_channel].Data8 : tmp.Data8;
		zero[s_channel].Data9 = zero[s_channel].Data9 > tmp.Data9 ? zero[s_channel].Data9 : tmp.Data9;
		zero[s_channel].Data10 = zero[s_channel].Data10 > tmp.Data10 ? zero[s_channel].Data10 : tmp.Data10;
//		if(zero[s_channel].Data0 == 0 &&
//				zero[s_channel].Data1 == 0 &&
//				zero[s_channel].Data2 == 0 &&
//				zero[s_channel].Data3 == 0 &&
//				zero[s_channel].Data4 == 0 &&
//				zero[s_channel].Data5 == 0 &&
//				zero[s_channel].Data6 == 0 &&
//				zero[s_channel].Data7 == 0 &&
//				zero[s_channel].Data8 == 0 &&
//				zero[s_channel].Data9 == 0 &&
//				zero[s_channel].Data10 == 0){
//					zeroCheck[s_channel] = 0;
//				}else{
//					zeroCheck[s_channel] = 1;
//				}
		ZeroCheckCount++;
	}else{
	//系数K,B赋值，去除零飘
#if ZERO_REDUCE
switch(s_channel){
		case 4:
			//115V总输出电压
				factor[0] = AC_115V_OUTV_ALL_A_FACTOR;
				B[0] = AC_115V_OUTV_ALL_A_B;
				
				factor[1] = AC_115V_OUTV_ALL_B_FACTOR;
				B[1] = AC_115V_OUTV_ALL_B_B;
				
				factor[2] = AC_115V_OUTV_ALL_C_FACTOR;
				B[2] = AC_115V_OUTV_ALL_C_B;
				
				factor[3] = AC_115V_OUTI_ALL_A_FACTOR;
				B[3] = AC_115V_OUTI_ALL_A_B;
				
				factor[4] = AC_115V_OUTI_ALL_B_FACTOR;
				B[4] = AC_115V_OUTI_ALL_B_B;
				
				factor[5] = AC_115V_OUTI_ALL_C_FACTOR;
				B[5] = AC_115V_OUTI_ALL_C_B;
				
				factor[6] = DC_28V1_OUTV_FACTOR;
				B[6] = DC_28V1_OUTV_B;
				
				factor[7] = DC_28V1_OUTI_ALL_FACTOR;
				B[7] = DC_28V1_OUTI_B;
				
				factor[8] = DC_28V2_OUTV_FACTOR;
				B[8] = DC_28V2_OUTV_B;
				
				factor[9] = DC_28V2_OUTI_ALL_FACTOR;
				B[9] = DC_28V2_OUTI_B;
				
				factor[10]=	DC_FAN_I_FACTOR;
				B[10]= DC_FAN_I_B;
				
			break;
		case 6:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH1_A_FACTOR;
				B[3] = AC_115V_OUTI_CH1_A_B;
				
				factor[4] = AC_115V_OUTI_CH1_B_FACTOR;
				B[4] = AC_115V_OUTI_CH1_B_B;
				
				factor[5] = AC_115V_OUTI_CH1_C_FACTOR;
				B[5] = AC_115V_OUTI_CH1_C_B;
				
				factor[6] = DC_28V1_OUTV_CH1_FACTOR;
				B[6] = DC_28V1_OUTV_CH1_B;
				
				factor[7] = DC_28V1_OUTI_CH1_FACTOR;
				B[7] = DC_28V1_OUTI_CH1_B;
				
				factor[8] = DC_28V2_OUTV_CH1_FACTOR;
				B[8] = DC_28V2_OUTV_CH1_B;
				
				factor[9] = DC_28V2_OUTI_CH1_FACTOR;
				B[9] = DC_28V2_OUTI_CH1_B;
				
				factor[10]=	AC_115V_INV_A_FACTOR;
				B[10]=	AC_115V_INV_A_B;		
				
			break;
		case 7:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH2_A_FACTOR;
				B[3] = AC_115V_OUTI_CH2_A_B;
				
				factor[4] = AC_115V_OUTI_CH2_B_FACTOR;
				B[4] = AC_115V_OUTI_CH2_B_B;
				
				factor[5] = AC_115V_OUTI_CH2_C_FACTOR;
				B[5] = AC_115V_OUTI_CH2_C_B;
				
				factor[6] = DC_28V1_OUTV_CH2_FACTOR;
				B[6] = DC_28V1_OUTV_CH2_B;
				
				factor[7] = DC_28V1_OUTI_CH2_FACTOR;
				B[7] = DC_28V1_OUTI_CH2_B;
				
				factor[8] = DC_28V2_OUTV_CH2_FACTOR;
				B[8] = DC_28V2_OUTV_CH2_B;
				
				factor[9] = DC_28V2_OUTI_CH2_FACTOR;
				B[9] = DC_28V2_OUTI_CH2_B;
				
				factor[10]=	AC_115V_INV_B_FACTOR;
				B[10]=	AC_115V_INV_B_B;		
				
			break;
		case 5:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH3_A_FACTOR;
				B[3] = AC_115V_OUTI_CH3_A_B;
				
				factor[4] = AC_115V_OUTI_CH3_B_FACTOR;
				B[4] = AC_115V_OUTI_CH3_B_B;
				
				factor[5] = AC_115V_OUTI_CH3_C_FACTOR;
				B[5] = AC_115V_OUTI_CH3_C_B;
				
				factor[6] = DC_28V1_OUTV_CH3_FACTOR;
				B[6] = DC_28V1_OUTV_CH3_B;
				
				factor[7] = DC_28V1_OUTI_CH3_FACTOR;
				B[7] = DC_28V1_OUTI_CH3_B;
				
				factor[8] = DC_28V2_OUTV_CH3_FACTOR;
				B[8] = DC_28V2_OUTV_CH3_B;
				
				factor[9] = DC_28V2_OUTI_CH3_FACTOR;
				B[9] = DC_28V2_OUTI_CH3_B;
				
				factor[10]=	AC_115V_INV_C_FACTOR;
				B[10]=	AC_115V_INV_C_B;		
				
			break;
		case 0:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH4_A_FACTOR;
				B[3] = AC_115V_OUTI_CH4_A_B;
				
				factor[4] = AC_115V_OUTI_CH4_B_FACTOR;
				B[4] = AC_115V_OUTI_CH4_B_B;
				
				factor[5] = AC_115V_OUTI_CH4_C_FACTOR;
				B[5] = AC_115V_OUTI_CH4_C_B;
				
				factor[6] = DC_28V1_OUTV_CH4_FACTOR;
				B[6] = DC_28V1_OUTV_CH4_B;
		
				factor[7] = DC_28V1_OUTI_CH4_FACTOR;
				B[7] = DC_28V1_OUTI_CH4_B;
				
				factor[8] = DC_28V2_OUTV_CH4_FACTOR;
				B[8] = DC_28V2_OUTV_CH4_B;
				
				factor[9] = DC_28V2_OUTI_CH4_FACTOR;
				B[9] = DC_28V2_OUTI_CH4_B;
				
				factor[10]=	AC_115V_INI_A_FACTOR;
				B[10]=	AC_115V_INI_A_B;		
			break;
		case 2:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH5_A_FACTOR;
				B[3] = AC_115V_OUTI_CH5_A_B;
				
				factor[4] = AC_115V_OUTI_CH5_B_FACTOR;
				B[4] = AC_115V_OUTI_CH5_B_B;
				
				factor[5] = AC_115V_OUTI_CH5_C_FACTOR;
				B[5] = AC_115V_OUTI_CH5_C_B;
				
				factor[6] = DC_28V1_OUTV_CH5_FACTOR;
				B[6] = DC_28V1_OUTV_CH5_B;
		
				factor[7] = DC_28V1_OUTI_CH5_FACTOR;
				B[7] = DC_28V1_OUTI_CH5_B;
				
				factor[8] = DC_28V2_OUTV_CH5_FACTOR;
				B[8] = DC_28V2_OUTV_CH5_B;
				
				factor[9] = DC_28V2_OUTI_CH5_FACTOR;
				B[9] = DC_28V2_OUTI_CH5_B;
				
				factor[10]=	AC_115V_INI_B_FACTOR;
				B[10]=	AC_115V_INI_B_B;		
			break;
		case 1:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
		
				factor[3] = AC_115V_OUTI_CH6_A_FACTOR;
				B[3] = AC_115V_OUTI_CH6_A_B;
				
				factor[4] = AC_115V_OUTI_CH6_B_FACTOR;
				B[4] = AC_115V_OUTI_CH6_B_B;
				
				factor[5] = AC_115V_OUTI_CH6_C_FACTOR;
				B[5] = AC_115V_OUTI_CH6_C_B;
				
				factor[6] = DC_28V1_OUTV_CH6_FACTOR;
				B[6] = DC_28V1_OUTV_CH6_B;
		
				factor[7] = DC_28V1_OUTI_CH6_FACTOR;
				B[7] = DC_28V1_OUTI_CH6_B;
				
				factor[8] = DC_28V2_OUTV_CH6_FACTOR;
				B[8] = DC_28V2_OUTV_CH6_B;
				
				factor[9] = DC_28V2_OUTI_CH6_FACTOR;
				B[9] = DC_28V2_OUTI_CH6_B;
				
				factor[10]=	AC_115V_INI_C_FACTOR;
				B[10]=	AC_115V_INI_C_B;		
			break;
		case 3:
				factor[0] = AC_380V_INV_A_FACTOR;
				B[0] = AC_380V_INV_A_B;
				
				factor[1] = AC_380V_INV_B_FACTOR;
				B[1] = AC_380V_INV_B_B;
		
				factor[2] = AC_380V_INV_C_FACTOR;
				B[2] = AC_380V_INV_C_B;
		
				factor[3] = AC_380V_INI_A_FACTOR;
				B[3] = AC_380V_INI_A_B;
				
				factor[4] = AC_380V_INI_B_FACTOR;
				B[4] = AC_380V_INI_B_B;

				factor[5] = AC_380V_INI_C_FACTOR;
				B[5] = AC_380V_INI_C_B;
				
				factor[6] = AC_220V_INV_FACTOR;
				B[6] = AC_220V_INV_B;
		
				factor[7] = AC_220V_INI_FACTOR;
				B[7] = AC_220V_INI_B;
				
				factor[8] = DC_28V3_OUTV_FACTOR;
				B[8] = DC_28V3_OUTV_B;	
				
				factor[9] = DC_28V3_OUTI_FACTOR;
				B[9] = DC_28V3_OUTI_B;
				
			factor[10]=	0;
			B[10]=	0;
			break;
		default:
			break;
	}
#else
	T_REG *rReg = ReadReg();
	switch(s_channel){
		case 4:
			if(rReg->Ac380VaOutputVoltage > 18000 && rReg->Ac380VbOutputVoltage > 18000 && rReg->Ac380VcOutputVoltage > 18000){		//当前是380V输入
					//115V总输出电压
			if(tmp.Data0<AC115U_OUT_ZERO_DRIFT_A){
				factor[0] = 0;
				B[0] = 0;
			}else{
				factor[0] = AC_115V_OUTV_ALL_380_A_FACTOR;
				B[0] = AC_115V_OUTV_ALL_380_A_B;
			}
			if(tmp.Data1<AC115U_OUT_ZERO_DRIFT_B){
				factor[1] = 0;
				B[1] = 0;
			}else{
				factor[1] = AC_115V_OUTV_ALL_380_B_FACTOR;
				B[1] = AC_115V_OUTV_ALL_380_B_B;
			}
			if(tmp.Data2<AC115U_OUT_ZERO_DRIFT_C){
				factor[2] = 0;
				B[2] = 0;
			}else{
				factor[2] = AC_115V_OUTV_ALL_380_C_FACTOR;
				B[2] = AC_115V_OUTV_ALL_380_C_B;
			}
			}else
			if(rReg->Ac115VaInputVoltage > 9000 && rReg->Ac115VbInputVoltage > 9000 && rReg->Ac115VcInputVoltage > 9000){			//当前是115V输入
				//115V总输出电压
			if(tmp.Data0<AC115U_OUT_ZERO_DRIFT_A){
				factor[0] = 0;
				B[0] = 0;
			}else{
				factor[0] = AC_115V_OUTV_ALL_115_A_FACTOR;
				B[0] = AC_115V_OUTV_ALL_115_A_B;
			}
			if(tmp.Data1<AC115U_OUT_ZERO_DRIFT_B){
				factor[1] = 0;
				B[1] = 0;
			}else{
				factor[1] = AC_115V_OUTV_ALL_115_B_FACTOR;
				B[1] = AC_115V_OUTV_ALL_115_B_B;
			}
			if(tmp.Data2<AC115U_OUT_ZERO_DRIFT_C){
				factor[2] = 0;
				B[2] = 0;
			}else{
				factor[2] = AC_115V_OUTV_ALL_115_C_FACTOR;
				B[2] = AC_115V_OUTV_ALL_115_C_B;
			}
			}else
			if(rReg->Ac220VInputVoltage > 20000 ){																																						//当前是220V输入
				//115V总输出电压
			if(tmp.Data0<AC115U_OUT_ZERO_DRIFT_A){
				factor[0] = 0;
				B[0] = 0;
			}else{
				factor[0] = AC_115V_OUTV_ALL_220_A_FACTOR;
				B[0] = AC_115V_OUTV_ALL_220_A_B;
			}
			if(tmp.Data1<AC115U_OUT_ZERO_DRIFT_B){
				factor[1] = 0;
				B[1] = 0;
			}else{
				factor[1] = AC_115V_OUTV_ALL_220_B_FACTOR;
				B[1] = AC_115V_OUTV_ALL_220_B_B;
			}
			if(tmp.Data2<AC115U_OUT_ZERO_DRIFT_C){
				factor[2] = 0;
				B[2] = 0;
			}else{
				factor[2] = AC_115V_OUTV_ALL_220_C_FACTOR;
				B[2] = AC_115V_OUTV_ALL_220_C_B;
			}
			}else{
					//115V总输出电压
			if(tmp.Data0<AC115U_OUT_ZERO_DRIFT_A){
				factor[0] = 0;
				B[0] = 0;
			}else{
				factor[0] = AC_115V_OUTV_ALL_220_A_FACTOR;
				B[0] = AC_115V_OUTV_ALL_220_A_B;
			}
			if(tmp.Data1<AC115U_OUT_ZERO_DRIFT_B){
				factor[1] = 0;
				B[1] = 0;
			}else{
				factor[1] = AC_115V_OUTV_ALL_220_B_FACTOR;
				B[1] = AC_115V_OUTV_ALL_220_B_B;
			}
			if(tmp.Data2<AC115U_OUT_ZERO_DRIFT_C){
				factor[2] = 0;
				B[2] = 0;
			}else{
				factor[2] = AC_115V_OUTV_ALL_220_C_FACTOR;
				B[2] = AC_115V_OUTV_ALL_220_C_B;
			}
			}
			
			//115V总输出电流--在有总电压且分路有输出电压的情况下才显示
			if(tmp.Data0>=AC115U_OUT_ZERO_DRIFT_A && (s_tReg->AcPowerControl & 0x3F) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){
				factor[3] = AC_115V_OUTI_ALL_A_FACTOR;
				B[3] = AC_115V_OUTI_ALL_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(tmp.Data1>=AC115U_OUT_ZERO_DRIFT_B && (s_tReg->AcPowerControl & 0x3F) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){
				factor[4] = AC_115V_OUTI_ALL_B_FACTOR;
				B[4] = AC_115V_OUTI_ALL_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(tmp.Data2>=AC115U_OUT_ZERO_DRIFT_C && (s_tReg->AcPowerControl & 0x3F) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){
				factor[5] = AC_115V_OUTI_ALL_C_FACTOR;
				B[5] = AC_115V_OUTI_ALL_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
		
			//28vDC1总输出电压
			if(tmp.Data6<DC28V1_ZERO_DRIFT){
				factor[6] = 0;
				B[6] = 0;
			}else{
				factor[6] = DC_28V1_OUTV_FACTOR;
				B[6] = DC_28V1_OUTV_B;
			}
			//28vDC1总输出电流--在有总电压且分路有输出电压的情况下才显示
			if(tmp.Data6>=DC28V1_ZERO_DRIFT && (s_tReg->DcPowerControl & 0x555)){
				if(s_tReg->DcPowerControl & 0x15){				//有1，2，3通道打开
					if(s_tReg->DcPowerControl & 0x540){			
						factor[7] = DC_28V1_OUTI_ALL_14_FACTOR;		//1，2，3，4，5，6混合使用
						B[7] = DC_28V1_OUTI_14_B;
					}else{
						factor[7] = DC_28V1_OUTI_ALL_FACTOR;	//只有1，2，3通道打开
						B[7] = DC_28V1_OUTI_B;
					}
				}else{																		//只有4，5，6通道打开
					factor[7] = DC_28V1_OUTI_ALL_4_FACTOR;
					B[7] = DC_28V1_OUTI_4_B;
				}
			}else{
				factor[7] = 0;
				B[7] = 0;
			}
			
			//28vDC2总输出电压
			if(tmp.Data8<DC28V2_ZERO_DRIFT){
				factor[8] = 0;
				B[8] = 0;
			}else{
				factor[8] = DC_28V2_OUTV_FACTOR;
				B[8] = DC_28V2_OUTV_B;
			}
			//28vDC2总输出电流--在有总电压且分路有输出电压的情况下才显示
			if(tmp.Data8>=DC28V2_ZERO_DRIFT && (s_tReg->DcPowerControl & 0xAAA)){
				if(s_tReg->DcPowerControl & 0x2A){						//有1，2，3通道打开
					if(s_tReg->DcPowerControl & 0xA80){			
						factor[9] = DC_28V2_OUTI_ALL_14_FACTOR;		//1，2，3，4，5，6混合使用
						B[9] = DC_28V2_OUTI_14_B;
					}else{
						factor[9] = DC_28V2_OUTI_ALL_FACTOR;			//只有1，2，3通道打开
						B[9] = DC_28V2_OUTI_B;
					}
				}else{																				//只有4，5，6通道打开
					factor[9] = DC_28V2_OUTI_ALL_4_FACTOR;
					B[9] = DC_28V2_OUTI_4_B;
				}
			}else{
				factor[9] = 0;
				B[9] = 0;
			}
			
			//风扇电流
			if(s_tReg->FanControlFeedback<9000){
				factor[10]=	DC_FAN_I_FACTOR;
				B[10]= DC_FAN_I_B;
			}else{
				factor[10]=	0;
				B[10]= 0;
			}
			break;
		case 6:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x1) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH1_A_FACTOR;
				B[3] = AC_115V_OUTI_CH1_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x1) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH1_B_FACTOR;
				B[4] = AC_115V_OUTI_CH1_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x1) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH1_C_FACTOR;
				B[5] = AC_115V_OUTI_CH1_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT	
			(s_tReg->DcPowerControl & 0x1) && 
			#endif
			tmp.Data6 > DC28V1_CH1_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH1_FACTOR;
				B[6] = DC_28V1_OUTV_CH1_B;
				factor[7] = DC_28V1_OUTI_CH1_FACTOR;
				B[7] = DC_28V1_OUTI_CH1_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x2) && 
			#endif
			tmp.Data8 > DC28V2_CH1_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH1_FACTOR;
				B[8] = DC_28V2_OUTV_CH1_B;
				factor[9] = DC_28V2_OUTI_CH1_FACTOR;
				B[9] = DC_28V2_OUTI_CH1_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电压A相
			if(tmp.Data10 >= AC115U_IN_ZERO_DRIFT_A && (rReg->Ac220VInputVoltage < 20000 )){//判断当前不是220V输入)
				factor[10]=	AC_115V_INV_A_FACTOR;
				B[10]=	AC_115V_INV_A_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}
			break;
		case 7:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x2) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH2_A_FACTOR;
				B[3] = AC_115V_OUTI_CH2_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x2) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH2_B_FACTOR;
				B[4] = AC_115V_OUTI_CH2_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x2) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH2_C_FACTOR;
				B[5] = AC_115V_OUTI_CH2_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x4) && 
			#endif
			tmp.Data6 > DC28V1_CH2_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH2_FACTOR;
				B[6] = DC_28V1_OUTV_CH2_B;
				factor[7] = DC_28V1_OUTI_CH2_FACTOR;
				B[7] = DC_28V1_OUTI_CH2_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x8) && 
			#endif
			tmp.Data8 > DC28V2_CH2_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH2_FACTOR;
				B[8] = DC_28V2_OUTV_CH2_B;
				factor[9] = DC_28V2_OUTI_CH2_FACTOR;
				B[9] = DC_28V2_OUTI_CH2_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电压A相
			if(tmp.Data10 >= AC115U_IN_ZERO_DRIFT_B && (rReg->Ac220VInputVoltage < 20000 )){//判断当前不是220V输入)
				factor[10]=	AC_115V_INV_B_FACTOR;
				B[10]=	AC_115V_INV_B_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}	
			break;
		case 5:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x4) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH3_A_FACTOR;
				B[3] = AC_115V_OUTI_CH3_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x4) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH3_B_FACTOR;
				B[4] = AC_115V_OUTI_CH3_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x4) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH3_C_FACTOR;
				B[5] = AC_115V_OUTI_CH3_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x10) && 
			#endif
			tmp.Data6 > DC28V1_CH3_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH3_FACTOR;
				B[6] = DC_28V1_OUTV_CH3_B;
				factor[7] = DC_28V1_OUTI_CH3_FACTOR;
				B[7] = DC_28V1_OUTI_CH3_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x20) && 
			#endif
			tmp.Data8 > DC28V2_CH3_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH3_FACTOR;
				B[8] = DC_28V2_OUTV_CH3_B;
				factor[9] = DC_28V2_OUTI_CH3_FACTOR;
				B[9] = DC_28V2_OUTI_CH3_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电压A相
			if(tmp.Data10 >= AC115U_IN_ZERO_DRIFT_C && (rReg->Ac220VInputVoltage < 20000 )){//判断当前不是220V输入)
				factor[10]=	AC_115V_INV_C_FACTOR;
				B[10]=	AC_115V_INV_C_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}	
			break;
		case 0:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x8) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH4_A_FACTOR;
				B[3] = AC_115V_OUTI_CH4_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x8) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH4_B_FACTOR;
				B[4] = AC_115V_OUTI_CH4_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x8) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH4_C_FACTOR;
				B[5] = AC_115V_OUTI_CH4_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x40) && 
			#endif
			tmp.Data6 > DC28V1_CH4_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH4_FACTOR;
				B[6] = DC_28V1_OUTV_CH4_B;
				factor[7] = DC_28V1_OUTI_CH4_FACTOR;
				B[7] = DC_28V1_OUTI_CH4_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x80) && 
			#endif
			tmp.Data8 > DC28V2_CH4_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH4_FACTOR;
				B[8] = DC_28V2_OUTV_CH4_B;
				factor[9] = DC_28V2_OUTI_CH4_FACTOR;
				B[9] = DC_28V2_OUTI_CH4_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电流A相--有电压才显示电流
			if(s_tReg->Ac115VaInputVoltage > 0){
				factor[10]=	AC_115V_INI_A_FACTOR;
				B[10]=	AC_115V_INI_A_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}
			break;
		case 2:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x10) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH5_A_FACTOR;
				B[3] = AC_115V_OUTI_CH5_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x10) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH5_B_FACTOR;
				B[4] = AC_115V_OUTI_CH5_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x10) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH5_C_FACTOR;
				B[5] = AC_115V_OUTI_CH5_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x100) && 
			#endif
			tmp.Data6 > DC28V1_CH5_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH5_FACTOR;
				B[6] = DC_28V1_OUTV_CH5_B;
				factor[7] = DC_28V1_OUTI_CH5_FACTOR;
				B[7] = DC_28V1_OUTI_CH5_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x200) &&
			#endif
			tmp.Data8 > DC28V2_CH5_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH5_FACTOR;
				B[8] = DC_28V2_OUTV_CH5_B;
				factor[9] = DC_28V2_OUTI_CH5_FACTOR;
				B[9] = DC_28V2_OUTI_CH5_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电流B相--有电压才显示电流
			if(s_tReg->Ac115VbInputVoltage > 0){
				factor[10]=	AC_115V_INI_B_FACTOR;
				B[10]=	AC_115V_INI_B_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}
			break;
		case 1:
			//115V输出CH1电压显示0
			factor[0] = AC_115V_OUTV_CHANNEL_A_FACTOR;
			factor[1] = AC_115V_OUTV_CHANNEL_B_FACTOR;
			factor[2] = AC_115V_OUTV_CHANNEL_C_FACTOR;
			B[0] = AC_115V_OUTV_CHANNEL_A_B;
			B[1] = AC_115V_OUTV_CHANNEL_B_B;
			B[2] = AC_115V_OUTV_CHANNEL_C_B;
			//115v通道电流 在有总电压且分路有输出电压的情况下才显示
			if(s_tReg->Ac115VaOutputVoltage>0 && (s_tReg->AcPowerControl & 0x20) && tmp.Data3 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[3] = AC_115V_OUTI_CH6_A_FACTOR;
				B[3] = AC_115V_OUTI_CH6_A_B;
			}else{
				factor[3] = 0;
				B[3] = 0;
			}
			if(s_tReg->Ac115VbOutputVoltage>0 && (s_tReg->AcPowerControl & 0x20) && tmp.Data4 > AC115I_OUT_ZERO_DRIFT_A){			
				factor[4] = AC_115V_OUTI_CH6_B_FACTOR;
				B[4] = AC_115V_OUTI_CH6_B_B;
			}else{
				factor[4] = 0;
				B[4] = 0;
			}
			if(s_tReg->Ac115VcOutputVoltage>0 && (s_tReg->AcPowerControl & 0x20) && tmp.Data5 > AC115I_OUT_ZERO_DRIFT_A){	
				factor[5] = AC_115V_OUTI_CH6_C_FACTOR;
				B[5] = AC_115V_OUTI_CH6_C_B;
			}else{
				factor[5] = 0;
				B[5] = 0;
			}
			//28vDC1 CH通道电压电流--有总电压 且 ch的通道开关打开 且 值大于零飘值 才显示
			if(s_tReg->Dc28V1OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x400) && 
			#endif
			tmp.Data6 > DC28V1_CH6_ZERO_DRIFT){
				factor[6] = DC_28V1_OUTV_CH6_FACTOR;
				B[6] = DC_28V1_OUTV_CH6_B;
				factor[7] = DC_28V1_OUTI_CH6_FACTOR;
				B[7] = DC_28V1_OUTI_CH6_B;
			}else{
				factor[6] = 0;
				B[6] = 0;
				factor[7] = 0;
				B[7] = 0;
			}
			if(s_tReg->Dc28V2OutputVoltage>0 && 
			#if !ZERO_DRIFT		
			(s_tReg->DcPowerControl & 0x800) && 
			#endif
			tmp.Data8 > DC28V2_CH6_ZERO_DRIFT){
				factor[8] = DC_28V2_OUTV_CH6_FACTOR;
				B[8] = DC_28V2_OUTV_CH6_B;
				factor[9] = DC_28V2_OUTI_CH6_FACTOR;
				B[9] = DC_28V2_OUTI_CH6_B;
			}else{
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}
			
			//115v输入电流A相--有电压才显示电流
			if(s_tReg->Ac115VcInputVoltage > 0){
				factor[10]=	AC_115V_INI_C_FACTOR;
				B[10]=	AC_115V_INI_C_B;		
			}else{
				factor[10]=	0;
				B[10]=	0;		
			}
			break;
		case 3:
			//交流380v
			if(tmp.Data0<AC380U_ZERO_DRIFT_A){
				factor[0] = 0;
				B[0] = 0;
				factor[3] = 0;
				B[3] = 0;
			}else{
				factor[0] = AC_380V_INV_A_FACTOR;
				B[0] = AC_380V_INV_A_B;
				factor[3] = AC_380V_INI_A_FACTOR;
				B[3] = AC_380V_INI_A_B;
			}
			if(tmp.Data1<AC380U_ZERO_DRIFT_B){
				factor[1] = 0;
				B[1] = 0;
				factor[4] = 0;
				B[4] = 0;
			}else{
				factor[1] = AC_380V_INV_B_FACTOR;
				B[1] = AC_380V_INV_B_B;
				factor[4] = AC_380V_INI_B_FACTOR;
				B[4] = AC_380V_INI_B_B;
			}
			if(tmp.Data2<AC380U_ZERO_DRIFT_C){
				factor[2] = 0;
				B[2] = 0;
				factor[5] = 0;
				B[5] = 0;
			}else{
				factor[2] = AC_380V_INV_C_FACTOR;
				B[2] = AC_380V_INV_C_B;
				
				factor[5] = AC_380V_INI_C_FACTOR;
				B[5] = AC_380V_INI_C_B;
			}
			//交流220v
			//if(tmp.Data6<AC220U_ZERO_DRIFT){
			if((rReg->Ac115VaInputVoltage > 9000 && rReg->Ac115VbInputVoltage > 9000 && rReg->Ac115VcInputVoltage > 9000) || (tmp.Data6 < AC220U_ZERO_DRIFT)){			//当前是115V输入
				factor[6] = 0;
				factor[7] = 0;
				B[6] = 0;
				B[7] = 0;
			}else{
				factor[6] = AC_220V_INV_FACTOR;
				factor[7] = AC_220V_INI_FACTOR;
				B[6] = AC_220V_INV_B;
				B[7] = AC_220V_INI_B;
			}
			//直流28VDC3
			if(tmp.Data8<DC28V3_ZERO_DRIFT){
				factor[8] = 0;
				B[8] = 0;
				factor[9] = 0;
				B[9] = 0;
			}else{
				factor[8] = DC_28V3_OUTV_FACTOR;
				B[8] = DC_28V3_OUTV_B;
				//28VDC3 控制开关打开才显示电流
				if(s_tReg->DcPowerControl & 0x1000){		
					factor[9] = DC_28V3_OUTI_FACTOR;
					B[9] = DC_28V3_OUTI_B;
				}else{
					factor[9] = 0;
					B[9] = 0;
				}
			}
			
			factor[10]=	0;
			B[10]=	0;
			break;
		default:
			break;
	}

#endif
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
	
#else
	//计算瞬态值
	spiTransientData.Data0 = (spiTransientData.Data0 - 0)*factor[0]+B[0];
	spiTransientData.Data1 = (spiTransientData.Data1 - 0)*factor[1]+B[1];
	spiTransientData.Data2 = (spiTransientData.Data2 - 0)*factor[2]+B[2];
	spiTransientData.Data3 = (spiTransientData.Data3 - 0)*factor[3]+B[3];
	spiTransientData.Data4 = (spiTransientData.Data4 - 0)*factor[4]+B[4];
	spiTransientData.Data5 = (spiTransientData.Data5 - 0)*factor[5]+B[5];
	spiTransientData.Data6 = (spiTransientData.Data6 - 0)*factor[6]+B[6];
	spiTransientData.Data7 = (spiTransientData.Data7 - 0)*factor[7]+B[7];
	spiTransientData.Data8 = (spiTransientData.Data8 - 0)*factor[8]+B[8];
	spiTransientData.Data9 = (spiTransientData.Data9 - 0)*factor[9]+B[9];
	spiTransientData.Data10 = (spiTransientData.Data10 - 0)*factor[10]+B[10];
	
	//计算稳态值
	spiSteadyData.Data0 = (tmp.Data0 - 0)*factor[0]+B[0];
	spiSteadyData.Data1 = (tmp.Data1 - 0)*factor[1]+B[1];
	spiSteadyData.Data2 = (tmp.Data2 - 0)*factor[2]+B[2];
	spiSteadyData.Data3 = (tmp.Data3 - 0)*factor[3]+B[3];
	spiSteadyData.Data4 = (tmp.Data4 - 0)*factor[4]+B[4];
	spiSteadyData.Data5 = (tmp.Data5 - 0)*factor[5]+B[5];
	spiSteadyData.Data6 = (tmp.Data6 - 0)*factor[6]+B[6];
	if(tmp.Data7 < zero[s_channel].Data7){
		spiSteadyData.Data7 = 0;
	}else{
		spiSteadyData.Data7 = (tmp.Data7 - zero[s_channel].Data7)*factor[7]+B[7];
	}
	//spiSteadyData.Data7 = (tmp.Data7)*factor[7]+B[7];
	spiSteadyData.Data8 = (tmp.Data8 - 0)*factor[8]+B[8];
	if(tmp.Data9 < zero[s_channel].Data9){
		spiSteadyData.Data9 = 0;
	}else{
		spiSteadyData.Data9 = (tmp.Data9 - zero[s_channel].Data9)*factor[9]+B[9];
	}
	//spiSteadyData.Data9 = (tmp.Data9)*factor[9]+B[9];
	spiSteadyData.Data10 = (tmp.Data10 - 0)*factor[10]+B[10];
#endif
}
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

