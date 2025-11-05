// Time.h
#ifndef __TIME_H
#define __TIME_H

#include "stm32f10x.h"

void Time_Init(void);
uint32_t Time_GetMillis(void);
void Time_DelayMs(uint32_t nMs);

#endif
