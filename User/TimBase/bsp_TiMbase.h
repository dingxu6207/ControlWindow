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

// TIM1 输出比较通道
#define ADVANCE_TIM_CH1_GPIO_CLK 		RCC_APB2Periph_GPIOA
#define ADVANCE_TIM_CH1_PORT 			GPIOA
#define ADVANCE_TIM_CH1_PIN 			GPIO_Pin_8


void BASIC_TIM_Init(void);
void ControlMotor(FunctionalState NewState);
void SetSpeedMoter(u16 SpeedMoter);
void SetSpeed(u16 uSetSpeed);

//M0信号 
#define M0_GPIO_PORT        GPIOA
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M0_GPIO_PIN         GPIO_Pin_12

//M1信号 
#define M1_GPIO_PORT        GPIOA
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M1_GPIO_PIN         GPIO_Pin_13

//M2信号 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_14

//DRV8825使能信号
#define EN_GPIO_PORT   	    GPIOA			              /* GPIO端口 */
#define EN_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define EN_GPIO_PIN		    GPIO_Pin_11		        /* 连接到SCL时钟线的GPIO */

// DRV8825 DIR方向信号
#define DIR_GPIO_PORT    	GPIOA/* GPIO端口 */
#define DIR_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define DIR_GPIO_PIN		GPIO_Pin_15 

// LED0
#define LED0_GPIO_PORT    	GPIOA/* GPIO端口 */
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED0_GPIO_PIN		GPIO_Pin_1 

#endif	/* __BSP_TIMEBASE_H */

