/*********************************************************************
* ��Ȩ���� (C)2023, �ɶ�XXXX���޹�˾��
* 
* �ļ����ƣ� // ErrorControl.c
* �ļ���ʶ�� // 
* ����ժҪ�� // ���Ͽ��Ƴ���
* ����˵���� // 
* ��ǰ�汾�� // V1.0
* ��     �ߣ�// 0001
* ������ڣ� // 20230104
* 
* �޸ļ�¼
* �޸����ڣ�
* �� �� �ˣ�
* �޸����ݣ� 
**********************************************************************/
#include "Ds18b20.h"
 
uint8_t tempConFinish=0;
uint8_t fanConFinish=0;
short temp18b20 = 0;

/*
��������: DS18B20��ʼ��
Ӳ������: PB15
*/
void DS18B20_Init(void)
{
		//�¶ȴ�����1
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);//����Ϊ����ģʽ
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);//����Ϊ����������ٶ�Ϊ50M
	
	//�¶ȴ�����2
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5);
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);
}
 
 
/*
��������: ���DS18B20�豸�Ƿ����
����ֵ  : 1��ʾ�豸������ 0��ʾ�豸����
*/
uint8_t DS18B20_CheckDevice(int channel)  //�����˸�λ���塢����������
{
	switch(channel){
		
		case DS18B20_TEMP:
			DS18B20_T1_OUT();			//��ʼ��Ϊ���ģʽ
			DS18B20_T1_DOWN;      //������λ����
			DelayUs(750);         //����750us�ĵ͵�ƽ
			DS18B20_T1_UP;        //�ͷ�����
			DelayUs(15);          //�ȴ�DS18B20��Ӧ
			break;			
		case DS18B20_Fan:
			DS18B20_T2_OUT();			//��ʼ��Ϊ���ģʽ
			DS18B20_T2_DOWN;      //������λ����
			DelayUs(750);         //����750us�ĵ͵�ƽ
			DS18B20_T2_UP;        //�ͷ�����
			DelayUs(15);          //�ȴ�DS18B20��Ӧ
			break;
		default:
			break;
	}
	return 0;
}
 
/*
��������: ���DS18B20�豸�Ĵ�������
����ֵ  : 1��ʾ���� 0��ʾ����
*/
uint8_t DS18B20_CleckAck(int channel)
{
		uint8_t cnt=0;
	
		switch(channel){
		
			case DS18B20_TEMP:
				DS18B20_T1_IN();										//��ʼ��Ϊ����ģʽ
				while(DS18B20_T1_GET_BIT&&cnt<200) 	//�ȴ�DS18B20��Ӧ��������
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=200)return 1; //����
		
				cnt=0;
				while((!DS18B20_T1_GET_BIT)&&cnt<240) //�ȴ�DS18B20�ͷ�����
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=240)return 1; //����
				break;
			case DS18B20_Fan:
				DS18B20_T2_IN();										//��ʼ��Ϊ����ģʽ
				while(DS18B20_T2_GET_BIT&&cnt<200) 	//�ȴ�DS18B20��Ӧ��������
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=200)return 1; //����
		
				cnt=0;
				while((!DS18B20_T2_GET_BIT)&&cnt<240) //�ȴ�DS18B20�ͷ�����
				{
					DelayUs(1);
					cnt++;
				}
				if(cnt>=240)return 1; //����
				break;
			default:
			break;
		}
		return 0;
}
 
 
/*
��������: дһ���ֽ�
����ѧ�����дһ��λ��
*/
void DS18B20_WriteByte(int channel, uint8_t cmd)
{
		uint8_t i;
		
		switch(channel){
		
			case DS18B20_TEMP:
				DS18B20_T1_OUT(); //��ʼ��Ϊ���ģʽ
				for(i=0;i<8;i++)
				{
					DS18B20_T1_DOWN;  //����дʱ���϶(д��ʼ)
					DelayUs(2);
					if(cmd&0x01)			//����ʵ�ʵ�����λ
						DS18B20_T1_UP;
					else
						DS18B20_T1_DOWN;
					DelayUs(60);    //�ȴ�д���
					DS18B20_T1_UP;  //�ͷ����ߣ�׼����һ�η���
					cmd>>=1;        //����������һλ����
				}
				break;
			case DS18B20_Fan:
				DS18B20_T2_OUT(); //��ʼ��Ϊ���ģʽ
				for(i=0;i<8;i++)
				{
					DS18B20_T2_DOWN;  //����дʱ���϶(д��ʼ)
					DelayUs(2);
					if(cmd&0x01)			//����ʵ�ʵ�����λ
						DS18B20_T2_UP;
					else
						DS18B20_T2_DOWN;
					DelayUs(60);    //�ȴ�д���
					DS18B20_T2_UP;  //�ͷ����ߣ�׼����һ�η���
					cmd>>=1;        //����������һλ����
				}
				break;
			default:
			break;
		}
}
 
