#ifndef __USART_H
#define __USART_H

#include "gd32f4xx.h"

#define MAX_RX_CNT 500

#define RS485_CTL_TX()   gpio_bit_set(GPIOD,GPIO_PIN_7)    
#define RS485_CTL_RX()   gpio_bit_reset(GPIOD,GPIO_PIN_7)


void Usart1_init(int iBoundRate);
void Usart2_init(int iBoundRate);

void UsartSendData(unsigned int usart_periph,unsigned char *wTxData,unsigned char len);

unsigned short *ReadUsart1RxCnt(void);
unsigned char CheckUsart1RxFrameEnd(void);
unsigned char* ReadUsart1RxData(void);

unsigned short *ReadUsart2RxCnt(void);
unsigned char CheckUsart2RxFrameEnd(void);
unsigned char* ReadUsart2RxData(void);


#endif













