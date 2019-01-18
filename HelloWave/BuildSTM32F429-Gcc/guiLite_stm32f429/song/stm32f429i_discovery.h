/**
  ******************************************************************************
  * @file    stm32f429i_discovery.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    28-October-2013
  * @brief   This file contains definitions for STM32F429I-DISCO Kit Leds, push-
  *          buttons hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_H
#define __STM32F429I_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
/* Includes ------------------------------------------------------------------*/
 #include "stm32f4xx.h"
   
/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32F4_DISCOVERY
  * @{
  */
   
/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
   
/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL
  * @{
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
  LED3 = 0,
  LED4 = 1
} Led_TypeDef;

typedef enum 
{  
  BUTTON_USER = 0,
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;     
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** 
  * @brief  Define for STM32F429I_DISCO board  
  */ 
#if !defined (USE_STM32F429I_DISCO)
 #define USE_STM32F429I_DISCO
#endif


/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             2
  
#define LED3_PIN                         GPIO_Pin_13
#define LED3_GPIO_PORT                   GPIOG
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOG  

#define LED4_PIN                         GPIO_Pin_14
#define LED4_GPIO_PORT                   GPIOG
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOG  
/**
  * @}
  */ 
  
/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                          1  

/**
 * @brief Wakeup push-button
 */
#define USER_BUTTON_PIN                GPIO_Pin_0
#define USER_BUTTON_GPIO_PORT          GPIOA
#define USER_BUTTON_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define USER_BUTTON_EXTI_LINE          EXTI_Line0
#define USER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define USER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define USER_BUTTON_EXTI_IRQn          EXTI0_IRQn 
/**
  * @}
  */

/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_I2C_EE
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */  
#define sEE_I2C                          I2C3
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C3
#define sEE_I2C_SCL_PIN                  GPIO_Pin_8                  /* PA.08 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOA                       /* GPIOA */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource8
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C3
#define sEE_I2C_SDA_PIN                  GPIO_Pin_9                  /* PC.09 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOC                       /* GPIOC */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOC
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource9
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C3
#define sEE_M24C64_32

#define sEE_I2C_DMA                      DMA1   
#define sEE_I2C_DMA_CHANNEL              DMA_Channel_3
#define sEE_I2C_DMA_STREAM_TX            DMA1_Stream4
#define sEE_I2C_DMA_STREAM_RX            DMA1_Stream2   
#define sEE_I2C_DMA_CLK                  RCC_AHB1Periph_DMA1
#define sEE_I2C_DR_Address               ((uint32_t)0x40005C10)
#define sEE_USE_DMA
   
#define sEE_I2C_DMA_TX_IRQn              DMA1_Stream4_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Stream2_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Stream4_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Stream2_IRQHandler   
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0   
   
#define sEE_TX_DMA_FLAG_FEIF             DMA_FLAG_FEIF4
#define sEE_TX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF4
#define sEE_TX_DMA_FLAG_TEIF             DMA_FLAG_TEIF4
#define sEE_TX_DMA_FLAG_HTIF             DMA_FLAG_HTIF4
#define sEE_TX_DMA_FLAG_TCIF             DMA_FLAG_TCIF4
#define sEE_RX_DMA_FLAG_FEIF             DMA_FLAG_FEIF2
#define sEE_RX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF2
#define sEE_RX_DMA_FLAG_TEIF             DMA_FLAG_TEIF2
#define sEE_RX_DMA_FLAG_HTIF             DMA_FLAG_HTIF2
#define sEE_RX_DMA_FLAG_TCIF             DMA_FLAG_TCIF2
   
#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1  

/* I2C clock speed configuration (in Hz), used by I2C EEPROM memory and IO Expander drivers */
#ifndef I2C_SPEED
 #define I2C_SPEED                        100000
#endif /* I2C_SPEED */

/**
  * @}
  */  

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Macros
  * @{
  */  
/**
  * @}
  */ 


/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Functions
  * @{
  */
void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void);
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
