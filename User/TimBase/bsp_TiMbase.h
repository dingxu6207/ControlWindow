#ifndef __BSP_TIMEBASE_H
#define __BSP_TIMEBASE_H

#include "stm32f10x.h"

#define            BASIC_TIM                   TIM1
#define            BASIC_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB2Periph_TIM1
#define            BASIC_TIM_Period            (10000-1)    
#define            BASIC_TIM_Prescaler         (7200-1)
#define            BASIC_TIM_IRQ               TIM1_UP_IRQn
#define            BASIC_TIM_IRQHandler        TIM1_UP_IRQHandler

// TIM1 ����Ƚ�ͨ��
#define ADVANCE_TIM_CH1_GPIO_CLK 		RCC_APB2Periph_GPIOA
#define ADVANCE_TIM_CH1_PORT 			GPIOA
#define ADVANCE_TIM_CH1_PIN 			GPIO_Pin_8


void BASIC_TIM_Init(void);
void ControlMotor(FunctionalState NewState);
void SetSpeedMoter(u16 SpeedMoter);
void SetSpeed(u16 uSetSpeed);

//M0�ź� 
#define M0_GPIO_PORT        GPIOA
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M0_GPIO_PIN         GPIO_Pin_5

//M1�ź� 
#define M1_GPIO_PORT        GPIOA
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M1_GPIO_PIN         GPIO_Pin_6

//M2�ź� 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_11


//SLF�ź� 
#define SLF_GPIO_PORT        GPIOA
#define SLF_GPIO_CLK         RCC_APB2Periph_GPIOA
#define SLF_GPIO_PIN         GPIO_Pin_13

//RST�ź� 
#define RST_GPIO_PORT        GPIOA
#define RST_GPIO_CLK         RCC_APB2Periph_GPIOA
#define RST_GPIO_PIN         GPIO_Pin_14

//DRV8825ʹ���ź�
#define EN_GPIO_PORT   	    GPIOA			              /* GPIO�˿� */
#define EN_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define EN_GPIO_PIN		    GPIO_Pin_4		        /* ���ӵ�SCLʱ���ߵ�GPIO */

// DRV8825 DIR�����ź�
#define DIR_GPIO_PORT    	GPIOA/* GPIO�˿� */
#define DIR_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define DIR_GPIO_PIN		GPIO_Pin_7  

#endif	/* __BSP_TIMEBASE_H */
