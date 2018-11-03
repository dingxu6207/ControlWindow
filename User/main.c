/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "ESP8266.h"
#include "WifiUsart.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h" 

#include <stdbool.h>
#include <stdlib.h>
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
extern bool bFlagRun;
extern bool bRunMotor;
u16 uSetSpeed;
u32 uStepCount = 1;
extern u16 uCountStep;
extern u16 uCountStep1;
bool AcFlag = false;
bool DeFlag = false;
char TempCount[100];
char TempCount1[100];
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
  SysTick_Init(); 

  BASIC_TIM_Init();

  Cover_TIM_Init();
	
  WifiUSART_Config();
	
  ESP8266IO();

  bFlagRun = true;
  sprintf((char*)CmdUART_RxBuffer, ":FY#");
		
  while(1)
	{	
		if (bFlagRun == true)
		{
			if (CmdUART_RxBuffer[0] == ':')
				  if (CmdUART_RxBuffer[1] == 'F')
				  	{
						if (CmdUART_RxBuffer[2] == 'W')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';							
							SetIP(CmdUART_RxBuffer);
						}
						else if (CmdUART_RxBuffer[2] == 'A')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';	
							SetWifiName(CmdUART_RxBuffer);
						}
						else if (CmdUART_RxBuffer[2] == 'C')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';	
							SetWifiCode(CmdUART_RxBuffer);
						}
							
						else if (CmdUART_RxBuffer[2] == 'Y')
						{
							SetSpeed(1000);
							SetSpeedCover(1000);
							SetNameCode();
							SetWifiConnect();	
						}
						else if (CmdUART_RxBuffer[2] == '+')
						{
							
							AcFlag = true;
					  		ControlMotor(ENABLE);
					  		ControlCover(ENABLE);
							GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
						    GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
							GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
					  		
						}
						
						else if(CmdUART_RxBuffer[2] == '-')
						{
							DeFlag = true;
							ControlMotor(ENABLE);
							ControlCover(ENABLE);
	            			GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
	            			GPIO_ResetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
							GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
						}

						else if (CmdUART_RxBuffer[2] == 'Q')
						{
							ControlMotor(DISABLE);
							ControlCover(DISABLE);
					  		GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);

						}

						else if (CmdUART_RxBuffer[2] == 'V')
						{
						
							uSetSpeed = atoi((char const *)CmdUART_RxBuffer+3);	
							printf("uSetSpeed = %d\n", uSetSpeed);
							SetSpeed(uSetSpeed);
							SetSpeedCover(uSetSpeed);
						
						}
						else if (CmdUART_RxBuffer[2] == 'S')
						{
							uStepCount = atoi((char const *)CmdUART_RxBuffer+3);
							printf("uStepCount = %u\n", uStepCount);
						}
				  	}	
				  	
			bFlagRun = false;
			CmdUsart_FlushRxBuffer();
		}

        if (bRunMotor == true)	
        {
        
			if (WIFIUART_RxBuffer[0] == ':')
				if (WIFIUART_RxBuffer[1] == 'F')
				{				
					if (WIFIUART_RxBuffer[2] == '+')
					{						
						AcFlag = true;
						ControlMotor(ENABLE);
						ControlCover(ENABLE);
						GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
						GPIO_ResetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
						
					}
					
					else if(WIFIUART_RxBuffer[2] == '-')
					{
					    DeFlag = true;
					  	ControlMotor(ENABLE);
					  	ControlCover(ENABLE);
	            		GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
	            		GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
					}

					else if (WIFIUART_RxBuffer[2] == 'Q')
					{
						ControlMotor(DISABLE);
						ControlCover(DISABLE);
					}

         			else if (WIFIUART_RxBuffer[2] == 'V')
					{
						
						uSetSpeed = atoi((char const *)WIFIUART_RxBuffer+3);
						SetSpeed(uSetSpeed);
						SetSpeedCover(uSetSpeed);
						
					}

					else if (WIFIUART_RxBuffer[2] == '?')
					{
						WifiUsart_SendString(USART3, ":FN2#");
					}

					else if (WIFIUART_RxBuffer[2] == 'D')
					{						
						sprintf(TempCount,"TempCount=%d\r\n",uCountStep);//uCountStep1
						sprintf(TempCount1,"TempCount1=%d\r\n",uCountStep1);
						WifiUsart_SendString(USART3, TempCount);
						WifiUsart_SendString(USART3, TempCount1);
					}

					else if (WIFIUART_RxBuffer[2] == 'O')
					{
						
						AcFlag = true;
						ControlMotor(ENABLE);
						ControlCover(ENABLE);
						GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
						GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
					}
					
					else if (WIFIUART_RxBuffer[2] == 'C')
					{
					  
					    DeFlag = true;
					  	ControlMotor(ENABLE);
					  	ControlCover(ENABLE);
						/* DIR=0 */
	          			GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
	          			GPIO_ResetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
					}
					
					else if (WIFIUART_RxBuffer[2] == 'V')
					{
							uSetSpeed = atoi((char const *)WIFIUART_RxBuffer+3);	
							SetSpeed(uSetSpeed);
							SetSpeedCover(uSetSpeed);
					}
					else if (WIFIUART_RxBuffer[2] == 'S')
					{
							uStepCount = atoi((char const *)WIFIUART_RxBuffer+3);	
					}				
						
				}
			
		 	Wifiuart_FlushRxBuffer();
			bRunMotor =false;
			
        }		
	}	
}
/*********************************************END OF FILE**********************/
