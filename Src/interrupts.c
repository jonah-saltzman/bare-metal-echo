#include <stdio.h>
#include "../Inc/sys/stm32f4xx.h"
#include "../Inc/timers.h"
#include "../Inc/display.h"
#include "../Inc/io.h"

void USART3_IRQHandler(void)
{
	uint8_t ch = USART3->DR & 0xFF;
	rxbuffer[rxbuffer_pos] = ch;
	++rxbuffer_pos;
	uart3_writechar(ch);
	if (ch == '\n')
		line_ready = 1;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= (~1UL);
	GPIOB->ODR &= ~GPIO_ODR_OD14_Msk;
}

void TIM5_IRQHandler(void)
{
	TIM5->SR &= (~1UL);
	GPIOB->ODR &= ~GPIO_ODR_OD0_Msk;
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	TIM10->SR &= (~1UL);
	// if (timer10_ticks)
	// {
	// 	--timer10_ticks;
	// }
	// else
	// {
	// 	GPIOB->ODR &= (~GPIO_ODR_OD14_Msk);
	// 	TIM10->CR1 &= (~1UL);
	// 	timer10_counting = 0;
	// 	printf("error led done\n");
	// }
}


// button press
void EXTI15_10_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR13;
	// if (timer5_counting)
	// {
	// 	stop_timer(TIM5);
	// }
	// else
	// {
	// 	start_timer(TIM5);
	// }
}


void HardFault_Handler(void)
{
	if (SCB->HFSR & (1UL << 30))
	{
		printf("FORCED hard fault\n");
		printf("MMFAR: %p\n", (void*)SCB->MMFAR);
		printf("BFAR: %p\n", (void*)SCB->BFAR);
		printf("MMFAR valid: %s\n", (SCB->CFSR & SCB_CFSR_MMARVALID_Msk) ? "true" : "false");
		printf("BFAR valid: %s\n", (SCB->CFSR & SCB_CFSR_BFARVALID_Msk) ? "true" : "false");
		uint32_t cfsr = SCB->CFSR;
		cfsr++;
	}
	if (SCB->HFSR & (1UL << 1))
	{
		printf("Vector table fault\n");
	}
	while (1)
	{
	}
}

void MemManage_Handler(void)
{
	while (1)
	{
	}
}

void BusFault_Handler(void)
{
	while (1)
	{
	}
}

void UsageFault_Handler(void)
{
	while (1)
	{
	}
}

void WWDG_IRQHandler(void)
{
	while (1)
	{
	}
}
