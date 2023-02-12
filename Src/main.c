#include "sys/stm32f4xx.h"
#include "init.h"
#include "io.h"
#include "timers.h"

int main(void)
{

	static_print("welcome...\n", 0);
	unsigned char msg[100];
	while (1)
	{
		readline(0, msg);
		static_print((const char*)msg, 1);
	}
}
