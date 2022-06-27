#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "main.h"
#include "LCD_Config.h"
#include "Delay.h"
#include "spi.h"

//LCD重要参数集
typedef struct  
{										    
	uint16_t  width;			//LCD 宽度
	uint16_t  height;			//LCD 高度
	uint16_t  id;				  //LCD ID
	uint8_t   dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t	wramcmd;		//开始写gram指令
	uint16_t  setxcmd;		//设置x坐标指令
	uint16_t  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数


#define RED  	     0xf800
#define GREEN	     0x07e0
#define BLUE 	     0x001f
#define WHITE	     0xffff
#define BLACK	     0x0000
#define YELLOW     0xFFE0
#define GRAY0      0xEF7D   	  //灰色0
#define GRAY1      0x8410      	//灰色1
#define GRAY2      0x4208      	//灰色2 
       	

#define LCD_RS         	GPIO_PIN_0	//PE0--->>RS     控制脚
#define LCD_CS        	GPIO_PIN_1  //PE1--->>CS     片选脚
    		
#define LCD_SCL        	GPIO_PIN_5	//PA5--->>SC     时钟脚  SCK(SPI)
#define LCD_SDA        	GPIO_PIN_7	//PD7--->>DI     数据脚  MOSI(SPI)

//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOE,LCD_CS,GPIO_PIN_SET)
#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOE,LCD_RS,GPIO_PIN_SET)
#define	LCD_SDA_SET  	HAL_GPIO_WritePin(GPIOD,LCD_SDA,GPIO_PIN_SET)
#define	LCD_SCL_SET  	HAL_GPIO_WritePin(GPIOA,LCD_SCL,GPIO_PIN_SET)  

//液晶控制口置0操作语句宏定义
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
