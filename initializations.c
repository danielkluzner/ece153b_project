

/*This will be used to initialize PortA pins 5, 1-3
  Port A pin x will be used to send PWM signals to Motor(x +1)
	
	pin setup
	Alterate Function 2 
	Timer 2, Channels 1-4
	
	default clock frequency is 4Mhz
*/

#include "initializations.h"

void PWM_Init()
{

	//port A clock in it
	//port A used for onboard joystick, interrupts, and PWM pins
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	// RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	//Timer 2 clock enable on peripheral bus (PWM clock)
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; //Timer 2 Clock

	//GPIO pin and Timer initialization
	//Port A, Pin 5, 1, 2, 3 will correspond to
	//motors 1, 2, 3, 4, respectively,
	//as well as Timer 2 channels 1, 2, 3, 4, respectively

	// Configure PA5,1,2,3 for alternate function mode (10)
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_0;

	GPIOA->MODER |= GPIO_MODER_MODE1_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_0;

	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2_0;

	GPIOA->MODER |= GPIO_MODER_MODE3_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE3_0;

	//ospeed to very high (11)

	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;

	//no pull up pull down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;

	//select AF1 for TIM2
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_0;

	// Configure PWM Output for TIM1 CH 1
	//default: 4MHz clock
	TIM2->CR1 &= ~TIM_CR1_DIR;
	TIM2->PSC = 15;   //frequency = 80MH / (PSC + 1) = 5MHz -> 0.2us increment on counter
	TIM2->ARR = 9999; //# steps before reload -> 10,000 * 0.2us = 2ms PWM signal period

	//set output compare mode to PWM mode 1 (0110)
	//channel active while TIM2_CNT < TIM2_CCR1
	//channel 1
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;
	//channel 2
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_2;
	//channel 3
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_2;
	//channel 4
	TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_2;

	//preload enable
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2->CCMR2 |= TIM_CCMR2_OC3PE;
	TIM2->CCMR2 |= TIM_CCMR2_OC4PE;

	//capture/compare output polarity
	//0: active high
	TIM2->CCER &= ~TIM_CCER_CC1P;
	TIM2->CCER &= ~TIM_CCER_CC2P;
	TIM2->CCER &= ~TIM_CCER_CC3P;
	TIM2->CCER &= ~TIM_CCER_CC4P;

	//capture compare output enable by channel
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CCER |= TIM_CCER_CC3E;
	TIM2->CCER |= TIM_CCER_CC4E;

	//auto-reload preload set ot buffer
	TIM2->CR1 |= TIM_CR1_ARPE;

	//initialize all registers
	TIM2->EGR |= TIM_EGR_UG;

	//ensure set to edge Aligned mode (00)
	TIM2->CR1 &= ~TIM_CR1_CMS;

	//ensure set to upcounting
	TIM2->CR1 &= ~TIM_CR1_DIR;

	//set compare value
	TIM2->CCR1 = START_THROTTLE;
	TIM2->CCR2 = START_THROTTLE;
	TIM2->CCR3 = START_THROTTLE;
	TIM2->CCR4 = START_THROTTLE;

	//enable counter
	TIM2->CR1 |= TIM_CR1_CEN;
}

void joystick_init()
{

	//PA3 and 5 correspond to up and down, respectively

	// Initialize Joystick
	//	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	//	GPIOA->MODER &= ~GPIO_MODER_MODE1;
	//	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	// GPIOA->MODER &= ~GPIO_MODER_MODE3;
	// GPIOA->MODER &= ~GPIO_MODER_MODE5;

	//	GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
	//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_0;
	//
	//	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;
	//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1_0;
	//
	//	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_1;
	//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_0;

	// GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_1;
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3_0;

	// GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1;
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
}

void interrupt_init()
{
	// Configure SYSCFG EXTI
	//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	//
	//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
	//
	//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;

	// SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	// SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;

	// SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR2_EXTI5;
	// SYSCFG->EXTICR[0] |= SYSCFG_EXTICR2_EXTI5_PA;

	// Configure EXTI Trigger
	//	EXTI->FTSR1 |= EXTI_FTSR1_FT0;
	//	EXTI->FTSR1 |= EXTI_FTSR1_FT1;
	//	EXTI->FTSR1 |= EXTI_FTSR1_FT2;
	// EXTI->FTSR1 |= EXTI_FTSR1_FT3;
	// EXTI->FTSR1 |= EXTI_FTSR1_FT5;

	// Enable EXTI
	//	EXTI->IMR1 |= EXTI_IMR1_IM0;
	//	EXTI->IMR1 |= EXTI_IMR1_IM1;
	//	EXTI->IMR1 |= EXTI_IMR1_IM2;
	// EXTI->IMR1 |= EXTI_IMR1_IM3;
	// EXTI->IMR1 |= EXTI_IMR1_IM5;

	// Configure and Enable in NVIC
	//	NVIC_EnableIRQ(EXTI0_IRQn);
	//	NVIC_SetPriority(EXTI0_IRQn, 0);
	//	NVIC_EnableIRQ(EXTI1_IRQn);
	//	NVIC_SetPriority(EXTI1_IRQn, 0);
	//	NVIC_EnableIRQ(EXTI2_IRQn);
	//	NVIC_SetPriority(EXTI2_IRQn, 0);
	// NVIC_EnableIRQ(EXTI3_IRQn);
	// NVIC_SetPriority(EXTI3_IRQn, 0);
	// NVIC_EnableIRQ(EXTI9_5_IRQn);
	// NVIC_SetPriority(EXTI9_5_IRQn, 0);
}
