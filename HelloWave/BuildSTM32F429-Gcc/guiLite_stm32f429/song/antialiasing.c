//
// Created by song on 17-6-1.
//

#include "stdlib.h"
#include "math.h"
#include "antialiasing.h"
#include "color.h"

uint16_t ipart(double x) {
    return (uint16_t) x;
}

float fpart(float x) {
    return (float) (x - floor(x));
}

float rfpart(float x) {
    return (float) (1.0 - fpart(x));
}

void ltdc_aa_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color, uint32_t backcolor) {
    uint8_t steep = (uint8_t) (abs(y1 - y0) > abs(x1 - x0));
//    if (steep) {
//        if (y0 > y1) {
//            ltdc_aa_line(x1, y1, x0, y0, color, backcolor);
//        }
//    }
////        ltdc_aa_line(y0, x0, y1, x1, color, backcolor);
//    if (x0 > x1)
//        ltdc_aa_line(x1, y1, x0, y0, color, backcolor);
    uint16_t tmp;
    uint16_t tmp1;
//    if (steep) {
//        if (y0 > y1) {
//            tmp = x0;
//            x0 = x1;
//            x1 = tmp;
//            tmp1 = y0;
//            y0 = y1;
//            y1 = tmp1;
//        }
//    } else {
//        if (x0 > x1) {
//
//            tmp = x0;
//            x0 = x1;
//            x1 = tmp;
//            tmp1 = y0;
//            y0 = y1;
//            y1 = tmp1;
//        }
//    }

    int16_t dx = (x1 - x0);
    int16_t dy = (y1 - y0);
    float gradient = 0;
    if (steep) {
        gradient = (float) ((1.0 * dx) / dy);
    } else {
        gradient = (float) ((1.0 * dy) / dx);
    }
    if (steep) {
        if (y0 < y1) {
            for (uint16_t i = y0; i < y1; ++i) {
                ltdc_draw_point_a(i, (int16_t) ipart(x0 + gradient * (i - y0)),
                                  colorBlend(color, backcolor, rfpart(x0 + gradient * (i - y0))));
                ltdc_draw_point_a(i, (int16_t) (ipart(x0 + gradient * (i - y0)) + 1), colorBlend(color, backcolor,
                                                                                                 fpart(x0 +
                                                                                                       gradient *
                                                                                                       (i -
                                                                                                        y0))));
            }
        } else {
            for (uint16_t i = y1; i < y0; ++i) {
                ltdc_draw_point_a(i, (int16_t) ipart(x1 + gradient * (i - y1)),
                                  colorBlend(color, backcolor, rfpart(x0 + gradient * (i - y1))));
                ltdc_draw_point_a(i, (int16_t) (ipart(x1 + gradient * (i - y1)) + 1), colorBlend(color, backcolor,
                                                                                                 fpart(x1 +
                                                                                                       gradient *
                                                                                                       (i -
                                                                                                        y1))));
            }
        }

    } else {
        if (x0 < x1) {
            for (uint16_t i = x0; i < x1; ++i) {

                ltdc_draw_point(i, (uint16_t) ipart(y0 + gradient * (i - x0)),
                                colorBlend(color, backcolor, rfpart(y0 + gradient * (i - x0))));

                ltdc_draw_point(i, (uint16_t) (ipart(y0 + gradient * (i - x0)) + 1),
                                colorBlend(color, backcolor, fpart(y0 + gradient * (i - x0))));

            }
        } else {
            for (uint16_t i = x1; i < x0; ++i) {
                ltdc_draw_point(i, (uint16_t) ipart(y1 + gradient * (i - x1)),
                                colorBlend(color, backcolor, rfpart(y1 + gradient * (i - x1))));

                ltdc_draw_point(i, (uint16_t) (ipart(y1 + gradient * (i - x1)) + 1),
                                colorBlend(color, backcolor, fpart(y1 + gradient * (i - x1))));

            }
        }
    }
}





