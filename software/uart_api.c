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
// #include <stdio.h>
// #include <sys/stat.h>
// __attribute__((used)) int _write(int fd, char *ptr, int len)
// {
// 	size_t i;
// 	for (i = 0; i < len; i++)
// 	{
// 		WriteUART(ptr[i]); // call character output function
// 	}
// 	return len;
// }
#include <stdarg.h>

static char digits[] = "0123456789abcdef";
static void
printint(int xx, int base, int sign)
{
  char buf[16];
  int i;
  unsigned int x;

  if(sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do {
    buf[i++] = digits[x % base];
  } while((x /= base) != 0);

  if(sign)
    buf[i++] = '-';

  while(--i >= 0)
    WriteUART(buf[i]);
}

static void
printptr(unsigned int x)
{
  int i;
  WriteUART('0');
  WriteUART('x');
  for (i = 0; i < (sizeof(unsigned int) * 2); i++, x <<= 4)
    WriteUART(digits[x >> (sizeof(unsigned int) * 8 - 4)]);
}

void
printf(char *fmt, ...)
{
  va_list ap;
  int i, c, locking;
  char *s;

  va_start(ap, fmt);
  for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
    if(c != '%'){
      WriteUART(c);
      continue;
    }
    c = fmt[++i] & 0xff;
    if(c == 0)
      break;
    switch(c){
    case 'd':
      printint(va_arg(ap, int), 10, 1);
      break;
    case 'x':
      printint(va_arg(ap, int), 16, 1);
      break;
    case 'p':
      printptr(va_arg(ap, unsigned int));
      break;
    case 's':
      if((s = va_arg(ap, char*)) == 0)
        s = "(null)";
      for(; *s; s++)
        WriteUART(*s);
      break;
    case '%':
      WriteUART('%');
      break;
    default:
      // Print unknown % sequence to draw attention.
      WriteUART('%');
      WriteUART(c);
      break;
    }
  }
}
#endif
unsigned char uart_fifo[16];
char ReadUARTState()
{
	char state;
	state = UART->UARTTX_STATE;
	return (state);
}

char ReadUART()
{
	char data;
	while (ReadUARTState()&0x2)
		;
	data = UART->UARTRX_DATA;
	return (data);
}

char ReadUART_NoWait()
{
	char data;
	if(ReadUARTState()&0x2){
		return 0;
	}
	data = UART->UARTRX_DATA;
	return (data);
}

void WriteUART(char data)
{
	while (ReadUARTState()&0x1)
		;
	UART->UARTTX_DATA = data;
}
