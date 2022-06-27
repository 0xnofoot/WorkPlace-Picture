#include "Lcd_Driver.h"

/****************************************************************************
* ��    �ƣ�u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
* ��    �ܣ�STM32_Ӳ��SPI��дһ���ֽ����ݵײ㺯��
* ��ڲ�����Byte
* ���ڲ��������������յ�������
* ˵    ����STM32_Ӳ��SPI��дһ���ֽ����ݵײ㺯��
****************************************************************************/
void SPI_WriteByte(uint8_t TxData)
{
  HAL_SPI_Transmit(&hspi1,&TxData,1,10);
} 



/****************************************************************************
* ��    �ƣ�void Lcd_WriteIndex(u8 idx)
* ��    �ܣ�д ST7735S �������Ĵ�����ַ
* ��ڲ�����idx   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
* ���÷�����Lcd_WriteIndex(0x00);
****************************************************************************/
void Lcd_WriteIndex(uint8_t Index)
{
   //SPI д����ʱ��ʼ
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteByte(Index); 
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�void Lcd_WriteData(u8 dat)
* ��    �ܣ�д ST7735S �Ĵ�������
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ�����ǰ����д�Ĵ�����ַ���ڲ�����
* ���÷�����Lcd_WriteData(0x30)
****************************************************************************/
void Lcd_WriteData(uint8_t Data)
{

   LCD_CS_CLR;
   LCD_RS_SET; 
	 SPI_WriteByte(Data);	 
   LCD_CS_SET; 
}

void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
//	LCD_RST_CLR;
	  delay_ms(100);
//	LCD_RST_SET;
	  delay_ms(100);
}


//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//����LCD����
//������к�����ģʽ�л�
void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x2C;
	lcddev.dir=0;//����				 	 		
	lcddev.width=128;
	lcddev.height=160;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;	
	Lcd_WriteReg(0x36,0xC0);
}


/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�,Y_IncMode��ʾ������y������x
����ֵ����
*************************************************/
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{

	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end);
	
	Lcd_WriteIndex(0x2c); //��ʼд��GRAM

}

/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
	  Lcd_SetRegion(x+2,y+1,x+2,y+1);
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	
	Lcd_SetRegion(x+2,y+1,x+3,y+2);
	Lcd_WriteData(Data>>8);
	Lcd_WriteData(Data);

}    

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;

   Lcd_SetRegion(2,1,X_MAX_PIXEL+1,Y_MAX_PIXEL);
	
   Lcd_WriteIndex(0x2C);
	
 	for(i=0;i<Y_MAX_PIXEL;i++)
    for(m=0;m<X_MAX_PIXEL;m++)
    {	
	  	Lcd_WriteData(Color>>8);
			Lcd_WriteData(Color);
    } 		
}

void Lcd_Init(void)
{

	  Lcd_Reset();
    
		Lcd_WriteIndex(0x11);//Sleep exit 
		
		delay_ms (300);
			
		Lcd_WriteIndex(0xB1); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteIndex(0xB2); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteIndex(0xB3); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		//------------------------------------End ST7735S Frame Rate---------------------------------// 
		Lcd_WriteIndex(0xB4); //Dot inversion 
		Lcd_WriteData(0x03); 
		//------------------------------------ST7735S Power Sequence---------------------------------// 
		Lcd_WriteIndex(0xC0); 
		Lcd_WriteData(0x28); 
		Lcd_WriteData(0x08); 
		Lcd_WriteData(0x04); 
		Lcd_WriteIndex(0xC1); 
		Lcd_WriteData(0XC0); 
		Lcd_WriteIndex(0xC2); 
		Lcd_WriteData(0x0D); 
		Lcd_WriteData(0x00); 
		Lcd_WriteIndex(0xC3); 
		Lcd_WriteData(0x8D); 
		Lcd_WriteData(0x2A); 
		Lcd_WriteIndex(0xC4); 
		Lcd_WriteData(0x8D); 
		Lcd_WriteData(0xEE); 
		//---------------------------------End ST7735S Power Sequence-------------------------------------// 
		Lcd_WriteIndex(0xC5); //VCOM 
		Lcd_WriteData(0x1A); 
		Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
		Lcd_WriteData(0xC0); 
		//------------------------------------ST7735S Gamma Sequence---------------------------------// 
		Lcd_WriteIndex(0xE0); 
		Lcd_WriteData(0x04); 
		Lcd_WriteData(0x22); 
		Lcd_WriteData(0x07); 
		Lcd_WriteData(0x0A); 
		Lcd_WriteData(0x2E); 
		Lcd_WriteData(0x30); 
		Lcd_WriteData(0x25); 
		Lcd_WriteData(0x2A); 
		Lcd_WriteData(0x28); 
		Lcd_WriteData(0x26); 
		Lcd_WriteData(0x2E); 
		Lcd_WriteData(0x3A); 
		Lcd_WriteData(0x00); 
		Lcd_WriteData(0x01); 
		Lcd_WriteData(0x03); 
		Lcd_WriteData(0x13); 
		Lcd_WriteIndex(0xE1); 
		Lcd_WriteData(0x04); 
		Lcd_WriteData(0x16); 
		Lcd_WriteData(0x06); 
		Lcd_WriteData(0x0D); 
		Lcd_WriteData(0x2D); 
		Lcd_WriteData(0x26); 
		Lcd_WriteData(0x23); 
		Lcd_WriteData(0x27); 
		Lcd_WriteData(0x27); 
		Lcd_WriteData(0x25); 
		Lcd_WriteData(0x2D); 
		Lcd_WriteData(0x3B); 
		Lcd_WriteData(0x00); 
		Lcd_WriteData(0x01); 
		Lcd_WriteData(0x04); 
		Lcd_WriteData(0x13); 
		//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
		Lcd_WriteIndex(0x3A); //65k mode 
		Lcd_WriteData(0x05); 
		Lcd_WriteIndex(0x29); //Display on 

    LCD_SetParam();//����LCD����	 
}

