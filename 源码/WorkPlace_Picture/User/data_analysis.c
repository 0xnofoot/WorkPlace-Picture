#include "data_analysis.h"
#include "Motor.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"

int16_t cycle_coor_original[5000][2]; //初始坐标数据
int16_t cycle_coor_filter[5000][2];   //过滤后的第四象限坐标数据
int16_t cycle_coor[5000][2];           //重新拼接后的坐标数据，即最终数据

/*坐标数据过滤，提取出第四象限坐标*/
static uint16_t Coor_Filter(int16_t X, int16_t Y, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t length_filter;
	for(i = 0;i < length;i++)
	{
		if((cycle_coor_original[i][0] < X)&&(cycle_coor_original[i][1] >= Y))
		{
			cycle_coor_filter[j][0] = cycle_coor_original[i][0];
			cycle_coor_filter[j][1] = cycle_coor_original[i][1];
			j++;
		}
	}
	length_filter = j;
	return length_filter;
}

/*冒泡排序，将第四象限点连续化*/
static void Cycle_BubbleSort(uint16_t len) 
{
    int16_t temp;
    int i, j;
    for (i=0; i<len-1; i++)
	{
		        for (j=0; j<len-1-i; j++) 
	     { 
            if (cycle_coor_filter[j][0] > cycle_coor_filter[j+1][0]) 
					 {
                temp = cycle_coor_filter[j][0];
                cycle_coor_filter[j][0] = cycle_coor_filter[j+1][0];
                cycle_coor_filter[j+1][0] = temp;
							
                temp = cycle_coor_filter[j][1];
                cycle_coor_filter[j][1] = cycle_coor_filter[j+1][1];
                cycle_coor_filter[j+1][1] = temp;							
            }
        }
	}
	
}

/*初始坐标数据保存*/
static void Cycle_Data_save(int32_t x,int32_t y,uint8_t flag)
{
	static uint16_t len = 0;
	if(flag) 
	{
		len = 0;
		return;
	}
	cycle_coor_original[len][0] = x;
	cycle_coor_original[len][1] = y;	
	len++;
}

