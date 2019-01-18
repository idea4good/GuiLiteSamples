//
// Created by song on 17-4-12.
//

#include "sdram.h"
#include "stm32f4xx_fmc.h"
#include "stm32f429i_discovery_sdram.h"

void sdram_init() {
    sdram_gpio_init();
    sdram_reg_init();
    FMC_Bank5_6->SDCR[1] &= ((uint32_t) 0x00007DFF);
}

void sdram_gpio_init() {

    RCC->AHB1ENR |= 1 << 1;
    RCC->AHB1ENR |= 1 << 2;
    RCC->AHB1ENR |= 1 << 3;
    RCC->AHB1ENR |= 1 << 4;
    RCC->AHB1ENR |= 1 << 5;
    RCC->AHB1ENR |= 1 << 6;
    RCC->AHB3ENR |= 1 << 0;

    gpio_set(GPIOB, PIN5 | PIN6, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    gpio_set(GPIOC, PIN0, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    gpio_set(GPIOD, PIN0 | PIN1 | PIN8 | PIN9 | PIN10 | PIN14 | PIN15, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M,
             GPIO_PUPD_NONE);
    gpio_set(GPIOE, PIN0 | PIN1 | PIN7 | PIN8 | PIN9 | PIN10 | PIN11 | PIN12 | PIN13 | PIN14 | PIN15, GPIO_MODE_AF,
             GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    gpio_set(GPIOF, PIN0 | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN11 | PIN12 | PIN13 | PIN14 | PIN15, GPIO_MODE_AF,
             GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_NONE);
    gpio_set(GPIOG, PIN0 | PIN1 | PIN4 | PIN5 | PIN8 | PIN15, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M,
             GPIO_PUPD_NONE);

    gpio_af_set(GPIOB, 5, 12);
    gpio_af_set(GPIOB, 6, 12);

    gpio_af_set(GPIOC, 0, 12);

    gpio_af_set(GPIOD, 0, 12);
    gpio_af_set(GPIOD, 1, 12);
    gpio_af_set(GPIOD, 8, 12);
    gpio_af_set(GPIOD, 9, 12);
    gpio_af_set(GPIOD, 10, 12);
    gpio_af_set(GPIOD, 14, 12);
    gpio_af_set(GPIOD, 15, 12);

    gpio_af_set(GPIOE, 0, 12);
    gpio_af_set(GPIOE, 1, 12);
    gpio_af_set(GPIOE, 7, 12);
    gpio_af_set(GPIOE, 8, 12);
    gpio_af_set(GPIOE, 9, 12);
    gpio_af_set(GPIOE, 10, 12);
    gpio_af_set(GPIOE, 11, 12);
    gpio_af_set(GPIOE, 12, 12);
    gpio_af_set(GPIOE, 13, 12);
    gpio_af_set(GPIOE, 14, 12);
    gpio_af_set(GPIOE, 15, 12);

    gpio_af_set(GPIOF, 0, 12);
    gpio_af_set(GPIOF, 1, 12);
    gpio_af_set(GPIOF, 2, 12);
    gpio_af_set(GPIOF, 3, 12);
    gpio_af_set(GPIOF, 4, 12);
    gpio_af_set(GPIOF, 5, 12);
    gpio_af_set(GPIOF, 11, 12);
    gpio_af_set(GPIOF, 12, 12);
    gpio_af_set(GPIOF, 13, 12);
    gpio_af_set(GPIOF, 14, 12);
    gpio_af_set(GPIOF, 15, 12);

    gpio_af_set(GPIOG, 0, 12);
    gpio_af_set(GPIOG, 1, 12);
    gpio_af_set(GPIOG, 4, 12);
    gpio_af_set(GPIOG, 5, 12);
    gpio_af_set(GPIOG, 8, 12);
    gpio_af_set(GPIOG, 15, 12);
}

void sdram_reg_init() {

    FMC_SDRAMInitTypeDef  FMC_SDRAMInitStructure;
    FMC_SDRAMTimingInitTypeDef  FMC_SDRAMTimingInitStructure;

    FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay    = 2;
    /* TXSR: min=70ns (7x11.11ns) */
    FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;
    /* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
    FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime      = 4;
    /* TRC:  min=70 (7x11.11ns) */
    FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay        = 7;
    /* TWR:  min=1+ 7ns (1+1x11.11ns) */
    FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime    = 2;
    /* TRP:  20ns => 2x11.11ns */
    FMC_SDRAMTimingInitStructure.FMC_RPDelay              = 2;
    /* TRCD: 20ns => 2x11.11ns */
    FMC_SDRAMTimingInitStructure.FMC_RCDDelay             = 2;

/* FMC SDRAM control configuration */
    FMC_SDRAMInitStructure.FMC_Bank = FMC_Bank2_SDRAM;
    /* Row addressing: [7:0] */
    FMC_SDRAMInitStructure.FMC_ColumnBitsNumber = FMC_ColumnBits_Number_8b;
    /* Column addressing: [11:0] */
    FMC_SDRAMInitStructure.FMC_RowBitsNumber = FMC_RowBits_Number_12b;
    FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth = SDRAM_MEMORY_WIDTH;
    FMC_SDRAMInitStructure.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
    FMC_SDRAMInitStructure.FMC_CASLatency = SDRAM_CAS_LATENCY;
    FMC_SDRAMInitStructure.FMC_WriteProtection = FMC_Write_Protection_Disable;
    FMC_SDRAMInitStructure.FMC_SDClockPeriod = SDCLOCK_PERIOD;
    FMC_SDRAMInitStructure.FMC_ReadBurst = SDRAM_READBURST;
    FMC_SDRAMInitStructure.FMC_ReadPipeDelay = FMC_ReadPipe_Delay_1;
    FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct = &FMC_SDRAMTimingInitStructure;

    /* FMC SDRAM bank initialization */
    FMC_SDRAMInit(&FMC_SDRAMInitStructure);

    /* FMC SDRAM device initialization sequence */
    //SDRAM_InitSequence();

    volatile uint16_t val = 0;
    volatile uint32_t colreg = 0;
    volatile uint32_t timreg = 0;

//    uint32_t tmpr1 = 0;
//    uint32_t tmpr2 = 0;
//    uint32_t tmpr3 = 0;
//    uint32_t tmpr4 = 0;
//
//
//
//    colreg |= 0 << 0;
//    colreg |= 1 << 2;
//    colreg |= 1 << 4;
//    colreg |= 1 << 6;
//    colreg |= 3 << 7;
//    colreg |= 1 << 9;
//    colreg |= 2 << 10;
//    colreg |= 0 << 12; //突发模式
//    colreg |= 1 << 13;
//    FMC_Bank5_6->SDCR[1] = colreg;
//
//    timreg |= (2 - 1) << 0;
//    timreg |= (7 - 1) << 4;
//    timreg |= (4 - 1) << 8;
//    timreg |= (7 - 1) << 12;
//    timreg |= (2 - 1) << 16;
//    timreg |= (2 - 1) << 20;
//    timreg |= (2 - 1) << 24;
//    FMC_Bank5_6->SDTR[1] = timreg;

//    SDRAM_InitSequence();
    sdram_send_commend(1, 1, 0);
    delay_ms(200);
    sdram_send_commend(2, 1, 0);
    sdram_send_commend(3, 4, 0);
    val |= 1 << 0;
    val |= 0 << 3;
    val |= 3 << 4;
    val |= 0 << 7;
    val |= 1 << 9;
    sdram_send_commend(4, 1, val);
    FMC_Bank5_6->SDRTR = 1386 << 1;
}


void SDRAM_InitSequence(void) {
    FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;
    uint32_t tmpr = 0;

/* Step 3 --------------------------------------------------------------------*/
    /* Configure a clock configuration enable command */
    FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_CLK_Enabled;
    FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 1;
    FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
    /* Send the command */
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

/* Step 4 --------------------------------------------------------------------*/
    /* Insert 100 ms delay */
    delay_ms(100);

/* Step 5 --------------------------------------------------------------------*/
    /* Configure a PALL (precharge all) command */
    FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_PALL;
    FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 1;
    FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
    /* Send the command */
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

/* Step 6 --------------------------------------------------------------------*/
    /* Configure a Auto-Refresh command */
    FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_AutoRefresh;
    FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 4;
    FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
    /* Send the  first command */
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
    /* Send the second command */
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

/* Step 7 --------------------------------------------------------------------*/
    /* Program the external memory mode register */
    tmpr = (uint32_t) SDRAM_MODEREG_BURST_LENGTH_2 |
           SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
           SDRAM_MODEREG_CAS_LATENCY_3 |
           SDRAM_MODEREG_OPERATING_MODE_STANDARD |
           SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    /* Configure a load Mode register command*/
    FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_LoadMode;
    FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 1;
    FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = tmpr;
    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
    /* Send the command */
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

/* Step 8 --------------------------------------------------------------------*/

    /* Set the refresh rate counter */
    /* (15.62 us x Freq) - 20 */
    /* Set the device refresh counter */
    FMC_SetRefreshCount(1386);
    /* Wait until the SDRAM controller is ready */
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET) {
    }
}

void sdram_send_commend(uint8_t cmd, uint8_t refresh, uint16_t val) {
    uint32_t reg = 0;
    reg |= cmd << 0;
    reg |= 1 << 3;
    reg |= (refresh - 1) << 5;
    reg |= val << 9;
    FMC_Bank5_6->SDCMR = reg;
    while ((FMC_Bank5_6->SDSR & (1 << 5)));
}

