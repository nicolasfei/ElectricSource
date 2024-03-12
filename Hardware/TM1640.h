/*
 *  TM1640.h
 *  Created on: 2021年08月23日
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


#define AUTO_ADDR           0x40        // 地址自动加
#define MANUAL_ADDR         0x44        // 固定地址
#define DISP_START_ADDR     0xC0        // 开始地址
#define DISP_ENABLE         0x8A        // 开显示
#define DISP_DISABLE        0x80        // 关显示 
#define BRIGHTNESS01        0x00        // 亮度1/16
#define BRIGHTNESS02        0x01        // 亮度2/16
#define BRIGHTNESS04        0x02        // 亮度4/16
#define BRIGHTNESS10        0x03        // 亮度10/16
#define BRIGHTNESS11        0x04        // 亮度11/16
#define BRIGHTNESS12        0x05        // 亮度12/16
#define BRIGHTNESS13        0x06        // 亮度13/16
#define BRIGHTNESS14        0x07        // 亮度14/16

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