//void DrawArch( int r ){
//    int y=0;
//    int x=r;
//    float d=0;
//    ltdc_draw_point(x,y,A);
//    while( x>y ){
//        y++;
//        if( DC(r,y) < d ) x--;
//        putpixel(x,   y, A*(1-DC(R,y) );
//        putpixel(x-1, y, A*   DC(R,y) );
//        d = DC(r,y);
//    }
//}
//
////Distance to ceil:
//double DC(int r, int y){
//    double x = sqrt(r*r-y*y);
//    return ceil(x) - x;
//}

void ltdc_aa_arc(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t degFrom, uint16_t degTo, uint32_t color,
                 uint32_t backcolor) {

    float x;
    float y;
    float f;
    float rf;
    float f1;
    float rf1;

    uint16_t xp1 = (uint16_t) floor(0.707 * r1);
    float g1 = (float) ((90 * 3.1416) / 180);
    float g2 = (float) ((89 * 3.1416) / 180);
    float gap = (cosf(g2) * r1 - cosf(g1) * r1);
    uint8_t am = (uint8_t) ceil(gap);
    for (uint16_t i = degFrom; i < degTo; ++i) {

        for (uint16_t j = 0; j < am; ++j) {

            float fi = (float) (i + 1.0 * j / am);
            float d = (float) ((fi * 3.1416) / 180);
            x = (cosf(d) * r1);
            y = (sinf(d) * r1);
            f = fpart(y0 - y);
            rf = rfpart(y0 - y);
            f1 = fpart(x + x0);
            rf1 = rfpart(x + x0);
            if ((x >= (-1 * xp1)) && (x <= xp1)) {
                if (y > 0) {
                    ltdc_draw_point((uint16_t) (x0 + x), (uint16_t) (ipart(y0 - y)), colorBlend(color, backcolor, f));
                    ltdc_draw_point((uint16_t) (x0 + x), (uint16_t) (ipart(y0 - y) - 1),
                                    colorBlend(color, backcolor, rf));
                } else {
                    ltdc_draw_point((uint16_t) (x0 + x), (uint16_t) (ipart(y0 - y)), colorBlend(color, backcolor, rf));
                    ltdc_draw_point((uint16_t) (x0 + x), (uint16_t) ((ipart(y0 - y) + 1)),
                                    colorBlend(color, backcolor, f));
                }
            } else {
                if (x > 0) {
                    ltdc_draw_point_a((uint16_t) (y0 - y), (uint16_t) (ipart(x0 + x)),
                                      colorBlend(color, backcolor, rf1));
                    ltdc_draw_point_a((uint16_t) (y0 - y), (uint16_t) (ipart(x0 + x) + 1),
                                      colorBlend(color, backcolor, f1));
                } else {
                    ltdc_draw_point_a((uint16_t) (y0 - y), (uint16_t) (ipart(x + x0)),
                                      colorBlend(color, backcolor, f1));
                    ltdc_draw_point_a((uint16_t) (y0 - y), (uint16_t) (ipart(x + x0) - 1),
                                      colorBlend(color, backcolor, rf1));
                }

            }
        }
    }
}

void ltdc_aa_farc(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t degFrom, uint16_t degTo, uint32_t color,
                  uint32_t backcolor) {

    ltdc_aa_arc(x0, y0, r1, degFrom, degTo, color, backcolor);

    uint16_t xstart = (uint16_t) (x0 + cosf((float) (degFrom * 3.1416 / 180)) * r1);
    uint16_t ystart = (uint16_t) (y0 - sinf((float) (degFrom * 3.1416 / 180)) * r1);

    uint16_t xend = (uint16_t) (x0 + cosf((float) (degTo * 3.1416 / 180)) * r1);
    uint16_t yend = (uint16_t) (y0 - sinf((float) (degTo * 3.1416 / 180)) * r1);

    ltdc_aa_line(x0, y0, xstart, ystart, color, backcolor);
    ltdc_aa_line(x0, y0, xend, yend, color, backcolor);
    float deg;
    for (int16_t i = (int16_t) (-1 * r1); i <= r1; ++i) {
        for (int16_t j = (int16_t) 0; j <= r1; ++j) {
//            ltdc_draw_point(i + x0, j + y0, R888T565(color));
            if (((i * i + j * j) <= (r1 + 1) * (r1 + 1))) {
                deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);

                if (i < 0) {
                    deg = 180 - deg;
                }
                if ((deg) > degFrom && deg < degTo) {
                    ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                }
            }
        }
    }

    for (int16_t i = (int16_t) (-1 * r1); i <= r1; ++i) {
        for (int16_t j = (int16_t) (-1 * r1); j <= 0; ++j) {
//            delay_ms(30);
            if (i < 0 && j > -0.3 * r1) {
                if ((i * i + j * j) <= (r1 + 1) * (r1 + 1)) {
                    deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);

                    if (i < 0) {
                        deg = 180 - deg;
                    }
                    if (deg < 0) {
                        deg += 360;
                    }
                    if ((deg) > degFrom && deg < degTo) {
                        ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                    }
                }
            } else if ((i * i + j * j) <= (r1) * (r1)) {
                deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);

                if (i < 0) {
                    deg = 180 - deg;
                }
                if (deg < 0) {
                    deg += 360;
                }
                if ((deg) > degFrom && deg < degTo) {
                    ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                }
            }
        }
    }
}

