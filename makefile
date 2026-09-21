CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -ffreestanding -Wall -Wextra -nostdlib -mcpu=cortex-m4 -mthumb -O2 -pedantic -ansi -gdwarf-4
CFLAGS += -fdata-sections -Wl,--print-gc-section -std=c99
LDFLAGS = -T linker.ld -nostdlib
OBJS = isr_vector.o main.o handler.o hal.o hardware_laout.o utilites.o

all: firmware.bin
firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin
firmware.elf:$(OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
.SUFFIXES:
.SUFFIXES: .c .o
.o:.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm *.o 
