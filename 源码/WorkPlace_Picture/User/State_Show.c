#include "State_Show.h"

void State_Show_Init(void)
{
	Lcd_Init();
	Lcd_Clear(WHITE);
	Gui_DrawLine(14,5,114,5,BLACK);
	Gui_DrawLine(114,5,114,105,BLACK);
	Gui_DrawLine(114,105,14,105,BLACK);
	Gui_DrawLine(14,105,14,5,BLACK);
	Gui_DrawFont_GBK24(10,120, BLUE,WHITE, "MODE:");
	//Gui_DrawFont_GBK24(50,120, BLUE,WHITE, " ");
}

void Place_Show(uint16_t X,uint16_t Y)
{
	Gui_Circle(X,Y,4,RED); 
}
