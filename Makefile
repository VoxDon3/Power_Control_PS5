SDK_ROOT = .
SDK_LDSCRIPTS = $(SDK_ROOT)/ldscripts
SDK_INCLUDE = $(SDK_ROOT)/include

CC = clang

CFLAGS = -target x86_64-scei-ps4-elf -I$(SDK_INCLUDE) -fPIC -ffreestanding -nostdinc -O2
LDFLAGS = -target x86_64-scei-ps4-elf -T $(SDK_LDSCRIPTS)/elf_x86_64.x -nostdlib

all: Control_power_ps5.elf

Control_power_ps5.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf

