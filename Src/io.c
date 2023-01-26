#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Inc/sys/stm32f4xx.h"
#include "../Inc/syscalls.h"

volatile uint16_t rxbuffer_pos = 0;
volatile uint8_t rxbuffer[0x1000] = {0};
volatile uint8_t line_ready = 0;

char* readline(const char* prompt)
{
	if (prompt)
		force_print((char*)prompt, strlen(prompt), 0);
	while (!line_ready)
		__WFI();
	__disable_irq();
	char* line = (char*)malloc(rxbuffer_pos);
	memcpy(line, (char*)rxbuffer, rxbuffer_pos);
	line[rxbuffer_pos - 1] = '\0';
	rxbuffer_pos = 0;
	line_ready = 0;
	__enable_irq();
	return line;
}

void uart3_writechar(int c)
{
	while ((USART3->SR & (1UL << 7)) == 0)
	{
	}
	USART3->DR = (c & 0xFF);
}

int __io_putchar(int ch)
{
	uart3_writechar(ch);
	return 1;
}
