#ifndef __CLIPPING_H
#define __CLIPPING_H 	

#define MaxMinLimit(x,max,min)  x = ((x) > (max)) ? (max) : (((x) < (min)) ? (min) : (x))

#define MaxLimit(x,max)   x = ((x) > (max)) ? (max) : (x)

#define MinLimit(x,min)   x = ((x) < (min)) ? (min) : (x)


#endif
