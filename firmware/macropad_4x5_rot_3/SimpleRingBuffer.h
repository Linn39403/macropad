#ifndef __SIMPLE_RING_BUFFER_H
#define __SIMPLE_RING_BUFFER_H

#define RINGFIFO_nSIZE (16u)               /* serial buffer in bytes (power 2)  */
#define RINGFIFO_MASK (RINGFIFO_nSIZE-1ul)  /* buffer size mask                  */

#if RINGFIFO_nSIZE <= 0xFF
    #define RINGFIFO_DATA_INDX_TYPE uint8_t
#elif RINGFIFO_nSIZE <= 0xFFFF
    #define RINGFIFO_DATA_INDX_TYPE uint16_t
#elif RINGFIFO_nSIZE <= 0xFFFFFFFF
    #define RINGFIFO_DATA_INDX_TYPE uint32_t
#else
    #error "RINGFIFO_nSIZE is too large"
#endif

typedef struct
{
    RINGFIFO_DATA_INDX_TYPE m_uxWrIdx;
    RINGFIFO_DATA_INDX_TYPE m_uxRdIdx;
    uint8_t m_au8Data[RINGFIFO_nSIZE];
} RNGBUF_tstFIFO;

/******************* RingBuffer Functions *******************/
#define RINGFIFO_RESET(ringFifo)      {ringFifo.m_uxRdIdx = ringFifo.m_uxWrIdx = 0;}
#define RINGFIFO_EMPTY(ringFifo)      (ringFifo.m_uxRdIdx == ringFifo.m_uxWrIdx)

#define RINGFIFO_WR(ringFifo, dataIn) {ringFifo.m_au8Data[RINGFIFO_MASK & ringFifo.m_uxWrIdx++] = (dataIn);}
#define RINGFIFO_RD(ringFifo, dataOut){ringFifo.m_uxRdIdx++; dataOut = ringFifo.m_au8Data[RINGFIFO_MASK & (ringFifo.m_uxRdIdx-1)];}

#define RINGFIFO_FULL(ringFifo)       ((RINGFIFO_MASK & ringFifo.m_uxRdIdx) == (RINGFIFO_MASK & (ringFifo.m_uxWrIdx+1)))
#define RINGFIFO_COUNT(ringFifo)      (RINGFIFO_MASK & (ringFifo.m_uxWrIdx - ringFifo.m_uxRdIdx))


#endif
