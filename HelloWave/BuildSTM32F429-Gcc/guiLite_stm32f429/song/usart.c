//
// Created by song on 17-2-11.
//

#include <stm32f429xx.h>
#include "usart.h"
void usart_init(uint32_t bound){
    float temp;
    uint16_t z;
    uint16_t f;
    RCC->AHB1ENR|=1<<0;
    RCC->APB2ENR|=1<<4;
    temp = (float)(90*1000000)/(bound*16);
    z = (uint16_t) temp;
    f = (uint16_t) ((temp - z) * 16);
    z<<=4;
    z+=f;
    gpio_set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
    gpio_af_set(GPIOA,9,7);
    gpio_af_set(GPIOA,10,7);
    USART1->BRR = z;
    USART1->CR1&=~(1<<15);
    USART1->CR2&=~(3<<12);
    USART1->CR1&=~(1<<10);
    USART1->CR1|=1<<3;
    USART1->CR1|=1<<2;  	//串口接收使能
    USART1->CR1|=1<<5;    	//接收缓冲区非空中断使能
    nvic_init(2,3,USART1_IRQn,2);//组2，最低优先级
    USART1->CR1|=1<<13;
}

void sputc(uint8_t ch){
    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
    USART1->DR = (uint8_t) ch;
}

void send(uint8_t* s){
    for (int i = 0; i < 5 ; ++i) {
        sputc(s[i]);
    }
}


