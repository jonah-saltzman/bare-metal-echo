extern volatile uint16_t rxbuffer_pos;
extern volatile uint8_t rxbuffer[0x1000];
extern volatile uint8_t line_ready;

char* readline(const char* prompt);
void uart3_writechar(int c);
int __io_putchar(int ch);