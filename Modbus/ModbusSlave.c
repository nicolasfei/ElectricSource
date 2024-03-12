#include <string.h>
#include "ModbusSlave.h"


static unsigned short CRC_Compute(unsigned char *ptr,unsigned int len)
{
		const unsigned char auchCRCHi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
		};
		const unsigned char auchCRCLo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
		0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
		0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
		0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
		0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
		0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
		0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
		0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
		0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
		0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
		0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
		0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
		0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
		0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
		0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
		0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
		0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
		0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
		0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
		0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
		0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
		0x43, 0x83, 0x41, 0x81, 0x80, 0x40
		};
		unsigned char uchCRCHi = 0xFF;  /* 高CRC字节初始化 */ 
		unsigned char uchCRCLo = 0xFF;  /* 低CRC字节初始化*/ 
		unsigned long uIndex;         
		while(len--)
		{
				uIndex = uchCRCHi ^ *ptr++;
				uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
				uchCRCLo = auchCRCLo[uIndex];
		}
		return ((uchCRCLo << 8) | uchCRCHi);
}

//Modbus功能码01
//读输出开关量
static void ReadCoilStatusResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum = (((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器数量
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//寄存器地址+数量在范围内
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				ByteNum = RegNum / 8;//字节数
				if(RegNum % 8) ByteNum += 1;//如果位数还有余数,则字节数+1
				cTxData[2] = ByteNum;//返回要读取的字节数
				for(i = 0;i < RegNum;i++)
				{
						if(i % 8 == 0) cTxData[3 + i / 8]=0x00;
						cTxData[3 + i / 8] >>= 1;//低位先发
						cTxData[3 + i / 8] |= ((ptModbusSlaveParam->pcCoilStatus[ptModbusSlaveParam->wStartAddr + i]) << 7) & 0x80;
						if(i == RegNum - 1)//发送到最后一位
						{
								if(RegNum % 8) cTxData[3 + i / 8] >>= 8 - (RegNum % 8);//如果最后一个字节还有余数,则输入MSB填充0
						}
				}
				CalCrc = CRC_Compute(cTxData,ByteNum + 3);
				cTxData[ByteNum + 3] = CalCrc & 0xFF;
				cTxData[ByteNum + 4] = (CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,ByteNum+5);
		}
		else//如果寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1] | 0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码02
//读输入开关量
static void ReadInputStatusResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum=(((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器数量
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//寄存器地址+数量在地址范围内
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				ByteNum = RegNum / 8;//字节数
				if(RegNum % 8) ByteNum += 1;//如果位数还有余数,则字节数+1
				cTxData[2] = ByteNum;//返回要读取的字节数
				for(i = 0;i < RegNum;i++)
				{
						if(i % 8 == 0) cTxData[3 + i / 8]=0x00;
						cTxData[3 + i / 8] >>= 1;//低位先发
						cTxData[3 + i / 8] |= ((ptModbusSlaveParam->pcInputStatus[ptModbusSlaveParam->wStartAddr + i]) << 7) & 0x80;
						if(i == RegNum - 1)//发送到最后一位
						{
								if(RegNum % 8) cTxData[3 + i / 8] >>= 8 - (RegNum % 8);//如果最后一个字节还有余数,则输入MSB填充0
						}
				}
				CalCrc = CRC_Compute(cTxData,ByteNum + 3);
				cTxData[ByteNum + 3] = CalCrc & 0xFF;
				cTxData[ByteNum + 4] = (CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,ByteNum+5);
		}
		else//寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1] | 0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码03
//读保持寄存器
static void ReadHoldRegResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		//unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum = (((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器地址
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//如果寄存器地址+数量在范围内
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				cTxData[2] = RegNum * 2;
				for(i = 0;i < RegNum;i++)
				{
						cTxData[4 + i * 2] =  ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr + i] & 0xFF;//后发低字节
						cTxData[3 + i * 2] = (ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr + i] >> 8) & 0xFF; //先发高字节
				}
				CalCrc = CRC_Compute(cTxData,RegNum * 2 + 3);
				cTxData[RegNum * 2 + 3]=CalCrc & 0xFF;
				cTxData[RegNum * 2 + 4]=(CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,RegNum * 2 + 5);
		}
		else//寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码04
//读输入寄存器
static void ReadInputRegResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		//unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum = (((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器地址
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//如果寄存器地址+数量在范围内
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				cTxData[2] = RegNum * 2;
				for(i = 0;i < RegNum;i++)
				{
						cTxData[4 + i * 2] =  ptModbusSlaveParam->pwInputReg[ptModbusSlaveParam->wStartAddr + i] & 0xFF;//后发低字节
						cTxData[3 + i * 2] = (ptModbusSlaveParam->pwInputReg[ptModbusSlaveParam->wStartAddr + i] >> 8) & 0xFF; //先发高字节
				}
				CalCrc = CRC_Compute(cTxData,RegNum * 2 + 3);
				cTxData[RegNum * 2 + 3]=CalCrc & 0xFF;
				cTxData[RegNum * 2 + 4]=(CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,RegNum * 2 + 5);
		}
		else//寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码05
