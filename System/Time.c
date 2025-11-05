#include "Time.h"

// 用于存储系统运行的毫秒数
static volatile uint32_t g_milliticks = 0;

// 初始化SysTick定时器，设置为1ms中断一次
void Time_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		// SysTick_Config 失败时的捕获
		while (1);
	}
}

// SysTick中断服务函数，每1ms自动调用一次
void SysTick_Handler(void)
{
	g_milliticks++; // 毫秒数自增
}

// 获取当前系统运行的毫秒数
uint32_t Time_GetMillis(void)
{
	return g_milliticks;
}

// 毫秒级延时 (非阻塞式，应避免在主循环中使用)
void Time_DelayMs(uint32_t nMs)
{
	uint32_t start = Time_GetMillis();
	while (Time_GetMillis() - start < nMs)
	{
		// 等待
	}
}
