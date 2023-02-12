#include "sys/stm32f439xx.h"
#include "init.h"
#include "dma.h"

void reset_dma(DMA_Stream_TypeDef *stream)
{
    stream->CR &= (~1UL); // disable stream

    // clear interrupt bits
    uint32_t icf_bits = ICF_BITS;
    switch((uint32_t) stream)
    {
        case DMA1_Stream0_BASE:
        case DMA1_Stream4_BASE:
        case DMA2_Stream0_BASE:
        case DMA2_Stream4_BASE:
            icf_bits <<= STREAM0_4_SHIFT;
            break;
        case DMA1_Stream1_BASE:
        case DMA1_Stream5_BASE:
        case DMA2_Stream1_BASE:
        case DMA2_Stream5_BASE:
            icf_bits <<= STREAM1_5_SHIFT;
            break;
        case DMA1_Stream2_BASE:
        case DMA1_Stream6_BASE:
        case DMA2_Stream2_BASE:
        case DMA2_Stream6_BASE:
            icf_bits <<= STREAM2_6_SHIFT;
            break;
        case DMA1_Stream3_BASE:
        case DMA1_Stream7_BASE:
        case DMA2_Stream3_BASE:
        case DMA2_Stream7_BASE:
            icf_bits <<= STREAM3_7_SHIFT;
            break;
        default:
            abort();
    }

    uint32_t dma_base_addr = (uint32_t)stream >= DMA2_BASE ? DMA2_BASE : DMA1_BASE; // s3 = 0x40026000
    uint32_t dma_offset = (uint32_t)stream - dma_base_addr; // s3 = 0x58
    uint32_t dma_ifcr_reg = dma_base_addr + (dma_offset >= 0x70UL ? 0xCUL : 0x8UL); // s3 = 0x40026008
    *(uint32_t*)dma_ifcr_reg = icf_bits;
}