//写单个输出开关量
static void WriteSingleCoilResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		if(ptModbusSlaveParam->wStartAddr < 255)//寄存器地址在范围内
		{
				if((ptModbusSlaveParam->pcRxData[4] == 0xFF) || (ptModbusSlaveParam->pcRxData[5] == 0xFF)) 
				{
						ptModbusSlaveParam->pcCoilStatus[ptModbusSlaveParam->wStartAddr] = 0x01;
				}
				else 
				{
						ptModbusSlaveParam->pcCoilStatus[ptModbusSlaveParam->wStartAddr] = 0x00;
				}
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				cTxData[2] = ptModbusSlaveParam->pcRxData[2];
				cTxData[3] = ptModbusSlaveParam->pcRxData[3];
				cTxData[4] = ptModbusSlaveParam->pcRxData[4];
				cTxData[5] = ptModbusSlaveParam->pcRxData[5];
				
				CalCrc = CRC_Compute(cTxData,6);
				cTxData[6] = CalCrc&0xFF;
				cTxData[7] = (CalCrc>>8)&0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,8);
		}
		else//寄存器地址超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码06
//写单个保持寄存器
static void WriteSigleRegResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr]  = ptModbusSlaveParam->pcRxData[5];//低字节在前
		ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr] |= ((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8;//高字节在后
		
		cTxData[0] = ptModbusSlaveParam->pcRxData[0];
		cTxData[1] = ptModbusSlaveParam->pcRxData[1];
		cTxData[2] = ptModbusSlaveParam->pcRxData[2];
		cTxData[3] = ptModbusSlaveParam->pcRxData[3];
		cTxData[4] = ptModbusSlaveParam->pcRxData[4];
		cTxData[5] = ptModbusSlaveParam->pcRxData[5];
		
		CalCrc = CRC_Compute(cTxData,6);
		cTxData[6] = CalCrc & 0xFF;
		cTxData[7] = (CalCrc >> 8) & 0xFF;
		UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,8);
}

//Modbus功能码15
//写多个输出开关量
static void WriteMultCoilsResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		//unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum = (((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器地址
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//如果寄存器地址+数量在范围内
		{        
				for(i = 0;i < RegNum;i++)
				{
						if(ptModbusSlaveParam->pcRxData[7 + i / 8] & 0x01) 
						{
								ptModbusSlaveParam->pcCoilStatus[ptModbusSlaveParam->wStartAddr + i] = 0x01;
						}
						else 
						{
								ptModbusSlaveParam->pcCoilStatus[ptModbusSlaveParam->wStartAddr + i] = 0x00;
						}
						ptModbusSlaveParam->pcRxData[7 + i / 8] >>= 1;//从低位开始
				}
				
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				cTxData[2] = ptModbusSlaveParam->pcRxData[2];
				cTxData[3] = ptModbusSlaveParam->pcRxData[3];
				cTxData[4] = ptModbusSlaveParam->pcRxData[4];
				cTxData[5] = ptModbusSlaveParam->pcRxData[5];
				CalCrc = CRC_Compute(cTxData,6);
				cTxData[6] = CalCrc & 0xFF;
				cTxData[7] = (CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,8);
		}
		else//寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}

//Modbus功能码16
//写多个保持寄存器
static void WriteMultRegsResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short i = 0;
		//unsigned short ByteNum = 0;
		unsigned short RegNum = 0;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		RegNum = (((unsigned short)ptModbusSlaveParam->pcRxData[4]) << 8) | ptModbusSlaveParam->pcRxData[5];//获取寄存器数量
		if((ptModbusSlaveParam->wStartAddr + RegNum) < 255)//如果寄存器地址+数量在范围内
		{
				for(i = 0;i < RegNum;i++)
				{
						ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr + i] = ptModbusSlaveParam->pcRxData[8 + i * 2]; //高字节在前
						ptModbusSlaveParam->pwHoldReg[ptModbusSlaveParam->wStartAddr + i] |= ((unsigned short)ptModbusSlaveParam->pcRxData[7 + i * 2]) << 8; //低字节在后
				}
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1];
				cTxData[2] = ptModbusSlaveParam->pcRxData[2];
				cTxData[3] = ptModbusSlaveParam->pcRxData[3];
				cTxData[4] = ptModbusSlaveParam->pcRxData[4];
				cTxData[5] = ptModbusSlaveParam->pcRxData[5];
				
				CalCrc = CRC_Compute(cTxData,6);
				cTxData[6] = CalCrc & 0xFF;
				cTxData[7] = (CalCrc >> 8) & 0xFF;
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,8);
		}
		else//寄存器地址+数量超出范围
		{
				cTxData[0] = ptModbusSlaveParam->pcRxData[0];
				cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
				cTxData[2] = 0x02; //异常码
				UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
		}
}


