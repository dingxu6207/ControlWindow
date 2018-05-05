#ifndef __BSP_TIMECOVER_H
#define __BSP_TIMECOVER_H

#include "stm32f10x.h"

#define            COVER_TIM                   TIM2
#define            COVER_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            COVER_TIM_CLK               RCC_APB1Periph_TIM2
#define            COVER_TIM_Period            (10000-1)    
#define            COVER_TIM_Prescaler         (7200-1)
#define            COVER_TIM_IRQ               TIM2_IRQn
#define            COVER_TIM_IRQHandler        TIM2_IRQHandler

// TIM2 输出比较通道
#define COVER_TIM_CH2_GPIO_CLK 		RCC_APB2Periph_GPIOA
#define COVER_TIM_CH2_PORT 			GPIOA
#define COVER_TIM_CH2_PIN 			GPIO_Pin_0


void Cover_TIM_Init(void);
void ControlCover(FunctionalState NewState);
void SetSpeedCoverPulse(u16 uSpeedCoverOne);
void SetSpeedCoverMoter(u16 SpeedMoter);
void SetSpeedCover(u16 uSetSpeed);
//void Timer2_Configuration(void);



//M0信号 
#define DrM0_GPIO_PORT        GPIOB
#define DrM0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define DrM0_GPIO_PIN         GPIO_Pin_12

//M1信号 
#define DrM1_GPIO_PORT        GPIOB
#define DrM1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define DrM1_GPIO_PIN         GPIO_Pin_13

//M2信号 
#define DrM2_GPIO_PORT        GPIOB
#define DrM2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define DrM2_GPIO_PIN         GPIO_Pin_14

//DRV8825使能信号
#define DrEN_GPIO_PORT   	    GPIOC			              /* GPIO端口 */
#define DrEN_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define DrEN_GPIO_PIN		    GPIO_Pin_13		        /* 连接到SCL时钟线的GPIO */

// DRV8825 DIR方向信号
#define DrDIR_GPIO_PORT    	GPIOB/* GPIO端口 */
#define DrDIR_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define DrDIR_GPIO_PIN		GPIO_Pin_15 
#endif	/* __BSP_TIMEBASE_H */
