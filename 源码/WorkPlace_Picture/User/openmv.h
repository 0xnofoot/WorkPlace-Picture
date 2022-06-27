#ifndef __OPENMV_H
#define __OPENMV_H

#include "main.h"

#define TITLE1   0XAA
#define TITLE2   0XAE

typedef struct Line_Coor
{
	uint8_t coor_x1; 
	uint8_t coor_y1; 
	uint8_t coor_x2; 
  uint8_t coor_y2;
}Coor_Type;

extern Coor_Type Coor_test;

void Date_Openmv_Receive_Init(void);
void Data_analysis_Openmv(uint8_t data);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /*__OPENMV_H*/

