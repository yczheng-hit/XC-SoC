# 
# @Author: yczheng-hit
# @Date: 2022-04-12 10:56:17
# @LastEditTime: 2022-04-14 10:28:50
# @LastEditors: yczheng-hit
# @Description: XC-SoC Software GCC Version Makefile
# 

# Endian Option
COMPILE_BIGEND ?= 0

# Configuration
USER_DEFINE    = -DCORTEX_M0

DEPS_LIST       = makefile

TOOL_CHAIN      = gcc

ifeq ($(TOOL_CHAIN),gcc)
  CPU_TYPE        = -mcpu=cortex-m0
endif

STARTUP_FILE = startup_CMSDK_CM0
SYSTEM_FILE  = system_CMSDK_CM0

# gcc options

GNG_CC      = arm-none-eabi-gcc
GNU_OBJDUMP = arm-none-eabi-objdump
GNU_OBJCOPY = arm-none-eabi-objcopy

LINKER_SCRIPT_PATH = ./scripts
LINKER_SCRIPT = $(LINKER_SCRIPT_PATH)/cmsdk_cm0.ld

GNU_CC_FLAGS = -g -O3 -mthumb $(CPU_TYPE)

ifeq ($(COMPILE_BIGEND),1)
 # Big Endian
 GNU_CC_FLAGS   += -mbig-endian
endif

all: all_$(TOOL_CHAIN)
# 
all_gcc: startup_CMSDK_CM0.s ../uart_api.c ../main.c
	$(GNG_CC) $(GNU_CC_FLAGS) $^\
		-I ../Include -I ..\
		-L $(LINKER_SCRIPT_PATH) \
		-D__STACK_SIZE=0x200 -D__HEAP_SIZE=0x1000 \
		$(USER_DEFINE) -T $(LINKER_SCRIPT) -o main.elf
	# Generate disassembly code
	$(GNU_OBJDUMP) -S main.elf > main.lst
	# Generate binary file
	$(GNU_OBJCOPY) -S main.elf -O binary main.bin
	# Generate hex file
	$(GNU_OBJCOPY) -S main.elf -O verilog main.hex
	# Generate image hex file
	python3 ./generate.py main.hex image.hex
	cp ./image.hex ../../simulation/image.hex

# Clean
clean :
	@rm -rf *.o
	@rm -rf *.hex
	@rm -rf *.lst
	@rm -rf *.ELF
	@rm -rf *.bin
	@rm -rf *.crf
	@rm -rf *.plg
	@rm -rf *.tra
	@rm -rf *.htm
	@rm -rf *.map
	@rm -rf *.dep
	@rm -rf *.d
	@rm -rf *.lnp
	@rm -rf *.bak
	@rm -rf *.lst
	@rm -rf *.axf
	@rm -rf *.sct
	@rm -rf *.__i
	@rm -rf *._ia