/*Bresenham算法,画圆函数*/
static uint16_t Circle_Bresenham(int16_t X,int16_t Y,uint16_t R) 
{
    int8_t  a; 
	  int8_t  b;
    int32_t c; 
	  uint16_t length = 0;
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
      { 
        Cycle_Data_save(X+a,Y+b,0);     //        7 
        Cycle_Data_save(X-a,Y+b,0);     //        6 
        Cycle_Data_save(X+a,Y-b,0);     //        2 
        Cycle_Data_save(X-a,Y-b,0);     //        3 
        Cycle_Data_save(X+b,Y+a,0);     //        8 
        Cycle_Data_save(X-b,Y+a,0);     //        5 
        Cycle_Data_save(X+b,Y-a,0);     //        1 
        Cycle_Data_save(X-b,Y-a,0);     //        4 	

				length = length+8;				
        if (c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a = a + 1; 
    }
	
    if (a==b) 
      { 
        Cycle_Data_save(X+a,Y+b,0); 
        Cycle_Data_save(X+a,Y+b,0); 
        Cycle_Data_save(X+a,Y-b,0); 
        Cycle_Data_save(X-a,Y-b,0); 
        Cycle_Data_save(X+b,Y+a,0); 
        Cycle_Data_save(X-b,Y+a,0); 
        Cycle_Data_save(X+b,Y-a,0); 
        Cycle_Data_save(X-b,Y-a,0);
				length = length+8;				
     } 
			
	  Cycle_Data_save(0,0,1);
	  return length;
} 

static uint16_t Cycle_Coor_Connect(int16_t X, int16_t Y, int16_t length)
{
	uint16_t i = 0;
	uint16_t len;
	for(i=i; i < length; i++)
	{
			cycle_coor[i][0] = cycle_coor_filter[i][0];
			cycle_coor[i][1] = cycle_coor_filter[i][1];
	}
	
		for(i=i; i < 2*length; i++)
	{
			cycle_coor[i][0] = X + (cycle_coor_filter[i-length][1] - Y);//x = x0 +(y - y0)
			cycle_coor[i][1] = Y + (X - cycle_coor_filter[i-length][0]);//y = y0 + (x0 -x)
	}
	
		for(i=i; i < 3*length; i++)
	{
			cycle_coor[i][0] = X + (X - cycle_coor_filter[i-2*length][0]);//x = x0 + (x0 - x)
			cycle_coor[i][1] = Y - (cycle_coor_filter[i-2*length][1] - Y);//y = y0 - (y - y0)
	}
	
		for(i=i; i < 4*length; i++)
	{
			cycle_coor[i][0] = X - (cycle_coor_filter[i-3*length][1] - Y);//x = x0 - (y - y0)
			cycle_coor[i][1] = Y - (X - cycle_coor_filter[i-3*length][0]);//y = y0 - (x0 - x)
	}
	
	len = 4*length;
//    for (i=0; i<len; i++)
//	{
//		printf("x = %d,y = %d\n",cycle_coor[i][0],cycle_coor[i][1]);
//	}
	return len;
}

void Data_Cycle_Reset(uint16_t len_original,uint16_t len_filter,uint16_t len)
{
	uint16_t i;
	for(i = 0; i < len_original; i++)
	{
		cycle_coor_original[i][0] = 0;
		cycle_coor_original[i][1] = 0;
	}
	
		for(i = 0; i < len_filter; i++)
	{
		cycle_coor_filter[i][0] = 0;
		cycle_coor_filter[i][1] = 0;
	}
	
		for(i = 0; i < len; i++)
	{
		cycle_coor[i][0] = 0;
		cycle_coor[i][1] = 0;
	}
	

}

//int16_t cycle_coor[5000][2];           //重新拼接后的坐标数据，即最终数据

void Cycle_Analysis(int16_t X,int16_t Y,uint16_t R)
{
	uint16_t length_original;//原始坐标数据长度
	uint16_t length_filter;//过滤后坐标数据的长度
	uint16_t length;//最终坐标数据的长度
	uint16_t i = 0;
	
	length_original = Circle_Bresenham(X, Y, R);//画圆算法
	length_filter = Coor_Filter(X, Y, length_original);//数据过滤
	Cycle_BubbleSort(length_filter);//冒泡排序
	length = Cycle_Coor_Connect(X , Y, length_filter);//数据重拼接
	
	/*此处调用圆切割函数*/
	
		for(i = 0; i < length-1; i++)
	{
		while(flag_x|flag_y)
		{
		}
		Motor_Action(cycle_coor[i][0],cycle_coor[i+1][0],cycle_coor[i][1],cycle_coor[i+1][1]);
		delay_ms(500);
	}
	
	Data_Cycle_Reset(length_original, length_filter, length);//数据复位
}


int16_t line_coor[5000][2]; 

/*坐标数据保存函数*/
static void Line_Data_save(int16_t x,int16_t y,uint8_t flag)
{
		static uint16_t len = 0;
		if(flag) 
	{
		len = 0;
		return;
	}
	
	line_coor[len][0] = x;
	line_coor[len][1] = y;	
	len++;
}

static uint16_t Line_Bresenham(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)   
{
	int16_t dx, dy;   
  int16_t dx2, dy2;    
  int16_t x_inc, y_inc;
  int16_t error, index;
	uint16_t length = 0;
	dx = x1-x0;
	dy = y1-y0;

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)
	{
		error = dy2 - dx; 
		for (index=0; index <= dx; index++)
		{
			Line_Data_save(x0,y0,0);
			length++;
			if (error >= 0) 
			{
				error-=dx2;
				y0+=y_inc;
			} 
			error = error + dy2;
			x0 = x0 + x_inc;
		}
	}
	else
	{
		error = dx2 - dy; 

		for (index=0; index <= dy; index++)
		{

			Line_Data_save(x0,y0,0);
			length++;
			if (error >= 0)
			{
				error = error - dy2;
				x0 =x0 + x_inc;
			} 
			error =error + dx2;

			y0 =y0 + y_inc;
		} 
	} 
	Line_Data_save(0,0,1);

	return length;
}


void Data_Line_Reset(int16_t len)
{
	uint16_t i;
	for(i = 0; i < len; i++)
	{
		line_coor[i][0] = 0;
		line_coor[i][1] = 0;
	}
}

//int16_t line_coor[5000][2];

void Line_Analysis(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
	uint16_t length;
	uint16_t i;
	length = Line_Bresenham(x0, y0 ,x1, y1);
	/*此处调用线条切割函数*/
	/**/
	for(i = 0; i < length-1; i++)
	{
		while(flag_x|flag_y)
		{
		}
		Motor_Action(line_coor[i][0],line_coor[i+1][0],line_coor[i][1],line_coor[i+1][1]);

	}

	Data_Line_Reset(length);
}
