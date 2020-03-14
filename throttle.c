
#include "throttle.h"

void increaseThrottle(void)
{

	if ((TIM2->CCR3 + 1) >= MAX_THROTTLE)
	{
		TIM2->CCR1 = MAX_THROTTLE;
		TIM2->CCR2 = MAX_THROTTLE;
		TIM2->CCR3 = MAX_THROTTLE;
		TIM2->CCR4 = MAX_THROTTLE;
	}
	else
	{
		TIM2->CCR1 += STEP_THROTTLE;
		TIM2->CCR2 += STEP_THROTTLE;
		TIM2->CCR3 += STEP_THROTTLE;
		TIM2->CCR4 += STEP_THROTTLE;
	}
}

void Motor1_increase(void)
{

	if ((TIM2->CCR1 + STEP_THROTTLE) >= MAX_THROTTLE)
	{
		TIM2->CCR1 = MAX_THROTTLE;
	}
	else
	{
		TIM2->CCR1 += STEP_THROTTLE;
	}
}

void Motor2_increase(void)
{

	if ((TIM2->CCR2 + STEP_THROTTLE) >= MAX_THROTTLE)
	{
		TIM2->CCR2 = MAX_THROTTLE;
	}
	else
	{
		TIM2->CCR2 += STEP_THROTTLE;
	}
}

void Motor3_increase(void)
{

	if ((TIM2->CCR3 + STEP_THROTTLE) >= MAX_THROTTLE)
	{
		TIM2->CCR3 = MAX_THROTTLE;
	}
	else
	{
		TIM2->CCR3 += STEP_THROTTLE;
	}
}

void Motor4_increase(oid)
{

	if ((TIM2->CCR4 + STEP_THROTTLE) >= MAX_THROTTLE)
	{
		TIM2->CCR4 = MAX_THROTTLE;
	}
	else
	{
		TIM2->CCR4 += STEP_THROTTLE;
	}
}

void decreaseThrottle(void)
{

	if ((TIM2->CCR3 - 1) <= MIN_THROTTLE)
	{
		TIM2->CCR1 = MIN_THROTTLE;
		TIM2->CCR2 = MIN_THROTTLE;
		TIM2->CCR3 = MIN_THROTTLE;
		TIM2->CCR4 = MIN_THROTTLE;
	}
	else
	{
		TIM2->CCR1 -= STEP_THROTTLE;
		TIM2->CCR2 -= STEP_THROTTLE;
		TIM2->CCR3 -= STEP_THROTTLE;
		TIM2->CCR4 -= STEP_THROTTLE;
	}
}

void Motor1_decrease(void)
{

	if ((TIM2->CCR1 - STEP_THROTTLE) <= MIN_THROTTLE)
	{
		TIM2->CCR1 = MIN_THROTTLE;
	}
	else
	{
		TIM2->CCR1 -= STEP_THROTTLE;
	}
}

void Motor2_decrease(void)
{

	if ((TIM2->CCR2 - STEP_THROTTLE) <= MIN_THROTTLE)
	{
		TIM2->CCR2 = MIN_THROTTLE;
	}
	else
	{
		TIM2->CCR2 -= STEP_THROTTLE;
	}
}

void Motor3_decrease(void)
{

	if ((TIM2->CCR3 - STEP_THROTTLE) <= MIN_THROTTLE)
	{
		TIM2->CCR3 = MIN_THROTTLE;
	}
	else
	{
		TIM2->CCR3 -= STEP_THROTTLE;
	}
}

void Motor4_decrease(void)
{

	if ((TIM2->CCR4 - STEP_THROTTLE) <= MIN_THROTTLE)
	{
		TIM2->CCR4 = MIN_THROTTLE;
	}
	else
	{
		TIM2->CCR4 -= STEP_THROTTLE;
	}
}

void killThrottle(void)
{
	TIM2->CCR1 = MIN_THROTTLE;
	TIM2->CCR2 = MIN_THROTTLE;
	TIM2->CCR3 = MIN_THROTTLE;
	TIM2->CCR4 = MIN_THROTTLE;
}
