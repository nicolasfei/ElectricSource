/*
 *  TM1640.h
 *  Created on: 2021��08��23��
 *  Author: LiYi
 */

#ifndef __TM1640_H
#define __TM1640_H


typedef struct
{
		void (*MCU_DATA_H)(void);
		void (*MCU_DATA_L)(void);
		void (*MCU_CLK_H)(void);
		void (*MCU_CLK_L)(void);
}MCU_DISP_PIN;	

/*
      TM1640_IO        MCU_IO
*/


#define AUTO_ADDR           0x40        // ��ַ�Զ���
#define MANUAL_ADDR         0x44        // �̶���ַ
#define DISP_START_ADDR     0xC0        // ��ʼ��ַ
#define DISP_ENABLE         0x8A        // ����ʾ
#define DISP_DISABLE        0x80        // ����ʾ 
#define BRIGHTNESS01        0x00        // ����1/16
#define BRIGHTNESS02        0x01        // ����2/16
#define BRIGHTNESS04        0x02        // ����4/16
#define BRIGHTNESS10        0x03        // ����10/16
#define BRIGHTNESS11        0x04        // ����11/16
#define BRIGHTNESS12        0x05        // ����12/16
#define BRIGHTNESS13        0x06        // ����13/16
#define BRIGHTNESS14        0x07        // ����14/16

#define DIG_VOLT1               0
#define DIG_VOLT2               1
#define DIG_VOLT3               2
#define DIG_VOLT4               3
#define DIG_AMP1                4
#define DIG_AMP2                5
#define DIG_AMP3                6
#define DIG_AMP4                7
#define DIG_LED9                8
#define DIG_LED10               9
#define DIG_LED11               10
#define DIG_LED12               11
#define DIG_LED13               12

void TM1640_IO_Init(void);
void TM1640_Disp_Init(void);
void TM1640_Disp_Update(unsigned char Num,unsigned short *DataBuf);

#endif
