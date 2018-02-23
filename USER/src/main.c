#include "main.h"

/* ========================================================================== */
int main(void)
{
	InitRCC();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	InitLED();
	InitSPI1();
	InitLIS3DSH();
	
	Identity_LIS3DSH();
	
	while (1)
	{
		TestLIS3DSH();				
	}	
}


/* ========================================================================== */
void SysTick_Handler()
{

}
