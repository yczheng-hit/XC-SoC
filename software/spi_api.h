#ifndef __SPI_API__
#define __SPI_API__
#include <stdint.h>
#include <stdbool.h>
// SPI DEF
typedef struct
{
	volatile uint32_t SPI_CONTROL;
	volatile uint32_t SPI_STATE;
	volatile uint32_t SPI_DATA;
	volatile uint32_t SPI_EXTENSION;
} SPIType;
#define SPI_BASE 0x40000020
#define SPI ((SPIType *)SPI_BASE)

typedef struct
{
    bool L1:1;
	bool L2:1;
	bool La:1;
	bool Lb:1;
	bool Lc:1;
	bool Ld:1;
    bool R1:1;
	bool R2:1;
	bool Ra:1;
	bool Rb:1;
	bool Rc:1;
	bool Rd:1;
}PS2;

#define PS2_OFFSET_L2     	((uint8_t)0x01<<0)
#define PS2_OFFSET_R2     	((uint8_t)0x01<<1)
#define PS2_OFFSET_L1     	((uint8_t)0x01<<2)
#define PS2_OFFSET_R1     	((uint8_t)0x01<<3)

#define PS2_OFFSET_a      	((uint8_t)0x01<<4)
#define PS2_OFFSET_b      	((uint8_t)0x01<<5)
#define PS2_OFFSET_c      	((uint8_t)0x01<<6)
#define PS2_OFFSET_d      	((uint8_t)0x01<<7)
void Get_PS2_Data(PS2 *PS2_data,bool verbose);

#endif
