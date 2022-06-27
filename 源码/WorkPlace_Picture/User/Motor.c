#include "Motor.h"
#include "tim.h"
#include "usart.h"
#include "data_analysis.h"

int16_t x_dis = 0;
int16_t y_dis = 0;
float   z_dis = 0;
uint8_t flag_x = 0;
uint8_t flag_y = 0;
uint8_t flag_z = 0;

static void Motor_Action_x(int16_t x0,int16_t x1);
static void Motor_Action_y(int16_t y0,int16_t y1);


void Motor_Init(void)
{
  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6) == GPIO_PIN_RESET)
		{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
		}
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_8) == GPIO_PIN_RESET)
		{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
		}
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_10) == GPIO_PIN_RESET)
		{
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		}
		
		if(!(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6)|HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_8)|HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_10)))
		{
			break;
		}
	}
}

void Motor_Start(void)
{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

void Motor_Stop(void)
{
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
}

static void Motor_Action_x(int16_t x0,int16_t x1)
{
	x_dis = x1 - x0;
	x_dis = 25*x_dis;
	
	if(x_dis>0) 
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_7) == GPIO_PIN_RESET) return;
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_SET);	
	}
	else if(x_dis<0)
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6) == GPIO_PIN_RESET) return;
		x_dis = 0-x_dis;
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_RESET);	
	}
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
	flag_x = 1;
}

static void Motor_Action_y(int16_t y0,int16_t y1)
{
	y_dis = y1 - y0;
	y_dis = 25*y_dis;
	
	if(y_dis>0) 
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_9) == GPIO_PIN_RESET) return;
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_SET);	
	}
	else if(y_dis<0)
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_8) == GPIO_PIN_RESET) return;
		y_dis = 0-y_dis;
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_RESET);	
	}
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	flag_y = 1;
}

void Motor_Action_z(float z0,float z1)
{
	z_dis = z1 - z0;
	z_dis = 25*z_dis;
	
	if(z_dis>0) 
	{
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_SET);	
	}
	else if(z_dis<0)
	{
		if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_10) == GPIO_PIN_RESET) return;
		z_dis = 0-z_dis;
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_RESET);	
	}
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
	flag_z = 1;
}

void Motor_Action(int16_t x0,int16_t x1,int16_t y0,int16_t y1)
{
	Motor_Action_x(x0,x1);
	Motor_Action_y(y0,y1);
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == htim2.Instance)
	{
		if(flag_x)
		{
			if(x_dis == 0)
				{
					HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
					flag_x = 0;
				}
			 x_dis--;
		}
	}
	
	else if(htim->Instance == htim3.Instance)
	{
		if(flag_y)
		{
			if(y_dis == 0)
				{
					HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
					flag_y = 0;
				}
			 y_dis--;
		}
	}
	
	else if(htim->Instance == htim4.Instance)
	{

		if(flag_z)
		{
			if(z_dis == 0)
				{
					HAL_TIM_PWM_Stop_IT(&htim4, TIM_CHANNEL_1);
					flag_z = 0;
				}
			 z_dis--;
		}
	}
}



