//
// Created by song on 17-4-8.
//


#include <stm32f429xx.h>
#include "ltdc.h"
#include "font.h"
#include "sdram.h"
#include "math.h"
#include "antialiasing.h"
#include "color.h"

//#include "doula.h"
//uint16_t buff1[76800] __attribute__((at(0XD0000000)));
//static const uint16_t buff1[76800];
//static uint16_t *buff1 = (uint16_t *) 0XD0000000;
//static const uint32_t buff2[38400];
//direction 为0表示纵向，为1表示横向
uint8_t *buff1 = (uint8_t *) 0xD0000000;
//uint16_t __attribute__((section (".sdramblock"))) buff1[76800];

uint8_t direction = 0;

uint8_t ltdc_clock_init(uint32_t n, uint32_t r, uint32_t div) {
    uint16_t retry = 0;
    uint32_t temprep = 0;
    RCC->CR &= ~(1 << 28);
    while ((RCC->CR & (1 << 29)) && (retry < 0x1fff))retry++;
    if (retry == 0X1FFF)return 1;
    else {
        temprep |= n << 6;
        temprep |= r << 28;
        RCC->PLLSAICFGR = temprep;        //设置LTDC的倍频和分频
        RCC->DCKCFGR &= ~(3 << 16);            //清除原来的设置.
        RCC->DCKCFGR |= div << 16;    //设置fdclk分频

        RCC->CR |= 1 << 28;                    //开启SAI时钟
        while (((RCC->CR & (1 << 29)) == 0) && (retry < 0X1FFF))retry++;//等待SAI时钟锁定
        if (retry == 0X1FFF) return 2;
    }
    return 0;
}

void ltdc_init() {
    while (ltdc_clock_init(192, 4, 2) != 0);
//    ltdc_clock_init(180, 4, 8);
    ltdc_gpio_init();
    //  nvic_init(3, 3, LTDC_IRQn, 2);
    ili9341_init();
    global_init();
    ltdc_layer_init();
//    dma2d_init();
//    ltdc_clear();

}

void ltdc_gpio_init() {
    RCC->APB2ENR |= 1 << 26;
    RCC->AHB1ENR |= 1 << 0;
    RCC->AHB1ENR |= 1 << 1;
    RCC->AHB1ENR |= 1 << 2;
    RCC->AHB1ENR |= 1 << 3;
    RCC->AHB1ENR |= 1 << 5;
    RCC->AHB1ENR |= 1 << 6;

    gpio_set(GPIOA, PIN3 | PIN4 | PIN6 | PIN11 | PIN12, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOB, PIN8 | PIN9 | PIN10 | PIN11, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOC, PIN6 | PIN7 | PIN10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOD, PIN3 | PIN6, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOF, PIN10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOG, PIN6 | PIN7 | PIN11, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOB, PIN0 | PIN1, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOG, PIN10 | PIN12, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);

    gpio_af_set(GPIOA, 3, 14);
    gpio_af_set(GPIOA, 4, 14);
    gpio_af_set(GPIOA, 6, 14);
    gpio_af_set(GPIOA, 11, 14);
    gpio_af_set(GPIOA, 12, 14);

    gpio_af_set(GPIOB, 8, 14);
    gpio_af_set(GPIOB, 9, 14);
    gpio_af_set(GPIOB, 10, 14);
    gpio_af_set(GPIOB, 11, 14);

    gpio_af_set(GPIOC, 6, 14);
    gpio_af_set(GPIOC, 7, 14);
    gpio_af_set(GPIOC, 10, 14);

    gpio_af_set(GPIOD, 3, 14);
    gpio_af_set(GPIOD, 6, 14);

    gpio_af_set(GPIOF, 10, 14);

    gpio_af_set(GPIOG, 6, 14);
    gpio_af_set(GPIOG, 7, 14);
    gpio_af_set(GPIOG, 11, 14);

    gpio_af_set(GPIOG, 10, 9);
    gpio_af_set(GPIOG, 12, 9);

    gpio_af_set(GPIOB, 0, 9);
    gpio_af_set(GPIOB, 1, 9);

}

