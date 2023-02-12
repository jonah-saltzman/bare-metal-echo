#ifndef IO_H_
#define IO_H_

#define IO_BUFSIZE ((uint16_t)0x100U)

typedef struct IOBuffer
{
    volatile uint8_t buf[IO_BUFSIZE];
    volatile uint16_t reader;
    volatile uint16_t writer;
} IOBuffer;

void basic_transfer(const char* str, uint16_t len);
void static_print(const char *ptr, uint8_t r);
int readline(const char *prompt, unsigned char* buf);
void flush_buf(IOBuffer* buf);
int read_buf(IOBuffer* buf, uint8_t* dst, uint16_t len);
int write_buf(IOBuffer* buf, uint8_t* src, uint16_t len);
void writec_buf(IOBuffer *buf, unsigned char c);
unsigned char readc_buf(IOBuffer *buf);

void uart3_writechar(int c);
int __io_putchar(int ch);

#endif
