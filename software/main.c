/*
 * @Author: yczheng-hit
 * @Date: 2022-04-02 14:30:35
 * @LastEditTime: 2022-04-14 11:14:19
 * @LastEditors: yczheng-hit
 * @Description: Main.c of XC-SoC Software
 */

#include "XC-SoC.h"
#include "uart_api.h"
#include "vga_api.h"
#include "spi_api.h"

/*Defination*/
// #define VGA_PRINT_TEST
/*Global Variable*/
int row, col;
unsigned int tick = 0;
/*UART Interupt Handler*/
void UART_Handler()
{
  // char ch;
  // ch = ReadUART();
  for (int i = 0; i < 16; i++)
  {
    uart_fifo[i] = ReadUART();
  }
  for (int i = 0; i < 16; i++)
  {
    WriteUART(uart_fifo[i]);
  }
  // VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(ch), 0, RGB(0, 0, 0), RGB(7, 7, 7)), row, col);
  // row++;
  // if (row >= 32)
  // {
  //   row = 0;
  //   col++;
  //   if (col >= 12)
  //     col = 0;
  // }
}

/*SysTick Interupt Handler*/
//2HZ
void SysTick_Handler()
{
  unsigned int mi,se;
  tick++;
  se = (tick>>2)%60;
  mi = (tick>>2)/60;
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE((mi/10)+'0'), 0, RGB(0, 0, 0), RGB(7, 7, 7)), 0, 0);
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE((mi%10)+'0'), 0, RGB(0, 0, 0), RGB(7, 7, 7)), 1, 0);
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(':'), 0, RGB(0, 0, 0), RGB(7, 7, 7)), 2, 0);
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE((se/10)+'0'), 0, RGB(0, 0, 0), RGB(7, 7, 7)), 3, 0);
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE((se%10)+'0'), 0, RGB(0, 0, 0), RGB(7, 7, 7)), 4, 0);
//  frame(RGB(tick,tick>>1,tick>>2));
  // printf("Systick Handler!\n");
}

/*Systick Init*/
uint32_t Systick_Init(void)
{
  SysTick->CTRL = 0;
  // CPU clk 40MHz
  SysTick->LOAD = 10000000;
  SysTick->VAL = 0;
  SysTick->CTRL = 0x7;
  while (SysTick->VAL == 0)
    ;
  return (SysTick->VAL);
}
/*Main Function*/
int main(void)
{
  NVIC_EnableIRQ(UART_IRQn);
  Systick_Init();
  VGA_Write_Status_Global(VGA_Read_Ctrl_Global());
  VGA_Write_Ctrl_Global(VGA_Read_Status_Global());
  printf("** TEST PASSED0 **\n");
#ifdef VGA_PRINT_TEST
  // printf("** VGA PRINT TEST START!n");
  VGA_Print_Left("Hello!", 0, 0);
  VGA_Print_Left("Welcome to XC-SoC", 1, 0);
  VGA_Print_Left("Welcome to XC-SoC", 2, 1);
  VGA_Print_Left("Welcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoC", 3, 0);
  VGA_Print_Left("Welcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoCWelcome to XC-SoC", 4, 1);
  VGA_Print_Mediate("Welcome to XC-SoC", 9);
  VGA_Print_Right("Welcome to XC-SoC", 11);
  while (1)
  {
  }
#endif
  
  printf("** TEST PASSED1 **\n");
  Display_Info();
  Display_FM();
  while (1)
  {
    unsigned char ch;
  again:
    ch = ReadUART_NoWait();
    if ((ch == 0) || (ch == '\n') || (ch == '\r'))
    {
      /* code */
      goto again;
    }

    switch (ch)
    {
    case '1':
      printf("Received: 1\n");
      break;
    default:
      printf("Command Error\n");
      break;
    }
    printf("Received: %c\n", ch);
  }
}