void ili9341_init() {
    RCC->AHB1ENR |= 1 << 2;
    RCC->AHB1ENR |= 1 << 3;
    gpio_set(GPIOD, PIN13 | PIN12, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    gpio_set(GPIOC, PIN2, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    PCout(2) = 0;
    PCout(2) = 1;
    spi_init();

    /* Configure LCD */
    ili9341_WriteReg(0xCA);
    ili9341_WriteData(0xC3);
    ili9341_WriteData(0x08);
    ili9341_WriteData(0x50);
    ili9341_WriteReg(LCD_POWERB);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0xC1);
    ili9341_WriteData(0x30);
    ili9341_WriteReg(LCD_POWER_SEQ);
    ili9341_WriteData(0x64);
    ili9341_WriteData(0x03);
    ili9341_WriteData(0x12);
    ili9341_WriteData(0x81);
    ili9341_WriteReg(LCD_DTCA);
    ili9341_WriteData(0x85);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x78);
    ili9341_WriteReg(LCD_POWERA);
    ili9341_WriteData(0x39);
    ili9341_WriteData(0x2C);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x34);
    ili9341_WriteData(0x02);
    ili9341_WriteReg(LCD_PRC);
    ili9341_WriteData(0x20);
    ili9341_WriteReg(LCD_DTCB);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x00);
    ili9341_WriteReg(LCD_FRMCTR1);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x1B);
    ili9341_WriteReg(LCD_DFC);
    ili9341_WriteData(0x0A);
    ili9341_WriteData(0xA2);
    ili9341_WriteReg(LCD_POWER1);
    ili9341_WriteData(0x10);
    ili9341_WriteReg(LCD_POWER2);
    ili9341_WriteData(0x10);
    ili9341_WriteReg(LCD_VCOM1);
    ili9341_WriteData(0x45);
    ili9341_WriteData(0x15);
    ili9341_WriteReg(LCD_VCOM2);
    ili9341_WriteData(0x90);
    ili9341_WriteReg(LCD_MAC);
    ili9341_WriteData(0xC8);
//    ili9341_WriteData(0x08);
    ili9341_WriteReg(LCD_3GAMMA_EN);
    ili9341_WriteData(0x00);
    ili9341_WriteReg(LCD_RGB_INTERFACE);
    ili9341_WriteData(0xC2);
    ili9341_WriteReg(LCD_DFC);
    ili9341_WriteData(0x0A);
    ili9341_WriteData(0xA7);
    ili9341_WriteData(0x27);
    ili9341_WriteData(0x04);

    /* Colomn address set */
    ili9341_WriteReg(LCD_COLUMN_ADDR);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0xEF);
    /* Page address set */
    ili9341_WriteReg(LCD_PAGE_ADDR);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x01);
    ili9341_WriteData(0x3F);
    ili9341_WriteReg(LCD_INTERFACE);
    ili9341_WriteData(0x01);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x06);

    ili9341_WriteReg(LCD_GRAM);
    delay_ms(500);

    ili9341_WriteReg(LCD_GAMMA);
    ili9341_WriteData(0x01);

    ili9341_WriteReg(LCD_PGAMMA);
    ili9341_WriteData(0x0F);
    ili9341_WriteData(0x29);
    ili9341_WriteData(0x24);
    ili9341_WriteData(0x0C);
    ili9341_WriteData(0x0E);
    ili9341_WriteData(0x09);
    ili9341_WriteData(0x4E);
    ili9341_WriteData(0x78);
    ili9341_WriteData(0x3C);
    ili9341_WriteData(0x09);
    ili9341_WriteData(0x13);
    ili9341_WriteData(0x05);
    ili9341_WriteData(0x17);
    ili9341_WriteData(0x11);
    ili9341_WriteData(0x00);
    ili9341_WriteReg(LCD_NGAMMA);
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x16);
    ili9341_WriteData(0x1B);
    ili9341_WriteData(0x04);
    ili9341_WriteData(0x11);
    ili9341_WriteData(0x07);
    ili9341_WriteData(0x31);
    ili9341_WriteData(0x33);
    ili9341_WriteData(0x42);
    ili9341_WriteData(0x05);
    ili9341_WriteData(0x0C);
    ili9341_WriteData(0x0A);
    ili9341_WriteData(0x28);
    ili9341_WriteData(0x2F);
    ili9341_WriteData(0x0F);

    ili9341_WriteReg(LCD_SLEEP_OUT);
    delay_ms(500);
    ili9341_WriteReg(LCD_DISPLAY_ON);
    /* GRAM start writing */
    ili9341_WriteReg(LCD_GRAM);
}

