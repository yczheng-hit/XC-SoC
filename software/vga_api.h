#ifndef __VGA_API__
#define __VGA_API__
#include <stdint.h>

typedef struct
{
	volatile uint32_t VGA_CTRL_GLOBAL;
	volatile uint32_t VGA_STATUS_GLOBAL;
} VGAGlobalType;

typedef struct
{
	volatile uint32_t VGA_CTRL_BLOCK[12][32];
} VGABlockType;

#define VGA_GLOBAL_BASE 0x40010000
#define VGA_GLOBAL ((VGAGlobalType *)VGA_GLOBAL_BASE)

#define VGA_BLOCK_BASE 0x40011000
#define VGA_BLOCK ((VGABlockType *)VGA_BLOCK_BASE)

#define SELFCHAR(ch) (ch + '~' + 1)
#define NUM2CHAR(num) (((num) <= 9) ? ((num) + '0') : ((num) <= 15) ? ((num)-10 + 'a') \
																	: '0')
#define CHAR2IMAGE(ch) (ch - ' ')
#define RGB(R, G, B) (((R & 0x7) << 6) | ((G & 0x7) << 3) | (B & 0x7))
#define BLOCK_CTRL(TYPE, BOARD, BACKGROUND, COLOR) (((TYPE & 0xff) << 24) | ((BOARD & 0xf) << 18) | ((BACKGROUND & 0x1ff) << 9) | (COLOR & 0x1ff))

// VGA
uint32_t VGA_Read_Ctrl_Global(void);
uint32_t VGA_Read_Status_Global(void);
void VGA_Write_Ctrl_Global(uint32_t data);
void VGA_Write_Status_Global(uint32_t state);
uint32_t VGA_Read_Block(uint8_t h, uint8_t v);
void VGA_Write_Block(uint32_t data, uint8_t h, uint8_t v);

void VGA_Write_Char_Row(uint8_t *ch, uint8_t r_start, uint8_t r_end, uint8_t c);
void VGA_Write_Char_Column(uint8_t *ch, uint8_t c_start, uint8_t c_end, uint8_t r);

void VGA_Print_Right(uint8_t *ch, uint8_t c);
void VGA_Print_Left(uint8_t *ch, uint8_t c, uint8_t n);
void VGA_Print_Mediate(uint8_t *ch, uint8_t c);
void frame(unsigned int color);
void Display_Info(void);
void Display_FM(void);
#endif
