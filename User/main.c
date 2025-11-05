#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "LightSensor2.h"

uint8_t KeyNum;

// 初始化LightSensor的状态变量
uint8_t S1_State = 0;         // 0: 未遮挡, 1: 已遮挡
uint32_t S1_StartTime = 0;    // 遮挡开始的毫秒时间戳
uint32_t S1_LastDuration = 0; // 上一次遮挡的持续时间 (ms)

// 初始化LightSensor2的状态变量
uint8_t S2_State = 0;         // 0: 未遮挡, 1: 已遮挡
uint32_t S2_StartTime = 0;    // 遮挡开始的毫秒时间戳
uint32_t S2_LastDuration = 0; // 上一次遮挡的持续时间 (ms)



int main(void)
{
	Buzzer_Init();
	LightSensor_Init();
	LightSensor2_Init();
	Time_Init();
	
	// --- 新增：OLED 初始化 ---
	OLED_Init();         // 初始化OLED
	OLED_Clear();        // 清空屏幕
	
	// --- 新增：显示静态UI文本 ---
	// (OLED_ShowString的参数：行, 列, 字符串)
	OLED_ShowString(1, 1, "S1 Time:");
	OLED_ShowString(2, 1, "S2 Time:");
	OLED_ShowString(1, 14, "ms");
	OLED_ShowString(2, 14, "ms");

	// --- 新增：显示初始的遮挡时间 (0) ---
	// (OLED_ShowNum的参数：行, 列, 数字, 显示长度)
	OLED_ShowNum(1, 9, S1_LastDuration, 5);
	OLED_ShowNum(2, 9, S2_LastDuration, 5);
	
	while(1)
	{
		uint32_t currentTime = Time_GetMillis(); // 获取当前时间
		
		
		uint8_t s1_current = LightSensor_Get();
		

		if (s1_current == 1 && S1_State == 0) 
		{
			S1_State = 1; // 更新状态为“已遮挡”
			S1_StartTime = currentTime; // 记录遮挡开始时间
			//Buzzer_ON();
		}
		
		else if (s1_current == 0 && S1_State == 1) 
		{
			S1_State = 0; // 更新状态为“未遮挡”
			S1_LastDuration = currentTime - S1_StartTime; // 计算持续时间
			OLED_ShowNum(1, 9, S1_LastDuration, 5);
		}
		
		
		uint8_t s2_current = LightSensor2_Get();

		if (s2_current == 1 && S2_State == 0) 
		{
			S2_State = 1; // 更新状态为“已遮挡”
			S2_StartTime = currentTime; // 记录遮挡开始时间
			//Buzzer_ON();
		}
		
		else if (s2_current == 0 && S2_State == 1) 
		{
			S2_State = 0; // 更新状态为“未遮挡”
			S2_LastDuration = currentTime - S2_StartTime; // 计算持续时间
			OLED_ShowNum(2, 9, S2_LastDuration, 5);
			//Buzzer_OFF();
		}
		

		// 蜂鸣器控制
		//if (S1_State == 0 && S2_State == 0)
		//{
		//	Buzzer_OFF();
		//}

	}
}
