#ifndef __XC_SOC__
#define __XC_SOC__

#include <stdint.h>

typedef enum IRQn
{
  /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/

  /* ToDo: use this Cortex interrupt numbers if your device is a CORTEX-M0 device                   */
  NonMaskableInt_IRQn = -14, /*!<  2 Cortex-M0 Non Maskable Interrupt              */
  HardFault_IRQn = -13,      /*!<  3 Cortex-M0 Hard Fault Interrupt                */
  SVCall_IRQn = -5,          /*!< 11 Cortex-M0 SV Call Interrupt                   */
  PendSV_IRQn = -2,          /*!< 14 Cortex-M0 Pend SV Interrupt                   */
  SysTick_IRQn = -1,         /*!< 15 Cortex-M0 System Tick Interrupt               */

  /******  CMSDK Specific Interrupt Numbers *********************************************************/
  UART_IRQn = 0, /*!< UART 0 RX Interrupt                               */

} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __CM0_REV 0x0000         /*!< Core Revision r0p0                               */
#define __NVIC_PRIO_BITS 2       /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used     */
#define __MPU_PRESENT 0          /*!< MPU present or not                               */

/*@}*/ /* end of group CMSDK_CMSIS */

#include "core_cm0.h" /* Cortex-M0 processor and core peripherals           */

#endif
