#ifndef __DATA_ANALYSIS_H
#define __DATA_ANALYSIS_H

#include "main.h"

extern int16_t cycle_coor[5000][2];

void Cycle_Analysis(int16_t X,int16_t Y,uint16_t R);
void Line_Analysis(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

#endif /*__DATA_ANALYSIS_H*/

