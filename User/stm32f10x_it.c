/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include <stdbool.h>
#include "WifiUsart.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h"
#include "bsp_usart_blt.h"

extern void TimingDelay_Decrement(void);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	 TimingDelay_Decrement();
}

// 串口中断服务函数
bool bFlagRun = false;
void DEBUG_USART_IRQHandler(void)
{
  	uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);

		if(CmdUART_RxPtr < (CmdUART_RX_BUFFER_SIZE - 1))
        {
                CmdUART_RxBuffer[CmdUART_RxPtr] = ucTemp;
                CmdUART_RxBuffer[CmdUART_RxPtr + 1]=0x00;
                CmdUART_RxPtr++;
        }
		else
        {
                CmdUART_RxBuffer[CmdUART_RxPtr  - 1] = ucTemp;
                
        }

		//如果为回车键，则开始处理串口数据
        if (ucTemp == 35)
        {
            bFlagRun = true;
        }
	}	 
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

// 串口中断服务函数
bool bRunMotor = false;
void DEBUG_USART3_IRQHandler(void) 
{
  	
	unsigned char data;
  	
	if(USART_GetITStatus(DEBUG_USART3x,USART_IT_RXNE)!=RESET)
	{		
    
			data = USART_ReceiveData(DEBUG_USART3x);
		
    	if(WIFIUART_RxPtr < (WIFIUART_RX_BUFFER_SIZE - 1))
        {
                WIFIUART_RxBuffer[WIFIUART_RxPtr] = data;
                WIFIUART_RxBuffer[WIFIUART_RxPtr + 1]=0x00;
                WIFIUART_RxPtr++;
        }
			else
        {
                WIFIUART_RxBuffer[WIFIUART_RxPtr - 1] = data;
                
        }

		if (data == 35)
		{
			bRunMotor = true;
		}
	}	 
}

//-------------------------------------------------------
//串口2收发
bool bUART2flag = false;
void BLT_USART_IRQHandler( void )
{
	unsigned char data;
	if(USART_GetITStatus(BLT_USARTx, USART_IT_RXNE)!= RESET)
	{
		data = USART_ReceiveData(BLT_USARTx);		
		if (BLTUART_RxPtr < (BLTUART_RX_BUFFER_SIZE - 1))
		{
			BLTUART_RxBuffer[BLTUART_RxPtr] = data;
            BLTUART_RxBuffer[BLTUART_RxPtr + 1]=0x00;
            BLTUART_RxPtr++;
		}
		else
		{
			BLTUART_RxBuffer[BLTUART_RxPtr - 1] = data;
		}
	}

	if (data == 35)
	{
		bUART2flag = true;
	}
}

extern bool AcFlag;
extern bool DeFlag;
u32 uCountStep = 10;
extern u32 uStepCount;
void  BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET )
	{
    	#if 1
		if((AcFlag == true))
        {
              uCountStep++; 
        }
    	else if((DeFlag == true))
        {
              uCountStep--;
        }
   		if (uCountStep < 10)
        {
			AcFlag = false;
			DeFlag = false;
			uCountStep = 10;
			ControlMotor(DISABLE);
			ControlCover(DISABLE);
							
        }
		else if ((uCountStep > (10 + (200*uStepCount))))
		{
			AcFlag = false;
		    DeFlag = false;
		    uCountStep = (10 + (200*uStepCount));
		    ControlMotor(DISABLE);
			  ControlCover(DISABLE);
		}
       
    #endif
					 
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update); 
	}

}
u16 uCountStep1 = 10;
void COVER_TIM_IRQHandler(void)
{
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET ) 
	{
		uCountStep1++;
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