void spi_init() {
    uint16_t reg = 0;
    RCC->AHB1ENR |= 1 << 5;
    RCC->APB2ENR |= 1 << 20;
    gpio_set(GPIOF, PIN7 | PIN8 | PIN9, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PD);
    gpio_af_set(GPIOF, 7, 5);
    gpio_af_set(GPIOF, 8, 5);
    gpio_af_set(GPIOF, 9, 5);
    RCC->APB2RSTR |= 1 << 20;
    RCC->APB2RSTR &= ~(1 << 20);
    reg |= 3 << 3;
    //从第一位开始采集
    reg &= ~(1 << 0);
    //默认极性是低电位
    reg &= ~(1 << 1);
    reg |= 1 << 2;
    reg &= ~(1 << 7);
    reg |= 1 << 8;
    reg |= 1 << 9;
    reg &= ~(1 << 10);
    //8位数据长度
    reg &= ~(1 << 11);
    //禁止crc校验
    reg &= ~(1 << 13);

    SPI5->CR1 = reg; //设置 CR1
    SPI5->CR1 |= 1 << 6;
    //设置模式,0->spi模式 1->I2S模式
    SPI5->I2SCFGR &= ~(1 << 11);
}


uint8_t spi_write(uint8_t value) {
    while ((SPI5->SR & 1 << 1) == 0); //等待发送区空
    SPI5->DR = value;
    while ((SPI5->SR & 1 << 0) == 0);
    return (uint8_t) SPI5->DR;
}


void lcd_write_rge(uint8_t reg) {
    PDout(13) = 0;
    PCout(2) = 0;
    spi_write(reg);
    PCout(2) = 1;
}

void lcd_write_data(uint8_t data) {
    PDout(13) = 1;
    PCout(2) = 0;
    spi_write(data);
    PCout(2) = 1;
}

void ili9341_WriteReg(uint8_t reg) {
    lcd_write_rge(reg);
};

void ili9341_WriteData(uint8_t data) {
    lcd_write_data(data);
};

void global_init() {
    uint32_t reg = 0u;
    reg |= 0 << 28;
    reg |= 0 << 29;
    reg |= 0 << 30;
    reg |= 0 << 31;
    LTDC->GCR = reg;

    reg = 1; //垂直脉宽
    reg |= 9 << 16;//水平脉宽
    LTDC->SSCR = reg;

    reg = 3;
    reg |= 29 << 16;
    LTDC->BPCR = reg;

    reg = 323;
    reg |= 269 << 16;
    LTDC->AWCR = reg;

    reg = 327;
    reg |= 279 << 16;
    LTDC->TWCR = reg;

    LTDC->BCCR = 0X00000000;
    LTDC->GCR |= 1 << 0;

//    uint32_t tmp= 0u;
//    tmp = 0 << 28;
//    tmp |= 0 << 29;
//    tmp |= 0 << 30;
//    tmp |= 0 << 31;
//    LTDC->GCR = tmp;
//
//    tmp = 1; //????
//    tmp |= 9 << 16;//????
//    LTDC->SSCR = ((9<<16)|1);
//
//    tmp = 3;
//    tmp |= 29 << 16;
//    LTDC->BPCR = ((29<<16)|3);
//
//    tmp = 323;
//    tmp |= 269 << 16;
//    LTDC->AWCR = ((269<<16)|323);
//
//    tmp = 327;
//    tmp |= 279 << 16;
//    LTDC->TWCR = ((279<<16)|327);
//
//    LTDC->BCCR = 0X00000000;

}

//通常只会用到一层，所以这里就只打开了第一层。
/*需要设置：
 * 像素格式
 * 缓存地址
 * 固定alpha
 * 层的默认颜色
 * 设置窗口
 * 设置行数
 * */
