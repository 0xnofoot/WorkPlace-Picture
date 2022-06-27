#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "main.h"
#include "LCD_Config.h"
#include "Delay.h"
#include "spi.h"

//LCD��Ҫ������
typedef struct  
{										    
	uint16_t  width;			//LCD ���
	uint16_t  height;			//LCD �߶�
	uint16_t  id;				  //LCD ID
	uint8_t   dir;			  //���������������ƣ�0��������1��������	
	uint16_t	wramcmd;		//��ʼдgramָ��
	uint16_t  setxcmd;		//����x����ָ��
	uint16_t  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����


#define RED  	     0xf800
#define GREEN	     0x07e0
#define BLUE 	     0x001f
#define WHITE	     0xffff
#define BLACK	     0x0000
#define YELLOW     0xFFE0
#define GRAY0      0xEF7D   	  //��ɫ0
#define GRAY1      0x8410      	//��ɫ1
#define GRAY2      0x4208      	//��ɫ2 
       	

#define LCD_RS         	GPIO_PIN_0	//PE0--->>RS     ���ƽ�
#define LCD_CS        	GPIO_PIN_1  //PE1--->>CS     Ƭѡ��
    		
#define LCD_SCL        	GPIO_PIN_5	//PA5--->>SC     ʱ�ӽ�  SCK(SPI)
#define LCD_SDA        	GPIO_PIN_7	//PD7--->>DI     ���ݽ�  MOSI(SPI)

//Һ�����ƿ���1�������궨��
#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOE,LCD_CS,GPIO_PIN_SET)
#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOE,LCD_RS,GPIO_PIN_SET)
#define	LCD_SDA_SET  	HAL_GPIO_WritePin(GPIOD,LCD_SDA,GPIO_PIN_SET)
#define	LCD_SCL_SET  	HAL_GPIO_WritePin(GPIOA,LCD_SCL,GPIO_PIN_SET)  

//Һ�����ƿ���0�������궨��
#define	LCD_CS_CLR  	HAL_GPIO_WritePin(GPIOE,LCD_CS,GPIO_PIN_RESET)    
#define	LCD_RS_CLR  	HAL_GPIO_WritePin(GPIOE,LCD_RS,GPIO_PIN_RESET)   
#define	LCD_SDA_CLR  	HAL_GPIO_WritePin(GPIOD,LCD_SDA,GPIO_PIN_RESET)   
#define	LCD_SCL_CLR  	HAL_GPIO_WritePin(GPIOA,LCD_SCL,GPIO_PIN_RESET)    
 

void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);


#endif /*__LCD_DRIVER_H*/
