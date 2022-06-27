#ifndef __LCD_CONFIG_H
#define __LCD_CONFIG_H


//==================================如何切换横竖屏显示=======================================//
//打开Lcd_Driver.h头文件，修改宏#define USE_HORIZONTAL 值为0使用竖屏模式.1,使用横屏模式
//===========================如何切换模拟SPI总线驱动和硬件SPI总线驱动=========================//
//打开Lcd_Driver.h头文件，修改宏#define USE_HARDWARE_SPI  值为0使用模拟SPI总线.1,使用硬件SPI总线

//定义LCD的尺寸
#if USE_HORIZONTAL==1	//使用横屏
#define X_MAX_PIXEL	        160
#define Y_MAX_PIXEL	        128
#else
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160
#endif


#endif  /*__LCD_CONFIG_H*/
