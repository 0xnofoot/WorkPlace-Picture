#ifndef __LCD_CONFIG_H
#define __LCD_CONFIG_H


//==================================����л���������ʾ=======================================//
//��Lcd_Driver.hͷ�ļ����޸ĺ�#define USE_HORIZONTAL ֵΪ0ʹ������ģʽ.1,ʹ�ú���ģʽ
//===========================����л�ģ��SPI����������Ӳ��SPI��������=========================//
//��Lcd_Driver.hͷ�ļ����޸ĺ�#define USE_HARDWARE_SPI  ֵΪ0ʹ��ģ��SPI����.1,ʹ��Ӳ��SPI����

//����LCD�ĳߴ�
#if USE_HORIZONTAL==1	//ʹ�ú���
#define X_MAX_PIXEL	        160
#define Y_MAX_PIXEL	        128
#else
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160
#endif


#endif  /*__LCD_CONFIG_H*/