void ltdc_layer_init() {
    uint32_t reg;
    //缓存地址
    LTDC_Layer1->CFBAR = ((uint32_t) buff1);
    //颜色格式
    LTDC_Layer1->PFCR = ((uint32_t) 0x00000002U);
    //恒定alpha值
    LTDC_Layer1->CACR = 255;
    //层的默认颜色
    LTDC_Layer1->DCCR = ((uint32_t) 0x00000000U);
    //选择是采用固定的alpha的值还是固定的alpha与原alpha共同作用的值
    LTDC_Layer1->BFCR = ((uint32_t) 6 << 8) | 7;

    reg = (0 + 240 + ((LTDC->BPCR & 0X0FFF0000) >> 16)) << 16;
    LTDC_Layer1->WHPCR = (0 + ((LTDC->BPCR & 0X0FFF0000) >> 16) + 1) | reg;//设置行起始和结束位置
    reg = (0 + 320 + (LTDC->BPCR & 0X7FF)) << 16;
    LTDC_Layer1->WVPCR = (0 + (LTDC->BPCR & 0X7FF) + 1) | reg;        //设置列起始和结束位置
    LTDC_Layer1->CFBLR = (240 * 2 << 16) | (240 * 2 + 3);        //帧缓冲区长度设置(字节为单位)
    LTDC_Layer1->CFBLNR = 320;


//    LTDC_Layer2->CFBAR = ((uint32_t) buff2);
//    //颜色格式
//    LTDC_Layer2->PFCR = ((uint32_t) 0x00000000U);
//    //恒定alpha值
//    LTDC_L的值ayer2->CACR = 255;
//    LTDC_Layer2->DCCR = ((uint32_t) 0x00000000U);
//    LTDC_Layer2->BFCR = ((uint32_t) 6 << 8) | 7;
//
//    reg = (0 + 240 + ((LTDC->BPCR & 0X0FFF0000) >> 16)) << 16;
//    LTDC_Layer2->WHPCR = (0 + ((LTDC->BPCR & 0X0FFF0000) >> 16) + 1) | reg;//设置行起始和结束位置
//    reg = (160 + 160 + (LTDC->BPCR & 0X7FF)) << 16;
//    LTDC_Layer2->WVPCR = (160 + (LTDC->BPCR & 0X7FF) + 1) | reg;
//    LTDC_Layer2->CFBLR = (240 * 4 << 16) | (240 * 4 + 3);        //帧缓冲区长度设置(字节为单位)
//    LTDC_Layer2->CFBLNR = 160;

    LTDC_Layer1->CR |= 1 << 0;
//    LTDC_Layer2->CR |= 1 << 0;
    LTDC->SRCR |= 1 << 0;

}



//大致的设置为：
/* 1.设置工作模式
 * 2.设置前景，在r2m的模式下不需要
 *      设置输入像素的格式
 *      设置输入像素的缓冲地址
 *      设置前景偏移
 *      设置NLR
 * 3.设置背景，只在blend模式下才需要
 *      同上
 * 4.设置输出层
 *      同上
 * 在寄存器模式下还需要设置颜色寄存器
 *
 * */
void ltdc_clear(uint16_t color) {
    RCC->AHB1ENR |= 1 << 23;
    DMA2D->CR &= ~(1 << 0);
    DMA2D->CR |= 3 << 16;
//    DMA2D->FGMAR = (uint32_t) ST_LOGO_1;
    //前景的偏移地址
    DMA2D->FGOR = 0;
//输出的颜色格式
    DMA2D->OPFCCR = 0x02;
    //PFC时使用,输入的颜色格式
    DMA2D->FGPFCCR |= 0x02;
//    DMA2D->OPFCCR = 0;
    //设置偏移
    DMA2D->OOR = 0;
    //设置缓冲地址
    DMA2D->OMAR = (uint32_t) buff1;
    //设置行和列
    DMA2D->NLR = 320 | 240 << 16;
    //设置寄存器模式下的颜色
    DMA2D->OCOLR = color;
    //使能
    DMA2D->CR |= 1 << 0;
    while ((DMA2D->ISR & (1 << 1)) == 0);
    DMA2D->IFCR |= 1 << 1;
    LTDC->SRCR |= 1 << 0;
}

