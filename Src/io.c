#include "sys/stm32f4xx.h"
#include "init.h"
#include "io.h"

static struct IOBuffer rxbuffer = {0};

static volatile uint8_t line_ready = 0;

void static_print(const char *ptr, uint8_t r)
{
	while (*ptr != '\0')
		__io_putchar(*ptr++);
	if (r)
	{
		__io_putchar('\r');
	}
}

int read_buf(IOBuffer *buf, uint8_t *dst, uint16_t len)
{
	__disable_irq();
	uint16_t i = 0;
	for (; i < len; ++i)
	{
		if (buf->reader == buf->writer)
			break;
		dst[i] = buf->buf[buf->reader];
		buf->reader = (++buf->reader) % IO_BUFSIZE;
	}
	__enable_irq();
	return i;
}

int write_buf(IOBuffer *buf, uint8_t *src, uint16_t len)
{
	__disable_irq();
	uint16_t i = 0;
	for (; i < len; ++i)
	{
		buf->buf[buf->writer] = src[i];
		buf->writer = (++buf->writer) % IO_BUFSIZE;
		if (buf->reader == buf->writer)
			buf->reader += 1;
	}
	__enable_irq();
	return i;
}

void writec_buf(IOBuffer *buf, unsigned char c)
{
	if (write_buf(buf, &c, 1) != 1)
		abort();
}

unsigned char readc_buf(IOBuffer *buf)
{
	unsigned char c;
	if (read_buf(buf, &c, 1) != 1)
		abort();
	return c;
}

int readline(const char *prompt, unsigned char* buf)
{
	if (prompt)
		static_print((char *)prompt, 0);
	while (!line_ready)
		__WFI();
	unsigned char c;
	int i = 0;
	while ((c = readc_buf(&rxbuffer)) != '\n') {
		buf[i] = c;
		++i;
	}
	buf[i] = '\0';
	line_ready = 0;
	return i + 1;
}

void USART3_IRQHandler(void)
{
	uint8_t ch = USART3->DR & 0xFF;
	writec_buf(&rxbuffer, ch);
	uart3_writechar(ch);
	if (ch == '\n')
		line_ready = 1;
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
