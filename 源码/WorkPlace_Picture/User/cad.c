#include "cad.h"
#include "usart.h"


void Date_Cad_Receive_Init(void)
{
	uint8_t uart3_start;
	HAL_UART_Receive_IT(&huart3,&uart3_start,1);
}

static uint16_t len = 0;
static uint16_t data_pic[100];

/*CAD数据解析函数*/
void Data_analysis_Cad(uint8_t data)
{
    static uint8_t state = 0;
    if(state==0&&data==TITLE_START1)
    {
        state=1;
    }
    else if(state==1&&data==TITLE_START2)
    {
        state=2;

    }
    else if(state==2)
    {
			data_pic[len] = data;
			len++;
		}

		if(state==2&&data==TITLE_STOP1)
		{
			state=3;
		}
		else if(state==3&&data==TITLE_STOP2)
		{
			state=0;
		}
    else state = 0;
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  static uint8_t fifo;
//	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_7);
//	
//	if(huart->Instance == huart3.Instance)
//	{
//		HAL_UART_Receive_IT(&huart3,&fifo,1);
//		//printf("%x\n",fifo);
//		Data_analysis_Cad(fifo);
//	}
//}

