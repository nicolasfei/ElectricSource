
#include "Temp18b20.h"
 
 /*
��������: ��ʱus��λ
*/
void DelayUs(int us)
{
#ifdef	_SYSTICK_IRQ_
	int i,j;
	for(i=0;i<us;i++)
		for(j=0;j<72;j++);
#else
	uint32_t tmp;
	SysTick->VAL=0;         //CNT������ֵ	
	SysTick->LOAD=9*us;     //9��ʾ1us
	SysTick->CTRL|=1<<0;    //������ʱ��	
	do
	{
			tmp=SysTick->CTRL; //��ȡ״̬
	}while((!(tmp&1<<16))&&(tmp&1<<0));
	SysTick->VAL=0;         //CNT������ֵ	
	SysTick->CTRL&=~(1<<0); //�رն�ʱ��	
#endif	
}

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
uint8_t DS18B20_CheckDevice(void)  //�����˸�λ���塢����������
{
		DS18B20_T1_OUT();//��ʼ��Ϊ���ģʽ
		DS18B20_T1_DOWN;        //������λ����
		DelayUs(750);         //����750us�ĵ͵�ƽ
		DS18B20_T1_UP;        //�ͷ�����
		DelayUs(15);          //�ȴ�DS18B20��Ӧ
		if(DS18B20_CleckAck())//����������
		{
				return 1;
		}
		return 0;
}
 
/*
��������: ���DS18B20�豸�Ĵ�������
����ֵ  : 1��ʾ���� 0��ʾ����
*/
uint8_t DS18B20_CleckAck(void)
{
		uint8_t cnt=0;
		DS18B20_T1_IN();//��ʼ��Ϊ����ģʽ
		while(DS18B20_T1_GET_BIT&&cnt<200) //�ȴ�DS18B20��Ӧ��������
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
		return 0;
}
 
 
/*
��������: дһ���ֽ�
����ѧ�����дһ��λ��
*/
void DS18B20_WriteByte(uint8_t cmd)
{
		uint8_t i;
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
}
 
/*
��������: ��һ���ֽ�
����ѧ����ζ�һ��λ��
*/
uint8_t DS18B20_ReadByte(void)
{
	 uint8_t i,data=0;	
	 for(i=0;i<8;i++)
	 {
			DS18B20_T1_OUT(); //��ʼ��Ϊ���ģʽ
			DS18B20_T1_DOWN;  //������ʱ���϶(����ʼ)
			DelayUs(2);
			DS18B20_T1_UP;  //�ͷ�����
			DS18B20_T1_IN(); //��ʼ��Ϊ����ģʽ
			DelayUs(8);    //�ȴ�DS18B20���������
			data>>=1;      //��λ��0��Ĭ����0Ϊ׼
		  if(DS18B20_T1_GET_BIT) data|=0x80;
			DelayUs(60);
			DS18B20_T1_UP;  //�ͷ�����,�ȴ���ȡ��һλ����
	 }
	 return data;
}
 
 
/*
��������: ��ȡһ��DS18B20���¶�����
�� �� ֵ: ��ȡ���¶�����
���ǵ����:  ������ֻ�ǽ���һ��DS18B20�����
*/
uint16_t DS18B20_ReadTemp(void)
{
	  uint16_t temp=0;
		uint8_t temp_H,temp_L;
	  DS18B20_CheckDevice();   //���͸�λ���塢����������
		DS18B20_WriteByte(0xCC); //����ROM���м��
		DS18B20_WriteByte(0x44); //����һ���¶�ת��
		
		//�ȴ��¶�ת�����
		while(DS18B20_ReadByte()!=0xFF){}
		
		DS18B20_CheckDevice();   //���͸�λ���塢����������
		DS18B20_WriteByte(0xCC); //����ROM���м��
		DS18B20_WriteByte(0xBE); //��ȡ�¶�
		
		temp_L=DS18B20_ReadByte(); //��ȡ���¶ȵ�λ����
		temp_H=DS18B20_ReadByte(); //��ȡ���¶ȸ�λ����
		temp=temp_L|(temp_H<<8);   //�ϳ��¶�
		return temp;
}
