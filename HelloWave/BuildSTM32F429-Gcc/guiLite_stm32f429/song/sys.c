//
// Created by song on 17-2-6.
//
#include "sys.h"

static uint8_t fac_us = 0;
static uint32_t fac_ms = 0;

void delay_init(uint8_t sysclk) {
    SysTick->CTRL &= ~(1 << 2);     //设置第二位为0,即时钟为HCLK/8

    fac_us = (uint8_t) (sysclk / 8);             //fac_us指的是1us的systick数目
    fac_ms = ((uint32_t) sysclk * 1000) / 8;
}

void delay_ms(uint16_t nms) {
    if (nms == 0)
        return;
    uint32_t temp;
    SysTick->LOAD = fac_ms * nms;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x01;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));  //要熟练理解:(temp&(1<<16))指的是提取出第16位,!(temp&(1<<16))指值为1时退出
    SysTick->CTRL = 0x0;
    SysTick->VAL = 0;
}

void delay_us(uint32_t nus) {
    if (nus == 0)
        return;
    uint32_t temp;
    SysTick->VAL = 0;
    SysTick->LOAD = fac_us * nus;
    SysTick->CTRL = 0x01;
    do {
        temp = SysTick->CTRL;
    } while (temp & (0x01) && !(temp & (1 << 16)));
    SysTick->CTRL = 0x0;
    SysTick->VAL = 0x0;
}

void clock_init(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq) {
    RCC->CR |= 0x00000001;
    RCC->CFGR = 0x0;
    RCC->CR &= 0xFEF6FFFF;
    RCC->PLLCFGR = 0x24003010;
    RCC->CR &= ~(1 << 18);
    RCC->CIR = 0x0;
    clock_set(pllm, plln, pllp, pllq);
    set_vector_table(0, 0x0);
}

uint8_t clock_set(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq) {
    uint16_t retry = 0;
    uint8_t status = 0;
    RCC->CR |= 1 << 16;
    while ((!(RCC->CR & (1 << 17))) && (retry < 0x1fff))retry++;
    if (retry == 0x1fff)
        status = 1;
    else {
        RCC->APB1ENR |= (1 << 28);
        PWR->CR = 3 << 14;
        RCC->CFGR |= (0 << 4) | (5 << 10) | (4 << 13);   //设置分频
        RCC->CR &= ~(1 << 24);
        RCC->PLLCFGR = pllm | (plln << 6) | (((pllp >> 1) - 1) << 16) | (pllq << 24) | (1 << 22);//配置主PLL,PLL时钟源来自HSE
        RCC->CR |= 1 << 24;            //打开主PLL
        while ((RCC->CR & (1 << 25)) == 0);//等待PLL准备好
        FLASH->ACR |= 1 << 8;        //指令预取使能.
        FLASH->ACR |= 1 << 9;        //指令cache使能.
        FLASH->ACR |= 1 << 10;        //数据cache使能.
        FLASH->ACR |= 5 << 0;        //5个CPU等待周期.
        RCC->CFGR &= ~(3 << 0);        //清零
        RCC->CFGR |= 2 << 0;        //选择主PLL作为系统时钟
        while ((RCC->CFGR & (3 << 2)) != (2 << 2));//等待主PLL作为系统时钟成功.
    }
    return status;

}

void set_vector_table(uint32_t vector, uint32_t offset) {
    SCB->VTOR = vector | (offset & (uint32_t) 0xFFFFFE00);
}

void nvic_priority_group(uint8_t nvic_group) {
    uint32_t temp, temp1;
    temp1 = (~nvic_group) & 0x07;//取后三位
    temp1 <<= 8;
    temp = SCB->AIRCR;  //读取先前的设置
    temp &= 0X0000F8FF; //清空先前分组
    temp |= 0X05FA0000; //写入钥匙
    temp |= temp1;
    SCB->AIRCR = temp;  //设置分组
}

void nvic_init(uint8_t nvic_pre, uint8_t nvic_sub, uint8_t nvic_channel, uint8_t nvic_group) {
    uint32_t temp;
    nvic_priority_group(nvic_group);
    temp = nvic_pre << (4 - nvic_group);
    temp |= nvic_sub & (0x0f >> nvic_group);
    temp &= 0xf;
    NVIC->ISER[nvic_channel / 32] = (uint32_t) (1 << (nvic_channel % 32));
    NVIC->IP[nvic_channel] |= temp << 4;
}

void exti_init(uint8_t gpiox, uint8_t bitx, uint8_t trim) {
    uint8_t offset = (uint8_t) ((bitx % 4) * 4);
    RCC->APB2ENR |= 1 << 14;
    SYSCFG->EXTICR[bitx / 4] &= ~(0x000F << offset);
    SYSCFG->EXTICR[bitx / 4] |= (gpiox << offset);   //配置中断,这里的配置有点特别，一般寄存器以配置PIN为多，这里是向寄存器中写入BASE组
    EXTI->IMR |= 1 << bitx;    //开启中断
    if (trim & 0x01)
        EXTI->FTSR |= 1 << bitx;
    if (trim & 0x02)
        EXTI->RTSR |= 1 << bitx;
}

void gpio_af_set(GPIO_TypeDef *gpiox, uint8_t bitx, uint8_t afx) {
    //这里的位操作主要是将四位二进制数的第四位和第三位进行分离。
    gpiox->AFR[bitx >> 3] &= ~(0x0f << ((bitx & 0x07) * 4));
    gpiox->AFR[bitx >> 3] |= afx << ((bitx & 0x07) * 4);
}

void gpio_set(GPIO_TypeDef* GPIOx,uint32_t BITx,uint32_t MODE,uint32_t OTYPE,uint32_t OSPEED,uint32_t PUPD)
{
    uint32_t pinpos=0,pos=0,curpin=0;
    //写成for循环是为了支持进行与操作配置例如:pin1|pin2
    for(pinpos=0;pinpos<16;pinpos++)
    {
        pos= (uint32_t) (1 << pinpos);	//一个个位检查
        curpin=BITx&pos;//检查引脚是否要设置
        if(curpin==pos)	//需要设置
        {
            GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
            GPIOx->MODER|=MODE<<(pinpos*2);	//设置新的模式
            if((MODE==0X01)||(MODE==0X02))	//如果是输出模式/复用功能模式
            {
                GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
                GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//设置新的速度值
                GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
                GPIOx->OTYPER|=OTYPE<<pinpos;		//设置新的输出模式
            }
            GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
            GPIOx->PUPDR|=PUPD<<(pinpos*2);	//设置新的上下拉
        }
    }
}






void assert_failed(const char *file, uint32_t line) {
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1) {}
}

void _assert(const char* file, int line){
    while (1) {}
}





























