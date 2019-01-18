//
// Created by song on 17-6-1.
//

#ifndef MOS_ANTIALIASING_H
#define MOS_ANTIALIASING_H



#include "sys.h"
#include "ltdc.h"

uint16_t ipart(double x);

float fpart(float x);

float rfpart(float x);

void ltdc_aa_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color, uint32_t backcolor);




void ltdc_aa_arc(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t degFrom, uint16_t degTo, uint32_t color,
                 uint32_t backcolor);

void ltdc_aa_farc(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t degFrom, uint16_t degTo, uint32_t color,
                  uint32_t backcolor);


void ltdc_aa_ring(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t r2, uint16_t degFrom, uint16_t degTo, uint32_t color,
                  uint32_t backcolor);

uint16_t max(uint16_t x0, uint16_t x1);

uint16_t min(uint16_t x0, uint16_t x1);

//void DrawArch( int r );
//double DC(int r, int y);

#endif //MOS_ANTIALIASING_H
