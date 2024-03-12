
#ifndef __GETTEMP_H
#define __GETTEMP_H

#include "gd32f4xx.h"

typedef struct
{
		void (*TEMP_OUT_DQ)(void);
		void (*TEMP_IN_DQ)(void);
		void (*TEMP_CLR_DQ)(void);
		void (*TEMP_SET_DQ)(void);
		unsigned char (*TEMP_GET_DQ)(void);
}TEMP_DQ;

typedef struct
{
		short Temp1;
		short Temp2;
}TEMP_VALUE;

TEMP_VALUE GetTempTask(unsigned char Chan);
TEMP_VALUE* ReadTemp(void);


#endif   /*__GETTEMP_H_*/

