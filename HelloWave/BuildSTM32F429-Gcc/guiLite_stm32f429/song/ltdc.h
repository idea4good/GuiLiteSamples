//
// Created by song on 17-4-8.
//

#ifndef APP_LTDC_H
#define APP_LTDC_H

#include "sys.h"
#include "usart.h"
#include "fonts.h"

#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_MAC                 0x36   /* Memory Access Control register*/

/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */

//画笔颜色
#define WHITE             0xFFFF
#define BLACK             0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE             0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN             0x07E0
#define CYAN             0x7FFF
#define YELLOW             0xFFE0
#define BROWN             0XBC40 //棕色
#define BRRED             0XFC07 //棕红色
#define GRAY             0X8430 //灰色
//GUI颜色

#define DARKBLUE         0X01CF    //深蓝色
#define LIGHTBLUE         0X7D7C    //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN         0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY             0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


void ltdc_init();

uint8_t ltdc_clock_init(uint32_t n, uint32_t r, uint32_t div);


//清屏
void ltdc_clear(uint16_t color);

//填充
void ltdc_fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void ltdc_draw_point(uint16_t x, uint16_t y, uint16_t color);

void ltdc_draw_point_a(uint16_t x, uint16_t y, uint16_t color);

uint16_t ltdc_read_point(int x, int y);

void ltdc_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void ltdc_draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);

void ltdc_change_direction();

void ltdc_draw_font(uint16_t x, uint16_t y, uint8_t chars, uint8_t size, uint16_t forColor, uint16_t backColor);

void ltdc_draw_string(uint16_t x, uint16_t y, uint8_t *s, uint8_t size, uint16_t forColor, uint16_t backColor);

void ltdc_draw_picture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const void *p);

void ltdc_layer_init();

void ltdc_gpio_init();

void ili9341_init();

void spi_init();

uint8_t spi_write(uint8_t value);

void lcd_write_rge(uint8_t reg);

void lcd_write_data(uint8_t data);

void ili9341_WriteReg(uint8_t reg);

void ili9341_WriteData(uint8_t data);

void global_init();

void ltdc_draw_line_a(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void ltdc_aa_circle(uint16_t x0, uint16_t y0, uint16_t r, uint32_t color, uint32_t backcolor);

void ltdc_aa_fcircle(uint16_t x0, uint16_t y0, uint16_t r1, uint32_t color, uint32_t backcolor);

#endif //APP_LTDC_H
