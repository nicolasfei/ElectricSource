#include <string.h>
#include "usart.h"
#include "UserTimer.h"

static unsigned short wUsart2RxCnt = 0;
static unsigned char cUsart2RxData[MAX_RX_CNT] = {0};
static long long llUsart2RxFrameEnd = 0;

static unsigned short wUsart1RxCnt = 0;
static unsigned char cUsart1RxData[MAX_RX_CNT] = {0};
static long long llUsart1RxFrameEnd = 0;


//初始化 串口1
//iBoundRate:波特率
void Usart1_init(int iBoundRate)
{  
		/*enable the GPIOA clock*/
		rcu_periph_clock_enable(RCU_GPIOD);
		/*enable the USART0 clock*/
		rcu_periph_clock_enable(RCU_USART1); 
		
		//配置复用功能
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_5); //配置PD5为复用类别7
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_6);
	
		//配置PD5引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_5);//配置PD5为复用上拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);//配置PD5为推挽输出，速度为50M
		//配置PD6引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6);//配置PD6为复用上拉模式
		//配置PD7引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_7);//配置PD7为下拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);//配置PD7为推挽输出，速度为50M
	
		usart_deinit(USART1);
		usart_baudrate_set(USART1, iBoundRate);                     // 波特率
		usart_word_length_set(USART1, USART_WL_8BIT);               // 帧数据字长
		usart_stop_bit_set(USART1, USART_STB_1BIT);                 // 停止位
		usart_parity_config(USART1, USART_PM_NONE);                 // 奇偶校验位
		usart_hardware_flow_rts_config(USART1, USART_RTS_DISABLE);  // 硬件流控制RTS
		usart_hardware_flow_cts_config(USART1, USART_CTS_DISABLE);  // 硬件流控制CTS
		usart_receive_config(USART1, USART_RECEIVE_ENABLE);         // 使能接收
		usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);       // 使能发送
		usart_enable(USART1);   
	
		nvic_irq_enable(USART1_IRQn, 3, 1);
		usart_interrupt_enable(USART1, USART_INT_RBNE);
}

//初始化 串口2
//iBoundRate:波特率
void Usart2_init(int iBoundRate)
{  	 
		/*enable the GPIOA clock*/
		rcu_periph_clock_enable(RCU_GPIOD);
		/*enable the USART0 clock*/
		rcu_periph_clock_enable(RCU_USART2); 
		
		//配置复用功能
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_8); //配置PD8为复用类别7
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_9);
	
		//配置PD8引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_8);//配置PD8为复用上拉模式
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);//配置PD8为推挽输出，速度为50M
		//配置PD9引脚的模式
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);//配置PD9为复用上拉模式
	
		usart_deinit(USART2);
	
		usart_baudrate_set(USART2, iBoundRate);                     // 波特率
		usart_word_length_set(USART2, USART_WL_8BIT);               // 帧数据字长
		usart_stop_bit_set(USART2, USART_STB_1BIT);                 // 停止位
		usart_parity_config(USART2, USART_PM_NONE);                 // 奇偶校验位
		usart_hardware_flow_rts_config(USART2, USART_RTS_DISABLE);  // 硬件流控制RTS
		usart_hardware_flow_cts_config(USART2, USART_CTS_DISABLE);  // 硬件流控制CTS
		usart_receive_config(USART2, USART_RECEIVE_ENABLE);         // 使能接收
		usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);       // 使能发送
		usart_enable(USART2);   
	
		nvic_irq_enable(USART2_IRQn, 3, 0);
		usart_interrupt_enable(USART2, USART_INT_RBNE);
}


void USART1_IRQHandler(void)
{
		unsigned char cData;
		if(RESET != usart_interrupt_flag_get(USART1,USART_INT_FLAG_RBNE_ORERR))
		{
				usart_interrupt_flag_clear(USART1,USART_INT_FLAG_RBNE_ORERR);
				cData = usart_data_receive(USART1);
		}
		if(RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE))
		{
				usart_interrupt_flag_clear(USART1,USART_INT_FLAG_RBNE);
				cData = usart_data_receive(USART1);
				
				if(wUsart1RxCnt < MAX_RX_CNT)
				{
						cUsart1RxData[wUsart1RxCnt] = cData;
						wUsart1RxCnt++;
						TimerInit(&llUsart1RxFrameEnd,4,1);
				}
				else
				{
						wUsart1RxCnt = 0;
				}
		}
}

void USART2_IRQHandler(void)
{
		unsigned char cData;
		if(RESET != usart_interrupt_flag_get(USART2,USART_INT_FLAG_RBNE_ORERR))
		{
				usart_interrupt_flag_clear(USART2,USART_INT_FLAG_RBNE_ORERR);
				cData = usart_data_receive(USART2);
		}
		if(RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE))
		{
				usart_interrupt_flag_clear(USART2,USART_INT_FLAG_RBNE);
				cData = usart_data_receive(USART2);
				
				if(wUsart2RxCnt < MAX_RX_CNT)
				{
						cUsart2RxData[wUsart2RxCnt] = cData;
						wUsart2RxCnt++;
						TimerInit(&llUsart2RxFrameEnd,4,1);
				}
				else
				{
						wUsart2RxCnt = 0;
				}
		}
}

/*-----------------------------------------------------------------
函数名称: void UsartSendData(unsigned int usart_periph,unsigned char *wTxData,unsigned char len)
函数功能: 串口发送程序
参    数: wTxData:发送的数据
返 回 值: 无
-----------------------------------------------------------------*/
void UsartSendData(unsigned int usart_periph,unsigned char *wTxData,unsigned char len)
{
		unsigned char i;
		if(USART1 == usart_periph)
		{
				RS485_CTL_TX();
		}
		for(i = 0;i < len;i++)
		{
				while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE));//等待发送结束
				usart_data_transmit(usart_periph,(unsigned char)wTxData[i]);
		}
		while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE));//等待发送结束
		if(USART1 == usart_periph)
		{
				RS485_CTL_RX();
		}
}

unsigned short *ReadUsart1RxCnt(void)
{
		return &wUsart1RxCnt;
}

unsigned char CheckUsart1RxFrameEnd(void)
{
		return TimerStsRead(&llUsart1RxFrameEnd,KILL_ON);
}

unsigned char* ReadUsart1RxData(void)
{
		return cUsart1RxData;
}

unsigned short *ReadUsart2RxCnt(void)
{
		return &wUsart2RxCnt;
}

unsigned char CheckUsart2RxFrameEnd(void)
{
		return TimerStsRead(&llUsart2RxFrameEnd,KILL_ON);
}

unsigned char* ReadUsart2RxData(void)
{
		return cUsart2RxData;
}

