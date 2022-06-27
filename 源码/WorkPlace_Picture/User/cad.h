#ifndef __CAD_H
#define __CAD_H

#include "main.h"

#define TITLE_START1   0XAA
#define TITLE_START2   0XBB

#define TITLE_STOP1    0XCC
#define TITLE_STOP2    0XDD

#define TITLE_LINEC1    0XEA
#define TITLE_LINEC2    0XEE

#define TITLE_LINEO1    0XDA
#define TITLE_LINEO2    0XDD

#define TITLE_CIR1    0XFA
#define TITLE_CIR2    0XFF

typedef struct Line_Coor
{
	uint8_t coor_x1; 
	uint8_t coor_y1; 
	uint8_t coor_x2; 
  uint8_t coor_y2;
}Coor_Type;



void Date_Cad_Receive_Init(void);
void Data_analysis_cad(uint8_t data);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /*__CAD_H*/

