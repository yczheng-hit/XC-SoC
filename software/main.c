/*
 * @Author: yczheng-hit
 * @Date: 2022-04-02 14:30:35
 * @LastEditTime: 2022-04-14 11:14:19
 * @LastEditors: yczheng-hit
 * @Description: Main.c of XC-SoC Software
 */

#include "stdio.h"
#include "XC-SoC.h"
#include "uart_api.h"
#include "vga_api.h"

/*Defination*/
#define VGA_PRINT_TEST
/*Global Variable*/
int row, col;

/*UART Interupt Handler*/
void UART_Handler()
{
  char ch;
  ch = ReadUART();
  WriteUART(ch);
  VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(ch), 0, RGB(0, 0, 0), RGB(7, 7, 7)), row, col);
  row++;
  if (row >= 32)
  {
    row = 0;
    col++;
    if (col >= 12)
      col = 0;
  }
}

/*SysTick Interupt Handler*/
void SysTick_Handler()
{
  printf("Systick Handler!\n");
}

/*Systick Init*/
uint32_t Systick_Init(void)
{
  SysTick->CTRL = 0;
  // CPU clk 25MHz
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

  while (1)
  {
  }
}
