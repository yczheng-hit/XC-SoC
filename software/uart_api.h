#ifndef __UART_API__
#define __UART_API__
#include <stdint.h>
// UART DEF
typedef struct
{
	volatile uint32_t UARTRX_DATA;
	volatile uint32_t UARTTX_STATE;
	volatile uint32_t UARTTX_DATA;
} UARTType;
extern unsigned char uart_fifo[16];
#define UART_BASE 0x40000010
#define UART ((UARTType *)UART_BASE)

// UART
#if defined(__CC_ARM)
#include <stdio.h>
#else
void printf(char *fmt, ...);
#endif
char ReadUARTState(void);
char ReadUART(void);
char ReadUART_NoWait(void);
void WriteUART(char data);

#endif
