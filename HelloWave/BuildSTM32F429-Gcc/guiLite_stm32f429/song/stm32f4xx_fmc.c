

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_fmc.h"
#include "sys.h"


#define SDCR_WriteProtection_RESET ((uint32_t)0x00007DFF) 



void FMC_SDRAMDeInit(uint32_t FMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_FMC_SDRAM_BANK(FMC_Bank));
  
  FMC_Bank5_6->SDCR[FMC_Bank] = 0x000002D0;
  FMC_Bank5_6->SDTR[FMC_Bank] = 0x0FFFFFFF;    
  FMC_Bank5_6->SDCMR = 0x00000000;
  FMC_Bank5_6->SDRTR = 0x00000000;
  FMC_Bank5_6->SDSR = 0x00000000; 
}  

/**
  * @brief  Initializes the FMC SDRAM Banks according to the specified
  *         parameters in the FMC_SDRAMInitStruct.
  * @param  FMC_SDRAMInitStruct : pointer to a FMC_SDRAMInitTypeDef structure
  *         that contains the configuration information for the FMC SDRAM 
  *         specified Banks.                       
  * @retval None
  */
void FMC_SDRAMInit(FMC_SDRAMInitTypeDef* FMC_SDRAMInitStruct)
{ 
  /* temporary registers */
  uint32_t tmpr1 = 0;
  uint32_t tmpr2 = 0;
  uint32_t tmpr3 = 0;
  uint32_t tmpr4 = 0;
  
  /* Check the parameters */
  
  /* Control parameters */
  assert_param(IS_FMC_SDRAM_BANK(FMC_SDRAMInitStruct->FMC_Bank));
  assert_param(IS_FMC_COLUMNBITS_NUMBER(FMC_SDRAMInitStruct->FMC_ColumnBitsNumber)); 
  assert_param(IS_FMC_ROWBITS_NUMBER(FMC_SDRAMInitStruct->FMC_RowBitsNumber));
  assert_param(IS_FMC_SDMEMORY_WIDTH(FMC_SDRAMInitStruct->FMC_SDMemoryDataWidth));
  assert_param(IS_FMC_INTERNALBANK_NUMBER(FMC_SDRAMInitStruct->FMC_InternalBankNumber)); 
  assert_param(IS_FMC_CAS_LATENCY(FMC_SDRAMInitStruct->FMC_CASLatency));
  assert_param(IS_FMC_WRITE_PROTECTION(FMC_SDRAMInitStruct->FMC_WriteProtection));
  assert_param(IS_FMC_SDCLOCK_PERIOD(FMC_SDRAMInitStruct->FMC_SDClockPeriod));
  assert_param(IS_FMC_READ_BURST(FMC_SDRAMInitStruct->FMC_ReadBurst));
  assert_param(IS_FMC_READPIPE_DELAY(FMC_SDRAMInitStruct->FMC_ReadPipeDelay));   
  
  /* Timing parameters */
  assert_param(IS_FMC_LOADTOACTIVE_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay)); 
  assert_param(IS_FMC_EXITSELFREFRESH_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay));
  assert_param(IS_FMC_SELFREFRESH_TIME(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime));
  assert_param(IS_FMC_ROWCYCLE_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay));
  assert_param(IS_FMC_WRITE_RECOVERY_TIME(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime)); 
  assert_param(IS_FMC_RP_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay)); 
  assert_param(IS_FMC_RCD_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RCDDelay));    
  
  /* SDRAM bank control register configuration */ 
  tmpr1 =   (uint32_t)FMC_SDRAMInitStruct->FMC_ColumnBitsNumber |
             FMC_SDRAMInitStruct->FMC_RowBitsNumber |
             FMC_SDRAMInitStruct->FMC_SDMemoryDataWidth |
             FMC_SDRAMInitStruct->FMC_InternalBankNumber |           
             FMC_SDRAMInitStruct->FMC_CASLatency |
             FMC_SDRAMInitStruct->FMC_WriteProtection |
             FMC_SDRAMInitStruct->FMC_SDClockPeriod |
             FMC_SDRAMInitStruct->FMC_ReadBurst | 
             FMC_SDRAMInitStruct->FMC_ReadPipeDelay;
            
  if(FMC_SDRAMInitStruct->FMC_Bank == FMC_Bank1_SDRAM )
  {
    FMC_Bank5_6->SDCR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr1;
  }
  else   /* SDCR2 "don't care" bits configuration */
  {
    tmpr3 = (uint32_t)FMC_SDRAMInitStruct->FMC_SDClockPeriod |
             FMC_SDRAMInitStruct->FMC_ReadBurst | 
             FMC_SDRAMInitStruct->FMC_ReadPipeDelay;
    
    FMC_Bank5_6->SDCR[FMC_Bank1_SDRAM] = tmpr3;
    FMC_Bank5_6->SDCR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr1;
  }
  /* SDRAM bank timing register configuration */
  if(FMC_SDRAMInitStruct->FMC_Bank == FMC_Bank1_SDRAM )
  {
    tmpr2 =   (uint32_t)((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay)-1) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay)-1) << 4) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime)-1) << 8) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay)-1) << 12) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime)-1) << 16) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay)-1) << 20) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RCDDelay)-1) << 24);
            
            FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr2;
  }
  else   /* SDTR "don't care bits configuration */
  {
    tmpr2 =   (uint32_t)((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay)-1) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay)-1) << 4) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime)-1) << 8) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime)-1) << 16);
            
    tmpr4 =   (uint32_t)(((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay)-1) << 12) |
            (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay)-1) << 20);
            
            FMC_Bank5_6->SDTR[FMC_Bank1_SDRAM] = tmpr4;
            FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr2;
  }
  
}



