#include "vga_api.h"

uint32_t VGA_Read_Ctrl_Global(){
	return VGA_GLOBAL->VGA_CTRL_GLOBAL;
}
uint32_t VGA_Read_Status_Global(){
	
	return VGA_GLOBAL->VGA_STATUS_GLOBAL;
}

void VGA_Write_Ctrl_Global(uint32_t data){
	VGA_GLOBAL->VGA_CTRL_GLOBAL = data;
}

void VGA_Write_Status_Global(uint32_t state){
	VGA_GLOBAL->VGA_STATUS_GLOBAL = state;
}

uint32_t VGA_Read_Block(uint8_t h,uint8_t v){
	return VGA_BLOCK->VGA_CTRL_BLOCK[v][h];
}

void VGA_Write_Block(uint32_t data,uint8_t h,uint8_t v){
	VGA_BLOCK->VGA_CTRL_BLOCK[v&0xf][h&0x1f] = data;
}

uint8_t Get_String_Leng(uint8_t *ch){
	uint8_t *ch_start;
	ch_start = ch;
	uint8_t i = 0;
	while (*ch++)
	{
		i++;
	}
	ch = ch_start;
	return i;
}

// n means next line if the string is to long
void VGA_Print_Mediate(uint8_t *ch,uint8_t c){
	uint8_t tmp;
	uint8_t size;
	size = Get_String_Leng(ch);
	for (int i = 0; i < size; i++)
	{
		tmp = *ch++;
		if(!tmp)
			return;
		if(size>31)
			size = 31;
		VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), (15-(size>>1))+i, c);
	}
}

void VGA_Print_Right(uint8_t *ch,uint8_t c){
	uint8_t tmp;
	uint8_t size;
	size = Get_String_Leng(ch);
	for (int i = 0; i < size; i++)
	{
		tmp = *ch++;
		if(!tmp)
			return;
		if(size>31)
			size = 31;
		VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), 31-size+i, c);
	}
}

void VGA_Print_Left(uint8_t *ch,uint8_t c,uint8_t n){
	uint8_t tmp;
	uint8_t size;
	size = Get_String_Leng(ch);
	for (int i = 0; i < size; i++)
	{
		tmp = *ch++;
		if(!tmp)
			return;
		if(!n){
			if(size>31)
			 size = 31;
			VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), i, c);
		}
		else
			VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), i&0x1f, c+(i>>5));
	}
}

void VGA_Write_Char_Row(uint8_t *ch,uint8_t r_start,uint8_t r_end,uint8_t c)
{
	uint8_t tmp;
	if (r_end>31)
		r_end = 31;
	for (int i = r_start; i <= r_end; i++)
	{
		tmp = *ch++;
		if(!tmp)
			return;
		VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), i, c);
	}
}

void VGA_Write_Char_Column(uint8_t *ch,uint8_t c_start,uint8_t c_end,uint8_t r)
{
	uint8_t tmp;
	if(c_end>11)
		c_end = 11;
	for (int i = c_start; i <= c_end; i++)
	{
		tmp = *ch++;
		if(!tmp)
			return;
		VGA_Write_Block(BLOCK_CTRL(CHAR2IMAGE(tmp),0,RGB(0,0,0),RGB(7,7,7)), r, i);
	}
}