void ltdc_fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    RCC->AHB1ENR |= 1 << 23;
    DMA2D->CR &= ~(1 << 0);
    DMA2D->CR |= 3 << 16;
    DMA2D->OPFCCR = 0x02;
    if (0 == direction) {
        DMA2D->OMAR = (uint32_t) ((uint32_t) buff1 + 2 * (240 * y + x));
        DMA2D->OOR = (uint32_t) (240 - w);
    } else {
        DMA2D->OMAR = (uint32_t) ((uint32_t) buff1 + 2 * (320 * y + x));
        DMA2D->OOR = (uint32_t) (320 - w);
    }
    DMA2D->NLR = h | w << 16;
    DMA2D->OCOLR = color;
    DMA2D->CR |= 1 << 0;
    while ((DMA2D->ISR & (1 << 1)) == 0);
    DMA2D->IFCR |= 1 << 1;
    LTDC->SRCR |= 1 << 0;
}


void ltdc_draw_picture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const void *p) {
    RCC->AHB1ENR |= 1 << 23;
    DMA2D->CR &= ~(1 << 0);
    DMA2D->CR &= ~(3 << 16);
    DMA2D->FGMAR = (uint32_t) p;
    DMA2D->FGOR = (uint32_t) 0;

    DMA2D->OPFCCR = 0x02;
    //PFC时使用,输入的颜色格式
    DMA2D->FGPFCCR |= 0x02;

    DMA2D->OMAR = (uint32_t) ((uint32_t) buff1 + 2 * (240 * y + x));
    DMA2D->OOR = (uint32_t) (240 - w);

    DMA2D->NLR = h | w << 16;
    DMA2D->CR |= 1 << 0;
    while ((DMA2D->ISR & (1 << 1)) == 0);
    DMA2D->IFCR |= 1 << 1;
    LTDC->SRCR |= 1 << 0;


}

void ltdc_draw_point(uint16_t x, uint16_t y, uint16_t color) {
    if (0 == direction) {
        *(uint16_t *) ((uint32_t) buff1 + 2 * (240 * y + x)) = color;
    } else {
        *(uint16_t *) ((uint32_t) buff1 + 2 * (320 * y + x)) = color;
    }
}

uint16_t ltdc_read_point(int x, int y) {
    return *(uint16_t *) ((uint32_t) buff1 + 2 * (240 * y + x));
}

void ltdc_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    float slope = ((float) (y1 - y0) / (x1 - x0));
    uint16_t y;
    if (x0 == x1) {
        if (y1 >= y0) {
            for (uint16_t i = y0; i <= y1; ++i) {
                ltdc_draw_point(x0, i, color);
            }
        } else {
            for (uint16_t i = y1; i <= y0; ++i) {
                ltdc_draw_point(x0, i, color);
            }
        }
    } else {
        for (uint16_t i = x0; i <= x1; ++i) {
            y = (uint16_t) (y0 + (i - x0) * slope);
            ltdc_draw_point(i, y, color);
        }
    }

}

void ltdc_draw_line_a(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    float slope = ((float) (y1 - y0) / (x1 - x0));
    uint16_t y;
    if (x0 == x1) {
        if (y1 >= y0) {
            for (uint16_t i = y0; i <= y1; ++i) {
                ltdc_draw_point_a(x0, i, color);
            }
        } else {
            for (uint16_t i = y1; i <= y0; ++i) {
                ltdc_draw_point_a(x0, i, color);
            }
        }
    } else {
        for (uint16_t i = x0; i <= x1; ++i) {
            y = (uint16_t) (y0 + (i - x0) * slope);
            ltdc_draw_point_a(i, y, color);
        }
    }

}