/**
  * @brief  Configures the SDRAM memory command issued when the device is accessed.   
  * @param  FMC_SDRAMCommandStruct: pointer to a FMC_SDRAMCommandTypeDef structure 
  *         which will be configured.
  * @retval None
  */
void FMC_SDRAMCmdConfig(FMC_SDRAMCommandTypeDef* FMC_SDRAMCommandStruct)
{
  uint32_t tmpr = 0x0;
    
  /* check parameters */
  assert_param(IS_FMC_COMMAND_MODE(FMC_SDRAMCommandStruct->FMC_CommandMode));
  assert_param(IS_FMC_COMMAND_TARGET(FMC_SDRAMCommandStruct->FMC_CommandTarget));
  assert_param(IS_FMC_AUTOREFRESH_NUMBER(FMC_SDRAMCommandStruct->FMC_AutoRefreshNumber));
  assert_param(IS_FMC_MODE_REGISTER(FMC_SDRAMCommandStruct->FMC_ModeRegisterDefinition));
  
  tmpr =   (uint32_t)(FMC_SDRAMCommandStruct->FMC_CommandMode |
                      FMC_SDRAMCommandStruct->FMC_CommandTarget |
                     (((FMC_SDRAMCommandStruct->FMC_AutoRefreshNumber)-1)<<5) |
                     ((FMC_SDRAMCommandStruct->FMC_ModeRegisterDefinition)<<9));
  
  FMC_Bank5_6->SDCMR = tmpr;

}


/**
  * @brief  Returns the indicated FMC SDRAM bank mode status.
  * @param  SDRAM_Bank: Defines the FMC SDRAM bank. This parameter can be 
  *                     FMC_Bank1_SDRAM or FMC_Bank2_SDRAM. 
  * @retval The FMC SDRAM bank mode status         
  */


/**
  * @brief  defines the SDRAM Memory Refresh rate.
  * @param  FMC_Count: specifies the Refresh timer count.       
  * @retval None
  */
void FMC_SetRefreshCount(uint32_t FMC_Count)
{
  /* check the parameters */
  assert_param(IS_FMC_REFRESH_COUNT(FMC_Count));
  
  FMC_Bank5_6->SDRTR |= (FMC_Count<<1);
   
}

/**
  * @brief  Sets the Number of consecutive SDRAM Memory auto Refresh commands.
  * @param  FMC_Number: specifies the auto Refresh number.       
  * @retval None
  */
void FMC_SetAutoRefresh_Number(uint32_t FMC_Number)
{
  /* check the parameters */
  assert_param(IS_FMC_AUTOREFRESH_NUMBER(FMC_Number));
  
  FMC_Bank5_6->SDCMR |= (FMC_Number << 5);   
}

/**
  * @brief  Enables or disables write protection to the specified FMC SDRAM Bank.
  * @param  SDRAM_Bank: Defines the FMC SDRAM bank. This parameter can be 
  *                     FMC_Bank1_SDRAM or FMC_Bank2_SDRAM.   
  * @param  NewState: new state of the write protection flag.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FMC_SDRAMWriteProtectionConfig(uint32_t SDRAM_Bank, FunctionalState NewState)
{
  /* Check the parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_FMC_SDRAM_BANK(SDRAM_Bank));
  
  if (NewState != DISABLE)
  {
    FMC_Bank5_6->SDCR[SDRAM_Bank] |= FMC_Write_Protection_Enable;    
  }
  else
  {
    FMC_Bank5_6->SDCR[SDRAM_Bank] &= SDCR_WriteProtection_RESET;
  } 
  
}




FlagStatus FMC_GetFlagStatus(uint32_t FMC_Bank, uint32_t FMC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpsr = 0x00000000;
  
  /* Check the parameters */
  assert_param(IS_FMC_GETFLAG_BANK(FMC_Bank));
  assert_param(IS_FMC_GET_FLAG(FMC_FLAG));
  


  if(FMC_Bank == FMC_Bank4_PCCARD)
  {
    tmpsr = FMC_Bank4->SR4;
  }
  else 
  {
    tmpsr = FMC_Bank5_6->SDSR;
  }
  
  /* Get the flag status */
  if ((tmpsr & FMC_FLAG) != FMC_FLAG )
  {
    bitstatus = RESET;
  }
  else
  {
    bitstatus = SET;
  }
  /* Return the flag status */
  return bitstatus;
}



