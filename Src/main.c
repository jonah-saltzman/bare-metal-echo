#include "sys/stm32f4xx.h"
#include "init.h"
#include "io.h"
#include "timers.h"

int main(void)
{
	const char* m = "welcome...\n";
	basic_transfer(m, 11);
	unsigned char msg[100];
	while (1)
	{
		readline(0, msg);
		static_print((const char*)msg, 1);
	}
}
