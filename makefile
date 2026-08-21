CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -ffreestanding -Wall -Wextra -nostdlib -mcpu=cortex-m4 -mthumb -O0 -pedantic -ansi -gdwarf-4
LDFLAGS = -T linker.ld -nostdlib
OBJS = isr_vector.o main.o handler.o hal.o hardware_laout.o led_clock.o utilites.o

all: firmware.bin
firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin
firmware.elf:$(OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
.SUFFIXES:
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS): basic_mapping.h symbols.h utilites.h

clean:
	rm -f $(OBJS) firmware.elf firmware.bin

