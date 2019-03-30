# Output filenames
TARGET = main

# The chip model
MCU = STM32F042K6T6

ifeq ($(MCU), STM32F042K6T6)
	MCU_FILES = STM32F042K6T6
	MCU_CLASS = F0
	MCU_DEF   = STM32F042x6
	IMG_START = 0x08000000
endif

# Define the linker script location
LD_SCRIPT = $(MCU_FILES).ld

ifeq ($(MCU_CLASS), F0)
	MCU_SPEC = cortex-m0
else ifeq ($(MCU_CLASS), L0)
	MCU_SPEC = cortex-m0plus
endif

# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN = /usr/local
CC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
ASFLAGS += -g

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -Os
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
CFLAGS += -std=c99
CFLAGS += -D$(MCU_DEF)
CFLAGS += -DMCU_CLASS_$(MCU_CLASS)

# Linker directives.
LSCRIPT = ./ld/$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += -Wl,--gc-sections
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

AS_SRC   =  ./boot_code/$(MCU_FILES)_core.s
AS_SRC   += ./vector_tables/$(MCU_FILES)_vt.s

C_SRC    =  $(wildcard ./src/core/*.c)
C_SRC    += $(wildcard ./src/hal/*.c)
C_SRC    += ./src/usbd_conf.c
C_SRC    += ./src/usbd_desc.c
C_SRC    += ./src/usbd_hid.c
C_SRC    += ./src/interrupts.c
C_SRC    += ./src/keys.c
C_SRC    += ./src/macros.c
C_SRC    += ./src/keyboard.c
C_SRC    += ./src/main.c

INCLUDE  =  -I./
INCLUDE  += -I./include
INCLUDE  += -I./include/core
INCLUDE  += -I./include/hal

OBJS  = $(AS_SRC:.s=.o)
OBJS += $(C_SRC:.c=.o)

.PHONY: all
all: $(TARGET).bin

%.o: %.s
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin

flash:
	st-flash erase 
	st-flash write $(TARGET).bin $(IMG_START)

reset:
	st-flash reset
