//
// Created by song on 17-4-12.
//

#ifndef APP_SDRAM_H
#define APP_SDRAM_H

#include "sys.h"

#define SDRAM_BANK_ADDR     ((uint32_t)0xD0000000)

#define IS42S16400J_SIZE             0x400000

#define SDRAM_BANK_END   ((uint32_t)0xD0400000)

void sdram_init();

void sdram_gpio_init();

void SDRAM_InitSequence(void);

/*这些位定义发送到 SDRAM 设备的命令。
000：正常模式
001：时钟配置使能
010： PALL（“预充电所有存储区域”）命令
011：自刷新命令
100：加载模式寄存器
101：自刷新命令
110：掉电命令
111：保留
 * */
void sdram_send_commend(uint8_t cmd, uint8_t refresh, uint16_t val);

void sdram_reg_init();

#endif //APP_SDRAM_H
