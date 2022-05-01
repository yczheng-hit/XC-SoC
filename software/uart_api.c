#include "uart_api.h"
#include <stdint.h>
#include <string.h>

#if defined(__CC_ARM)
/******************************************************************************/
/* Retarget functions for ARM DS-5 Professional / Keil MDK                                 */
/******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <rt_misc.h>
#pragma import(__use_no_semihosting_swi)

struct __FILE
{
	int handle; /* Add whatever you need here */
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
	WriteUART(ch);
	return (ch);
}

int ferror(FILE *f)
{
	/* Your implementation of ferror */
	return EOF;
}

void _ttywrch(int ch)
{
	WriteUART(ch);
}

void _sys_exit(int return_code)
{
label:
	goto label; /* endless loop */
}

#else

/******************************************************************************/
/* Retarget functions for GNU Tools for ARM Embedded Processors               */
/******************************************************************************/
#include <stdio.h>
#include <sys/stat.h>
__attribute__((used)) int _write(int fd, char *ptr, int len)
{
	size_t i;
	for (i = 0; i < len; i++)
	{
		WriteUART(ptr[i]); // call character output function
	}
	return len;
}

#endif

char ReadUARTState()
{
	char state;
	state = UART->UARTTX_STATE;
	return (state);
}

char ReadUART()
{
	char data;
	data = UART->UARTRX_DATA;
	return (data);
}

void WriteUART(char data)
{
	while (ReadUARTState())
		;
	UART->UARTTX_DATA = data;
}
