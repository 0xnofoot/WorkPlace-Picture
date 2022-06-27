#include "openmv.h"
#include "usart.h"

Coor_Type Coor_test;

void Date_Openmv_Receive_Init(void)
{
	uint8_t uart4_start;
	HAL_UART_Receive_IT(&huart4,&uart4_start,1);
}

/*坐标数据解析函数，仅支持8位数据，即0--255，改变数据大小可更改C代码和openmv代码*/
void Data_analysis_Openmv(uint8_t data)
{
    static uint8_t RxBuffer[16];
    static uint8_t _data_cnt = 0;
    static uint8_t state = 0;
 
    if(state==0&&data==TITLE1)
    {
        state=1;
    }
    else if(state==1&&data==TITLE2)
    {
        state=2;
        _data_cnt = 0;
    }
    else if(state==2)
    {
			RxBuffer[_data_cnt] = data;
			_data_cnt++;
			if(_data_cnt == 16)
			{
				_data_cnt = 0;
				state = 0;
				Coor_test.coor_x1 = RxBuffer[0];
				Coor_test.coor_y1 = RxBuffer[4];
				Coor_test.coor_x2 = RxBuffer[8];
				Coor_test.coor_y2 = RxBuffer[12];
				//printf("x1:%d\ny1:%d\nx2:%d\ny2:%d\n",Coor_test.coor_x1,Coor_test.coor_y1,Coor_test.coor_x2,Coor_test.coor_y2);
			}
    }
    else state = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  static uint8_t fifo;
	if(huart->Instance == huart4.Instance)
	{
		HAL_UART_Receive_IT(&huart4,&fifo,1);
		Data_analysis_Openmv(fifo);
	}
}

