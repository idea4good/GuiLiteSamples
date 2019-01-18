//
// Created by song on 17-5-9.
//

#ifndef MOS_COLOR_H
#define MOS_COLOR_H


#include "stdint.h"

uint16_t R888T565(uint32_t);

uint32_t R565T888(uint16_t);

uint16_t colorBlend(uint32_t colorFore, uint32_t colorBack, float alpha);

#endif //MOS_COLOR_H
