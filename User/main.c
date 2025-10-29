#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "LightSensor2.h"

uint8_t KeyNum;

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();
	LightSensor_Init2();
	while(1)
	{
		if (LightSensor_Get() == 1 ||LightSensor2_Get()==1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
		

	}
}
