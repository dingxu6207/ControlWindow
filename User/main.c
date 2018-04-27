/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "ESP8266.h"
#include "WifiUsart.h"
#include "bsp_TiMbase.h" 

#include <stdbool.h>
#include <stdlib.h>
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
extern bool bFlagRun;
extern bool bRunMotor;
u16 uSetSpeed;
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
  SysTick_Init(); 

  BASIC_TIM_Init();
	
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
							SetNameCode();
							SetWifiConnect();	
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
						ControlMotor(ENABLE);
						GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
						
					}
					
					else if(WIFIUART_RxBuffer[2] == '-')
					{
					  ControlMotor(ENABLE);
						/* DIR=0 */
	          GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
					}

					else if (WIFIUART_RxBuffer[2] == 'Q')
					{
						ControlMotor(DISABLE);
					}

         	else if (WIFIUART_RxBuffer[2] == 'V')
					{
						
						uSetSpeed = atoi((char const *)WIFIUART_RxBuffer+3);
						SetSpeed(uSetSpeed);
						
					}
					//WifiUsart_SendString(USART3, ":FV13#\n");
						
				}
			
		 	Wifiuart_FlushRxBuffer();
			bRunMotor =false;
			
        }		
	}	
}
/*********************************************END OF FILE**********************/