void ltdc_aa_ring(uint16_t x0, uint16_t y0, uint16_t r1, uint16_t r2, uint16_t degFrom, uint16_t degTo, uint32_t color,
                  uint32_t backcolor) {
    ltdc_aa_arc(x0, y0, r1, degFrom, degTo, color, backcolor);
    ltdc_aa_arc(x0, y0, r2, degFrom, degTo, color, backcolor);


    uint16_t xstart = (uint16_t) (x0 + cosf((float) (degFrom * 3.1416 / 180)) * r1);
    uint16_t ystart = (uint16_t) (y0 - sinf((float) (degFrom * 3.1416 / 180)) * r1);

    uint16_t xend = (uint16_t) (x0 + cosf((float) (degTo * 3.1416 / 180)) * r1);
    uint16_t yend = (uint16_t) (y0 - sinf((float) (degTo * 3.1416 / 180)) * r1);


    float deg;
    for (int16_t i = (int16_t) (-1 * r1); i <= r1; ++i) {
        for (int16_t j = (int16_t) 0; j <= r1; ++j) {
//            ltdc_draw_point(i + x0, j + y0, R888T565(color));
            if (((i * i + j * j) <= (r1 + 1) * (r1 + 1)) && ((i * i + j * j) >= (r2 + 1) * (r2 + 1))) {
                deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);

                if (i < 0) {
                    deg = 180 - deg;
                }
                if ((deg) > degFrom && deg < degTo) {
                    ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                }
            }
        }
    }

    for (int16_t i = (int16_t) (-1 * r1); i <= r1; ++i) {
        for (int16_t j = (int16_t) (-1 * r1); j <= 0; ++j) {
//            delay_ms(30);
            if (i < 0 && j > -0.3 * r1) {
                if (((i * i + j * j) <= (r1 + 1) * (r1 + 1)) && ((i * i + j * j) >= (r2 + 1) * (r2 + 1))) {
                    deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);
                    if (i < 0) {
                        deg = 180 - deg;
                    }
                    if (deg < 0) {
                        deg += 360;
                    }
                    if ((deg) > degFrom && deg < degTo) {
                        ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                    }
                }
            } else if (((i * i + j * j) <= (r1) * (r1)) && ((i * i + j * j) >= (r2) * (r2))) {
                deg = (float) ((asinf((float) ((j * 1.0) / sqrt(j * j + i * i))) * 180) / 3.1416);

                if (i < 0) {
                    deg = 180 - deg;
                }
                if (deg < 0) {
                    deg += 360;
                }
                if ((deg) > degFrom && deg < degTo) {
                    ltdc_draw_point(i + x0, y0 - j, R888T565(color));
                }
            }
        }
    }
}


uint16_t max(uint16_t x0, uint16_t x1) {
    if (x0 > x1)
        return x0;
    else
        return x1;
}

uint16_t min(uint16_t x0, uint16_t x1) {
    if (x0 < x1)
        return x0;
    else
        return x1;
}

