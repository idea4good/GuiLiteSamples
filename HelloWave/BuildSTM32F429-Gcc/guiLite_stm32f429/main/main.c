#include "main.h"
#include "../song/usart.h"
#include "../song/ltdc.h"
#include "../song/stm32f429i_discovery_ioe.h"
#include "../song/sdram.h"
#include "../song/stm32f429i_discovery_ioe.h"
#include "../song/memalloc.h"
#include "../song/antialiasing.h"
#include "../song/color.h"
#include "../song/sys.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


#define GL_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))

struct EXTERNAL_GFX_OP {
    void (*draw_pixel)(int x, int y, unsigned int rgb);

    void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} my_gfx_op;

extern void startHelloMCU(int width, int height, int color_bytes, struct EXTERNAL_GFX_OP *gfx_op);

void gfx_draw_pixel(int x, int y, int rgb) {
    //LCD_Fast_DrawPoint(x, y, GL_RGB_32_to_16(rgb));
    ltdc_draw_point_a(y, x, GL_RGB_32_to_16(rgb));
}

void gfx_fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb) {
    ltdc_fill(x0, y0, (x1 - x0), (y1 - y0), GL_RGB_32_to_16(rgb));
}

int main() {
    init();

    ltdc_init();
    IOE_Config();
    sdram_init();
    pool_init();
    ltdc_clear(WHITE);

    LED_GREEN = 1;
    LED_RED = 0;

    my_gfx_op.draw_pixel = gfx_draw_pixel;
    my_gfx_op.fill_rect = 0;
    startHelloMCU(240, 320, 16, &my_gfx_op);


    while (1) {
        printf("song\n");
        LED_GREEN = 1;
        LED_RED = 0;
        delay_ms(500);
        LED_GREEN = 0;
        LED_RED = 1;
        delay_ms(500);
    }
    return 0;
}

void init(void) {
    //初始化内核
    clock_init(8, 360, 2, 4);
    delay_init(180);
    //初始化板载LED
    exti_init(GPIO_A, 0, RTIR);
    nvic_init(2, 2, EXTI0_IRQn, 2);
    nvic_init(3, 3, SysTick_IRQn, 2);
    usart_init(9600);
    RCC->AHB1ENR |= 1 << 6;
    RCC->AHB1ENR |= 1 << 0;
    gpio_set(GPIOG, PIN13 | PIN14, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOA, PIN0, GPIO_MODE_IN, 0, 0, GPIO_PUPD_PD);


}


PUTCHAR_PROTOTYPE {
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    // HAL_UART_Transmit(&handleTypeDef, (uint8_t *)&ch, 1, 0xFFFF);
    sputc((uint8_t) ch);
    return ch;
}


