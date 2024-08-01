#
# main.c
#
#  Created on: 02-Aug-2024
#      Author: Arunava Karmakar
#        mail: arunava.karmakar@protonmail.ch
#


# PROJECT: name of the output file
PROJECT = arm-none-eabi-toolchain_DEMO

# MCU
MCU = TM4C129ENCPDT

# DEV: TM4C129ENCPDT when connected to your system, usually it's /dev/ttyACM0
#      can be checked with - [ls /dev/tty*]
DEV = /dev/ttyACM0


# SRCS: all source files from src directory
C_SRCS = $(wildcard src/*.c)
ASM_SRCS = $(wildcard src/*.s)
SRCS = $(C_SRCS) $(ASM_SRCS)

OBJ = obj/
# OBJ_ALL: list of object files
OBJ_ALL = $(C_OBJ) $(AS_OBJS)
C_OBJ = $(addprefix $(OBJ),$(notdir $(C_SRCS:.c=.o)))
AS_OBJ = $(addprefix $(OBJ),$(notdir $(ASM_SRCS:.s=.o)))

# header files
INC = -Iinc -I/opt/arm/CMSIS/Core/Include -I/opt/arm/ti/TM4C_DFP/Device/Include/TM4C129


# LD_SCRIPT: linker script
LD_SCRIPT = ld/$(MCU).ld


# utility variables
CC = arm-none-eabi-gcc              # compiler
AS = arm-none-eabi-as               # assembler
LD = arm-none-eabi-ld               # linker
OBJCOPY = arm-none-eabi-objcopy     # final executable builder
RM      = rm -rf
MKDIR   = @mkdir -p $(@D)           # creates folders if not present


# gcc flags
CFLAGS = -ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 
CFLAGS += -mfloat-abi=softfp -Os -MD -std=c99 -c    

# assembler Flags
ASFLAGS = -ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16

# linker flags
LDFLAGS = -T $(LD_SCRIPT) -e Reset_Handler 



# rules to build bin
all: bin/$(PROJECT).bin

# compile obj files from c source files
$(OBJ)%.o: src/%.c
	$(MKDIR)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)
	
# get obj files from assembly code
$(AS_OBJ)%.o: src/%.s
	$(MKDIR)
	$(AS) -o $@ $^ $(CFLAGS)

# get elf file from the obj files
bin/$(PROJECT).elf: $(OBJ_ALL)
	$(MKDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

# get the binary ready for flashing from elf file
bin/$(PROJECT).bin: bin/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@


# remove object and bin files
clean:
	-$(RM) obj
	-$(RM) bin

.PHONY: all clean
