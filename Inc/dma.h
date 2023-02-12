#ifndef DMA_H_
#define _H_
#include "sys/stm32f439xx.h"

#define FEIF_BIT  (1UL << 0)
#define DMEIF_BIT (1UL << 2)
#define TEIF_BIT  (1UL << 3)
#define HTIF_BIT  (1UL << 4)
#define TCIF_BIT  (1UL << 5)

#define STREAM0_4_SHIFT (0UL)
#define STREAM1_5_SHIFT (6UL)
#define STREAM2_6_SHIFT (16UL)
#define STREAM3_7_SHIFT (22UL)

#define ICF_BITS (FEIF_BIT | DMEIF_BIT | TEIF_BIT | HTIF_BIT | TCIF_BIT)

void reset_dma(DMA_Stream_TypeDef *stream);
#endif