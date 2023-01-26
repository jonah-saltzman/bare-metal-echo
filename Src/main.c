#include <stdio.h>
#include <stdlib.h>
#include "../Inc/sys/stm32f4xx.h"
#include "../Inc/init.h"
#include "../Inc/io.h"
#include "../Inc/timers.h"
#include "../Inc/display.h"

int main(void)
{
	// initialize_TIM2_5(TIM2, 10000, 0, 40);
	// initialize_TIM2_5(TIM5, 10000, 0, 41);
	// initialize_IO();

	// enable_ext_intr(50);

	// start_timer(TIM2);

	printf("welcome...\n");

	char* msg;
	while (1)
	{
		msg = readline(0);
		printf("%s\n\n", msg);
		free(msg);
	}
}
