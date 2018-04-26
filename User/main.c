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
#include <stdbool.h>

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
extern bool bFlagRun;
extern bool bRunMotor;
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
  SysTick_Init();

  ESP8266IO();

  WifiUSART_Config();

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

							sprintf((char*)WIFIUART_RxBuffer, "%s", ":F+725#");
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

					printf("it is ok!\n");

					WifiUsart_SendString(USART3, ":FV13#\n");
						
				}

			 Wifiuart_FlushRxBuffer();
			 bRunMotor =false;

        }

		
	}	
}
/*********************************************END OF FILE**********************/
