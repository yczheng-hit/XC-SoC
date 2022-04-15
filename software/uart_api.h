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

#define UART_BASE 0x40000010
#define UART ((UARTType *)UART_BASE)

// UART
char ReadUARTState(void);
char ReadUART(void);
void WriteUART(char data);

#endif
