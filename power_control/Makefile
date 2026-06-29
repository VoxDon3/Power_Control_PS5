SDK_ROOT = ../ps5-payload-sdk
SDK_TARGET = $(SDK_ROOT)/target
SDK_LDSCRIPTS = $(SDK_ROOT)/ldscripts

CC = clang
CFLAGS = -target x86_64-scei-ps4-elf -I$(SDK_TARGET)/include -fPIC -ffreestanding -nostdinc -O2
LDFLAGS = -target x86_64-scei-ps4-elf -T $(SDK_LDSCRIPTS)/elf_x86_64.x -nostdlib

all: Control_power_ps5.elf

Control_power_ps5.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf
