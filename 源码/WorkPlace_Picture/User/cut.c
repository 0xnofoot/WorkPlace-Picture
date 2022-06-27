#include "cut.h"
#include "tim.h"
#include "data_analysis.h"
#include "Motor.h"
#include "usart.h"
#include "delay.h"

void Cut_Init(void)
{
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
}

void Cut_Start(void)
{
	//HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,1400);
}

void Cut_Stop(void)
{
	HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
}


/*以下是测试代码*/
/*在cut.c中暂留*/
void Cut_Rec(void)
{
	uint8_t i = 7;
	Cut_Init();
	delay_ms(2000);
	Motor_Init();
	Motor_Action(0,48,0,60);
	delay_ms(15000);
	Cut_Start();
	Motor_Action_z(0,34);
	delay_ms(8000);
	
	while(i--)
	{	
//		Line_Analysis(15,20,55,20);
//		delay_ms(500);
//		Line_Analysis(55,20,55,50);
//		delay_ms(500);
//		Line_Analysis(55,50,15,50);
//		delay_ms(500);
//		Line_Analysis(15,50,15,20);
//		delay_ms(500);
//		Motor_Action_z(0,0.2);
//		delay_ms(500);
		
//		Cycle_Analysis(0,0,20);
//		delay_ms(500);
//		Motor_Action_z(0,0.2);
//		delay_ms(500);

		Line_Analysis(48,83,68,83);
		delay_ms(500);
		Line_Analysis(68,83,75,102);
		delay_ms(500);
		Line_Analysis(75,102,81,83);
		delay_ms(500);
		Line_Analysis(81,83,101,83);
		delay_ms(500);
		Line_Analysis(101,83,85,71);
		delay_ms(500);
		Line_Analysis(85,71,91,52);
		delay_ms(500);
		Line_Analysis(91,52,75,64);
		delay_ms(500);
		Line_Analysis(75,64,58,52);
		delay_ms(500);
		Line_Analysis(58,52,65,71);
		delay_ms(500);
		Line_Analysis(65,71,48,83);
		delay_ms(500);
		Motor_Action_z(0,0.2);
		delay_ms(500);		
	}
	Cut_Stop();
	Motor_Stop();
}




