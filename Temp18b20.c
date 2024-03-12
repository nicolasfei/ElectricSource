
#include "Temp18b20.h"
 
 /*
函数功能: 延时us单位
*/
void DelayUs(int us)
{
#ifdef	_SYSTICK_IRQ_
	int i,j;
	for(i=0;i<us;i++)
		for(j=0;j<72;j++);
#else
	uint32_t tmp;
	SysTick->VAL=0;         //CNT计数器值	
	SysTick->LOAD=9*us;     //9表示1us
	SysTick->CTRL|=1<<0;    //开启定时器	
	do
	{
			tmp=SysTick->CTRL; //读取状态
	}while((!(tmp&1<<16))&&(tmp&1<<0));
	SysTick->VAL=0;         //CNT计数器值	
	SysTick->CTRL&=~(1<<0); //关闭定时器	
#endif	
}

/*
函数功能: DS18B20初始化
硬件连接: PB15
*/
void DS18B20_Init(void)
{
		//温度传感器1
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//配置为下拉模式
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//配置为推挽输出，速度为50M
	
	//温度传感器2
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);
}
 
 
/*
函数功能: 检测DS18B20设备是否存在
返回值  : 1表示设备不存在 0表示设备正常
*/
uint8_t DS18B20_CheckDevice(void)  //包含了复位脉冲、检测存在脉冲
{
		DS18B20_T1_OUT();//初始化为输出模式
		DS18B20_T1_DOWN;        //产生复位脉冲
		DelayUs(750);         //产生750us的低电平
		DS18B20_T1_UP;        //释放总线
		DelayUs(15);          //等待DS18B20回应
		if(DS18B20_CleckAck())//检测存在脉冲
		{
				return 1;
		}
		return 0;
}
 
/*
函数功能: 检测DS18B20设备的存在脉冲
返回值  : 1表示错误 0表示正常
*/
uint8_t DS18B20_CleckAck(void)
{
		uint8_t cnt=0;
		DS18B20_T1_IN();//初始化为输入模式
		while(DS18B20_T1_GET_BIT&&cnt<200) //等待DS18B20响应存在脉冲
		{
				DelayUs(1);
				cnt++;
		}
		if(cnt>=200)return 1; //错误
		
		cnt=0;
		while((!DS18B20_T1_GET_BIT)&&cnt<240) //等待DS18B20释放总线
		{
				DelayUs(1);
				cnt++;
		}
		if(cnt>=240)return 1; //错误
		return 0;
}
 
 
/*
函数功能: 写一个字节
首先学会如何写一个位。
*/
void DS18B20_WriteByte(uint8_t cmd)
{
		uint8_t i;
		DS18B20_T1_OUT(); //初始化为输出模式
		for(i=0;i<8;i++)
	  {
				DS18B20_T1_DOWN;  //产生写时间间隙(写开始)
				DelayUs(2);
				if(cmd&0x01)			//发送实际的数据位
					DS18B20_T1_UP;
				else
					DS18B20_T1_DOWN;
				DelayUs(60);    //等待写完成
				DS18B20_T1_UP;  //释放总线，准备下一次发送
				cmd>>=1;        //继续发送下一位数据
		}
}
 
/*
函数功能: 读一个字节
首先学会如何读一个位。
*/
uint8_t DS18B20_ReadByte(void)
{
	 uint8_t i,data=0;	
	 for(i=0;i<8;i++)
	 {
			DS18B20_T1_OUT(); //初始化为输出模式
			DS18B20_T1_DOWN;  //产生读时间间隙(读开始)
			DelayUs(2);
			DS18B20_T1_UP;  //释放总线
			DS18B20_T1_IN(); //初始化为输入模式
			DelayUs(8);    //等待DS18B20的数据输出
			data>>=1;      //高位补0，默认以0为准
		  if(DS18B20_T1_GET_BIT) data|=0x80;
			DelayUs(60);
			DS18B20_T1_UP;  //释放总线,等待读取下一位数据
	 }
	 return data;
}
 
 
/*
函数功能: 读取一次DS18B20的温度数据
返 回 值: 读取的温度数据
考虑的情况:  总线上只是接了一个DS18B20的情况
*/
uint16_t DS18B20_ReadTemp(void)
{
	  uint16_t temp=0;
		uint8_t temp_H,temp_L;
	  DS18B20_CheckDevice();   //发送复位脉冲、检测存在脉冲
		DS18B20_WriteByte(0xCC); //跳过ROM序列检测
		DS18B20_WriteByte(0x44); //启动一次温度转换
		
		//等待温度转换完成
		while(DS18B20_ReadByte()!=0xFF){}
		
		DS18B20_CheckDevice();   //发送复位脉冲、检测存在脉冲
		DS18B20_WriteByte(0xCC); //跳过ROM序列检测
		DS18B20_WriteByte(0xBE); //读取温度
		
		temp_L=DS18B20_ReadByte(); //读取的温度低位数据
		temp_H=DS18B20_ReadByte(); //读取的温度高位数据
		temp=temp_L|(temp_H<<8);   //合成温度
		return temp;
}
