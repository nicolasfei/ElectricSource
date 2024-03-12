/*********************************************************************
* 版权所有 (C)2023, 成都XXXX有限公司。
* 
* 文件名称： // ErrorControl.c
* 文件标识： // 
* 内容摘要： // 故障控制程序
* 其它说明： // 
* 当前版本： // V1.0
* 作     者：// 0001
* 完成日期： // 20230104
* 
* 修改记录
* 修改日期：
* 修 改 人：
* 修改内容： 
**********************************************************************/
#include "Ds18b20.h"
 
uint8_t tempConFinish=0;
uint8_t fanConFinish=0;
short temp18b20 = 0;

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
uint8_t DS18B20_CheckDevice(int channel)  //包含了复位脉冲、检测存在脉冲
{
	switch(channel){
		
		case DS18B20_TEMP:
			DS18B20_T1_OUT();			//初始化为输出模式
			DS18B20_T1_DOWN;      //产生复位脉冲
			DelayUs(750);         //产生750us的低电平
			DS18B20_T1_UP;        //释放总线
			DelayUs(15);          //等待DS18B20回应
			break;			
		case DS18B20_Fan:
			DS18B20_T2_OUT();			//初始化为输出模式
			DS18B20_T2_DOWN;      //产生复位脉冲
			DelayUs(750);         //产生750us的低电平
			DS18B20_T2_UP;        //释放总线
			DelayUs(15);          //等待DS18B20回应
			break;
		default:
			break;
	}
	return 0;
}
 
/*
函数功能: 检测DS18B20设备的存在脉冲
返回值  : 1表示错误 0表示正常
*/
uint8_t DS18B20_CleckAck(int channel)
{
		uint8_t cnt=0;
	
		switch(channel){
		
			case DS18B20_TEMP:
				DS18B20_T1_IN();										//初始化为输入模式
				while(DS18B20_T1_GET_BIT&&cnt<200) 	//等待DS18B20响应存在脉冲
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
				break;
			case DS18B20_Fan:
				DS18B20_T2_IN();										//初始化为输入模式
				while(DS18B20_T2_GET_BIT&&cnt<200) 	//等待DS18B20响应存在脉冲
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=200)return 1; //错误
		
				cnt=0;
				while((!DS18B20_T2_GET_BIT)&&cnt<240) //等待DS18B20释放总线
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=240)return 1; //错误
				break;
			default:
			break;
		}
		return 0;
}
 
 
/*
函数功能: 写一个字节
首先学会如何写一个位。
*/
void DS18B20_WriteByte(int channel, uint8_t cmd)
{
		uint8_t i;
		
		switch(channel){
		
			case DS18B20_TEMP:
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
				break;
			case DS18B20_Fan:
				DS18B20_T2_OUT(); //初始化为输出模式
				for(i=0;i<8;i++)
				{
					DS18B20_T2_DOWN;  //产生写时间间隙(写开始)
					DelayUs(2);
					if(cmd&0x01)			//发送实际的数据位
						DS18B20_T2_UP;
					else
						DS18B20_T2_DOWN;
					DelayUs(60);    //等待写完成
					DS18B20_T2_UP;  //释放总线，准备下一次发送
					cmd>>=1;        //继续发送下一位数据
				}
				break;
			default:
			break;
		}
}
 
/*
函数功能: 读一个字节
首先学会如何读一个位。
*/
uint8_t DS18B20_ReadByte(int channel)
{
	uint8_t i,data=0;	
	
	switch(channel){
		
			case DS18B20_TEMP:
				for(i=0;i<8;i++)
				{
					DS18B20_T1_OUT(); //初始化为输出模式
					DS18B20_T1_DOWN;  //产生读时间间隙(读开始)
					DelayUs(2);
					DS18B20_T1_UP;  //释放总线
					DS18B20_T1_IN(); //初始化为输入模式
					DelayUs(12);    //等待DS18B20的数据输出
					data>>=1;      //高位补0，默认以0为准
					if(DS18B20_T1_GET_BIT) data|=0x80;
						DelayUs(50);
					DS18B20_T1_UP;  //释放总线,等待读取下一位数据
				}
				break;
			case DS18B20_Fan:
				for(i=0;i<8;i++)
				{
					DS18B20_T2_OUT(); //初始化为输出模式
					DS18B20_T2_DOWN;  //产生读时间间隙(读开始)
					DelayUs(2);
					DS18B20_T2_UP;  //释放总线
					DS18B20_T2_IN(); //初始化为输入模式
					DelayUs(12);    //等待DS18B20的数据输出
					data>>=1;      //高位补0，默认以0为准
					if(DS18B20_T2_GET_BIT) data|=0x80;
						DelayUs(50);
					DS18B20_T2_UP;  //释放总线,等待读取下一位数据
				}
				break;
			default:
			break;
	}
	
	 return data;
}
 