void ltdc_draw_font(uint16_t x, uint16_t y, uint8_t chars, uint8_t size, uint16_t forColor, uint16_t backColor) {
    uint8_t num = (uint8_t) (chars - ' ');
    sFONT font;
    uint8_t bsize = 0;
    switch (size) {
        case 8:
            font = Font8;
            bsize = 1;
            break;
        case 12:
            font = Font12;
            bsize = 1;
            break;
        case 16:
            font = Font16;
            bsize = 2;
            break;
        case 20:
            font = Font20;
            bsize = 2;
            break;
        case 24:
            font = Font24;
            bsize = 3;
            break;
        default:
            font = Font16;
            bsize = 2;
            break;
    }

    for (uint8_t i = 0; i < font.Height; ++i) {
        for (uint8_t j = 0; j < bsize; ++j) {
            uint8_t tmp = font.table[num * (font.Height) * bsize + i * bsize + j];
            for (uint8_t k = 0; k < 8; ++k) {
                if (tmp & 0x80) {
                    ltdc_draw_point((uint16_t) (x + j * 8 + k), y + i, forColor);
                } else {
                    ltdc_draw_point((uint16_t) (x + j * 8 + k), y + i, backColor);
                }
                tmp <<= 1;
            }
        }
    }

//    for (uint8_t i = 0; i < font.Height; ++i) {
//        uint8_t tmp = font.table[num * 12 + i];
//        for (uint8_t j = 0; j < 8; ++j) {
//            if (tmp & 0x80) {
//                ltdc_draw_point(x + j, y + i, WHITE);
//            } else {
//                ltdc_draw_point(x + j, y + i, BLACK);
//            }
//            tmp <<= 1;
//        }
//    }
}


void ltdc_draw_string(uint16_t x, uint16_t y, uint8_t *s, uint8_t size, uint16_t forColor, uint16_t backColor) {
    uint8_t len = strlen(s);
    uint16_t x1 = x;
    uint16_t y1 = y;

    sFONT font;
    uint8_t bsize = 0;
    switch (size) {
        case 8:
            font = Font8;
            bsize = 1;
            break;
        case 12:
            font = Font12;
            bsize = 1;
            break;
        case 16:
            font = Font16;
            bsize = 2;
            break;
        case 20:
            font = Font20;
            bsize = 2;
            break;
        case 24:
            font = Font24;
            bsize = 3;
            break;
        default:
            font = Font16;
            bsize = 2;
            break;
    }

    for (uint16_t i = 0; i < len; ++i) {
        x1 = (uint16_t) (x1 + font.Width);
//        x1 = (uint16_t) (x1 + bsize*8);
        if (x1 > 239 - 7) {
            x1 = 0;
            y1 = (uint16_t) (y1 + font.Height);
        }
        ltdc_draw_font(x1, y1, *(s + i), size, forColor, backColor);
    }
}


void ltdc_draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color) {
    for (uint16_t i = 1; i < radius + 1; ++i) {
        double y1 = sqrt(radius * radius - i * i);
        ltdc_draw_point(x + i, y - (uint16_t) y1, color);
        ltdc_draw_point(x + i, y + (uint16_t) y1, color);
        ltdc_draw_point(x - i, y - (uint16_t) y1, color);
        ltdc_draw_point(x - i, y + (uint16_t) y1, color);

    }
}

void ltdc_draw_point_a(uint16_t x, uint16_t y, uint16_t color) {

    *(uint16_t *) ((uint32_t) buff1 + 2 * (240 * x + y)) = color;
}