/*
��������: ��һ���ֽ�
����ѧ����ζ�һ��λ��
*/
uint8_t DS18B20_ReadByte(int channel)
{
	uint8_t i,data=0;	
	
	switch(channel){
		
			case DS18B20_TEMP:
				for(i=0;i<8;i++)
				{
					DS18B20_T1_OUT(); //��ʼ��Ϊ���ģʽ
					DS18B20_T1_DOWN;  //������ʱ���϶(����ʼ)
					DelayUs(2);
					DS18B20_T1_UP;  //�ͷ�����
					DS18B20_T1_IN(); //��ʼ��Ϊ����ģʽ
					DelayUs(12);    //�ȴ�DS18B20���������
					data>>=1;      //��λ��0��Ĭ����0Ϊ׼
					if(DS18B20_T1_GET_BIT) data|=0x80;
						DelayUs(50);
					DS18B20_T1_UP;  //�ͷ�����,�ȴ���ȡ��һλ����
				}
				break;
			case DS18B20_Fan:
				for(i=0;i<8;i++)
				{
					DS18B20_T2_OUT(); //��ʼ��Ϊ���ģʽ
					DS18B20_T2_DOWN;  //������ʱ���϶(����ʼ)
					DelayUs(2);
					DS18B20_T2_UP;  //�ͷ�����
					DS18B20_T2_IN(); //��ʼ��Ϊ����ģʽ
					DelayUs(12);    //�ȴ�DS18B20���������
					data>>=1;      //��λ��0��Ĭ����0Ϊ׼
					if(DS18B20_T2_GET_BIT) data|=0x80;
						DelayUs(50);
					DS18B20_T2_UP;  //�ͷ�����,�ȴ���ȡ��һλ����
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
			DS18B20_CheckDevice(DS18B20_TEMP);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_TEMP);
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_TEMP,0x44); //����һ���¶�ת��
		break;
		case 1:
			DS18B20_CheckDevice(DS18B20_TEMP);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_TEMP);
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_TEMP,0xBE); //��ȡ�¶�
			temp_L=DS18B20_ReadByte(DS18B20_TEMP); //��ȡ���¶ȵ�λ����
			temp_H=DS18B20_ReadByte(DS18B20_TEMP); //��ȡ���¶ȸ�λ����
			temp=(temp_L|(temp_H<<8)) * 0.625;   	 //�ϳ��¶�
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
			DS18B20_CheckDevice(DS18B20_TEMP);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_TEMP);
		break;
		case 1:
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_TEMP,0x44); //����һ���¶�ת��
		break;
		case 2:
			DS18B20_CheckDevice(DS18B20_TEMP);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_TEMP);
		break;
		case 3:
			DS18B20_WriteByte(DS18B20_TEMP,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_TEMP,0xBE); //��ȡ�¶�
		break;
		case 4:
			temp_L=DS18B20_ReadByte(DS18B20_TEMP); //��ȡ���¶ȵ�λ����
			temp_H=DS18B20_ReadByte(DS18B20_TEMP); //��ȡ���¶ȸ�λ����
			temp=(temp_L|(temp_H<<8)) * 0.625;   	 //�ϳ��¶�
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
			DS18B20_CheckDevice(DS18B20_Fan);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_Fan);
			DS18B20_WriteByte(DS18B20_Fan,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_Fan,0x44); //����һ���¶�ת��
		break;
		case 1:
			DS18B20_CheckDevice(DS18B20_Fan);   //���͸�λ���塢����������
			DS18B20_CleckAck(DS18B20_Fan);
			DS18B20_WriteByte(DS18B20_Fan,0xCC); //����ROM���м��
			DS18B20_WriteByte(DS18B20_Fan,0xBE); //��ȡ�¶�
			temp_L=DS18B20_ReadByte(DS18B20_Fan); //��ȡ���¶ȵ�λ����
			temp_H=DS18B20_ReadByte(DS18B20_Fan); //��ȡ���¶ȸ�λ����
			temp=(temp_L|(temp_H<<8)) * 0.625;   	//�ϳ��¶�
			fanConFinish=1;
		break;
	}
	fanReadStatus++;
	if(fanReadStatus>1)
		fanReadStatus=0;
	return temp;
}

/*
��������: ��ȡһ��DS18B20���¶�����
�� �� ֵ: ��ȡ���¶�����
���ǵ����:  ������ֻ�ǽ���һ��DS18B20�����
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

