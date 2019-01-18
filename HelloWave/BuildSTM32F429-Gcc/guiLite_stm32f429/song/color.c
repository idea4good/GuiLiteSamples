//
// Created by song on 17-5-9.
//

#include "color.h"
#include "usart.h"

uint16_t R888T565(uint32_t color) {
    uint16_t c;
    uint8_t r = (uint8_t) (color >> 16) >> 3;
    uint8_t g = (uint8_t) ((color << 16) >> 24) >> 2;
    uint8_t b = (uint8_t) ((color << 24) >> 24) >> 3;
    c = (r << 11) | (g << 5) | (b << 0);
    return c;
}

uint32_t R565T888(uint16_t color) {
    uint32_t c;
    uint8_t r = (uint8_t) (color >> 11) << 3;
    uint8_t g = (uint8_t) ((color << 5) >> 11) << 2;
    uint8_t b = (uint8_t) ((color << 11) >> 11) << 3;
    c = (r << 16) | (g << 8) | (b << 0);
    return c;
}

uint16_t colorBlend(uint32_t colorFore, uint32_t colorBack, float alpha) {
    uint16_t c = 0;

    uint8_t rf = (uint8_t) (colorFore >> 16);
    uint8_t gf = (uint8_t) ((colorFore << 16) >> 24);
    uint8_t bf = (uint8_t) ((colorFore << 24) >> 24);

    uint8_t rb = (uint8_t) (colorBack >> 16);
    uint8_t gb = (uint8_t) ((colorBack << 16) >> 24);
    uint8_t bb = (uint8_t) ((colorBack << 24) >> 24);

    uint8_t r = (uint8_t) ((rf * alpha) + (rb * (1 - alpha)));
    uint8_t g = (uint8_t) ((gf * alpha) + (gb * (1 - alpha)));
    uint8_t b = (uint8_t) ((bf * alpha) + (bb * (1 - alpha)));

    r >>= 3;
    g >>= 2;
    b >>= 3;

    c = (r << 11) | (g << 5) | (b << 0);
    return c;
}