void ltdc_aa_circle(uint16_t x0, uint16_t y0, uint16_t r, uint32_t color, uint32_t backcolor) {


    uint16_t xp1 = (uint16_t) floor(0.707 * r); //floor
    uint16_t xp2 = (uint16_t) (xp1 + 1);     //ceil
    float y = 0.0;
    float f;
    float rf;
    for (uint16_t i = 0; i <= xp1; ++i) {
        y = (float) sqrt(r * r - i * i);
        f = fpart(y);
        rf = rfpart(y);

        ltdc_draw_point(i + x0, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(i + x0, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point(x0 - i, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(x0 - i, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point(i + x0, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(i + x0, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point(x0 - i, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(x0 - i, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point_a(i + y0, (uint16_t) (x0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(i + y0, (uint16_t) (x0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point_a(i + y0, (uint16_t) (x0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(i + y0, (uint16_t) (x0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
    }

//    for (uint16_t i = 0; i <= xp1; ++i) {
//        y = (float) sqrt(r * r - i * i);
//        f = fpart(y);
//        rf = rfpart(y);
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
//
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
//
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
//
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
//
//    }

}

void ltdc_aa_fcircle(uint16_t x0, uint16_t y0, uint16_t r1, uint32_t color, uint32_t backcolor) {

    if (x0 > y0) {
        if (r1 >= y0) {
            r1 = (uint16_t) (y0 - 1);
        }
    } else {
        if (r1 >= x0) {
            r1 = (uint16_t) (x0 - 1);
        }
    }
    uint16_t xp1 = (uint16_t) floor(0.707 * r1); //floor
//    uint16_t xp2 = (uint16_t) floor(0.707 * r2);     //ceil
    float y = 0.0;
    float f;
    float rf;
    for (uint16_t i = 0; i <= xp1; ++i) {
        y = (float) sqrt(r1 * r1 - i * i);
        f = fpart(y);
        rf = rfpart(y);

        ltdc_draw_point(i + x0, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(i + x0, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_line(i + x0, y0, i + x0, (uint16_t) (y0 + ipart(y)), R888T565(color));

        ltdc_draw_point(x0 - i, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(x0 - i, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_line(x0 - i, y0, x0 - i, (uint16_t) (y0 + ipart(y)), R888T565(color));

        ltdc_draw_point(i + x0, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(i + x0, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_line(i + x0, y0, i + x0, (uint16_t) (y0 - ipart(y)), R888T565(color));

        ltdc_draw_point(x0 - i, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point(x0 - i, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));

        ltdc_draw_line(x0 - i, y0, x0 - i, (uint16_t) (y0 - ipart(y)), R888T565(color));


        ltdc_draw_point_a(i + y0, (uint16_t) (x0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(i + y0, (uint16_t) (x0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
        ltdc_draw_line_a(i + y0, x0 + xp1, i + y0, (uint16_t) (x0 + ipart(y)), R888T565(color));

        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 + ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
        ltdc_draw_line_a(y0 - i, x0 + xp1, y0 - i, (uint16_t) (x0 + ipart(y)), R888T565(color));

        ltdc_draw_point_a(i + y0, (uint16_t) (x0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(i + y0, (uint16_t) (x0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
        ltdc_draw_line_a(i + y0, x0 - xp1, i + y0, (uint16_t) (x0 - ipart(y)), R888T565(color));

        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 - ipart(y)), colorBlend(color, backcolor, rf));
        ltdc_draw_point_a(y0 - i, (uint16_t) (x0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
        ltdc_draw_line_a(y0 - i, x0 - xp1, y0 - i, (uint16_t) (x0 - ipart(y)), R888T565(color));

    }

//
//    for (uint16_t i = (uint16_t) (xp1 + 1); i <= r1; ++i) {
//        y = (float) sqrt(r1 * r1 - i * i);
//        ltdc_draw_line(i + x0, y0, i + x0, (uint16_t) (y0 + ipart(y)), R888T565(color));
//        ltdc_draw_line(x0 - i, y0, x0 - i, (uint16_t) (y0 + ipart(y)), R888T565(color));
//        ltdc_draw_line(i + x0, y0, i + x0, (uint16_t) (y0 - ipart(y)), R888T565(color));
//        ltdc_draw_line(x0 - i, y0, x0 - i, (uint16_t) (y0 - ipart(y)), R888T565(color));
//
//    }

//    for (uint16_t i = 0; i <= xp1; ++i) {
//        y = (float) sqrt(r1 * r1 - i * i);
//        f = fpart(y);
//        rf = rfpart(y);
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
//        ltdc_draw_line_a(i + x0, y0 + xp1, i + x0, (uint16_t) (y0 + ipart(y)), R888T565(color));
//
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 + ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 + (ipart(y) + 1)), colorBlend(color, backcolor, f));
//        ltdc_draw_line_a(x0 - i, y0 + xp1, x0 - i, (uint16_t) (y0 + ipart(y)), R888T565(color));
//
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(i + x0, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
//        ltdc_draw_line_a(i + x0, y0 - xp1, i + x0, (uint16_t) (y0 - ipart(y)), R888T565(color));
//
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 - ipart(y)), colorBlend(color, backcolor, rf));
//        ltdc_draw_point_a(x0 - i, (uint16_t) (y0 - (ipart(y) + 1)), colorBlend(color, backcolor, f));
//        ltdc_draw_line_a(x0 - i, y0 - xp1, x0 - i, (uint16_t) (y0 - ipart(y)), R888T565(color));
//
//    }


}