static char tempReadStatus=0;
static uint8_t temp_H,temp_L;
uint16_t DS18B20_GetTemp()
{
	uint16_t temp=0;
#if	1
	switch(tempReadStatus){
		case 0:
		default:
			tempConFinish=0;
			DS18B20_CheckDevice(DS18B20_TEMP);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_TEMP);
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_TEMP,0x44); //启动一次温度转换
		break;
		case 1:
			DS18B20_CheckDevice(DS18B20_TEMP);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_TEMP);
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_TEMP,0xBE); //读取温度
			temp_L=DS18B20_ReadByte(DS18B20_TEMP); //读取的温度低位数据
			temp_H=DS18B20_ReadByte(DS18B20_TEMP); //读取的温度高位数据
			temp=(temp_L|(temp_H<<8)) * 0.625;   	 //合成温度
			tempConFinish=1;
		break;
	}
	tempReadStatus++;
	if(tempReadStatus>1)
		tempReadStatus=0;
#else
	switch(tempReadStatus){
		case 0:
		default:
			tempConFinish=0;
			DS18B20_CheckDevice(DS18B20_TEMP);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_TEMP);
		break;
		case 1:
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_TEMP,0x44); //启动一次温度转换
		break;
		case 2:
			DS18B20_CheckDevice(DS18B20_TEMP);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_TEMP);
		break;
		case 3:
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_TEMP,0xBE); //读取温度
		break;
		case 4:
			temp_L=DS18B20_ReadByte(DS18B20_TEMP); //读取的温度低位数据
			temp_H=DS18B20_ReadByte(DS18B20_TEMP); //读取的温度高位数据
			temp=(temp_L|(temp_H<<8)) * 0.625;   	 //合成温度
			tempConFinish=1;
		break;
	}
	tempReadStatus++;
	if(tempReadStatus>4)
		tempReadStatus=0;
#endif
	return temp;
}

static char fanReadStatus=0;
uint16_t DS18B20_GetFan()
{
	uint16_t temp=0;
	uint8_t temp_H,temp_L;
	switch(fanReadStatus){
		case 0:
		default:
			fanConFinish=0;
			DS18B20_CheckDevice(DS18B20_Fan);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_Fan);
			DS18B20_WriteByte(DS18B20_Fan,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_Fan,0x44); //启动一次温度转换
		break;
		case 1:
			DS18B20_CheckDevice(DS18B20_Fan);   //发送复位脉冲、检测存在脉冲
			DS18B20_CleckAck(DS18B20_Fan);
			DS18B20_WriteByte(DS18B20_Fan,0xCC); //跳过ROM序列检测
			DS18B20_WriteByte(DS18B20_Fan,0xBE); //读取温度
			temp_L=DS18B20_ReadByte(DS18B20_Fan); //读取的温度低位数据
			temp_H=DS18B20_ReadByte(DS18B20_Fan); //读取的温度高位数据
			temp=(temp_L|(temp_H<<8)) * 0.625;   	//合成温度
			fanConFinish=1;
		break;
	}
	fanReadStatus++;
	if(fanReadStatus>1)
		fanReadStatus=0;
	return temp;
}

/*
函数功能: 读取一次DS18B20的温度数据
返 回 值: 读取的温度数据
考虑的情况:  总线上只是接了一个DS18B20的情况
*/
uint16_t DS18B20_ReadTemp(int channel)
{
	  uint16_t temp=0;
	
		switch(channel){
		case DS18B20_TEMP:
			temp = DS18B20_GetTemp();
			break;
		case DS18B20_Fan:
			temp = DS18B20_GetFan();
			break;
		default:
			break;
		}
		return temp;
}

uint8_t DS18B20_Temp_Finish(int channel)
{
	uint8_t finish=0;
	
	switch(channel){
		case DS18B20_TEMP:
			finish = tempConFinish;
		break;
		case DS18B20_Fan:
			finish = fanConFinish;
		break;
		default:
			break;
	}
	return finish;
}