void ModbusSlaveResponse(MODBUS_SLAVE_PARAM *ptModbusSlaveParam)
{
		unsigned short recCRC;
		unsigned short CalCrc = 0;
		unsigned char cTxData[MAX_RX_CNT] = {0};
		
		if(1 == ptModbusSlaveParam->cRxFrameEndFlag)
		{
				if(*ptModbusSlaveParam->pcRxCnt > 2)
				{
						if(ptModbusSlaveParam->pcRxData[0] == ptModbusSlaveParam->cSlaveId)//从机地址正确
						{
								if((ptModbusSlaveParam->pcRxData[1] == 01) || (ptModbusSlaveParam->pcRxData[1] == 02) || (ptModbusSlaveParam->pcRxData[1] == 03) 
								|| (ptModbusSlaveParam->pcRxData[1] == 04) || (ptModbusSlaveParam->pcRxData[1] == 05) || (ptModbusSlaveParam->pcRxData[1] == 06) 
								|| (ptModbusSlaveParam->pcRxData[1] == 15) || (ptModbusSlaveParam->pcRxData[1] == 16))//功能码正确
								{
										if(ptModbusSlaveParam->pcRxData[1] > 4)
										{
												*(ptModbusSlaveParam->pcSlaveOnlineVal) = 2;
										}
										ptModbusSlaveParam->wStartAddr  = (((unsigned short)ptModbusSlaveParam->pcRxData[2]) << 8) | ptModbusSlaveParam->pcRxData[3];//获取寄存器起始地址
										
										CalCrc = CRC_Compute(ptModbusSlaveParam->pcRxData,*ptModbusSlaveParam->pcRxCnt - 2);//计算接收数据的CRC
										recCRC = ptModbusSlaveParam->pcRxData[*ptModbusSlaveParam->pcRxCnt - 2] | (((unsigned short)ptModbusSlaveParam->pcRxData[*ptModbusSlaveParam->pcRxCnt - 1]) << 8);//接收到的CRC(低值在前，高值在后)
										if(CalCrc == recCRC)//CRC校验正确
										{
												switch(ptModbusSlaveParam->pcRxData[1])//根据不同的功能码处理
												{
														
														case 01://读输出开关量  
																ReadCoilStatusResponse(ptModbusSlaveParam);
																break;
														case 02://读输入开关量 
																ReadInputStatusResponse(ptModbusSlaveParam);
																break;
														case 03: //读保持寄存器
																ReadHoldRegResponse(ptModbusSlaveParam);
																break;
														case 04: //读输入寄存器
																ReadInputRegResponse(ptModbusSlaveParam);
																break;
														case 05://写单个输出开关量   
																WriteSingleCoilResponse(ptModbusSlaveParam);
																break;
														case 06: //写单个保持寄存器
																WriteSigleRegResponse(ptModbusSlaveParam);
																break;
														case 15://写多个输出开关量  
																WriteMultCoilsResponse(ptModbusSlaveParam);
																break;
														case 16: //写多个保持寄存器
																WriteMultRegsResponse(ptModbusSlaveParam);
																break;																											
														default:
															    break;
												}
										}
										else//CRC校验错误
										{
												cTxData[0] = ptModbusSlaveParam->pcRxData[0];
												cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
												cTxData[2] = 0x04; //异常码
												UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
										}                                              
								}
								else//功能码错误
								{
									cTxData[0] = ptModbusSlaveParam->pcRxData[0];
									cTxData[1] = ptModbusSlaveParam->pcRxData[1]|0x80;
									cTxData[2] = 0x01; //异常码
									UsartSendData(ptModbusSlaveParam->wUsartPeriph,cTxData,3);
								}
						}		
				}
				*ptModbusSlaveParam->pcRxCnt = 0;//接收寄存器清零       
		}                
}
