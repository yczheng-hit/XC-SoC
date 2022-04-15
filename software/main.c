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
/*UART Interupt Handler*/
void UART_Handler()
{
  WriteUART(ReadUART());
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
  SysTick->LOAD = 12500000;
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
  printf("** TEST PASSED **\n");
  printf("** TEST PASSED **\n");
  printf("** TEST PASSED **\n");
  while (1)
  {
  }
}
