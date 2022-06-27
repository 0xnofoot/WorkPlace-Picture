#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

extern uint8_t flag_x;
extern uint8_t flag_y;
extern uint8_t flag_z;

void Motor_Start(void);
void Motor_Stop(void);
void Motor_Action(int16_t x0,int16_t x1,int16_t y0,int16_t y1);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void Motor_Action_z(float z0,float z1);
void Motor_Init(void);

#endif /*__MOTOR_H*/

