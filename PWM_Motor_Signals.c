#include "PWM_Motor_Signals.h"
#include "throttle.h"

/*This will be used to initialize Port A pins 5, 1-3,
    and assign Timer 2, Channels 1-4, to each pin respectively
    Channel 'x' will be used to send PWM signals to Motor 'x'
	
	pin setup:
	Alterate Function 2 
	Timer 2, Channels 1-4
	
	default clock frequency is 80Mhz
*/

void Motor_PWM_Init()
{

    //port A clock enable
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
