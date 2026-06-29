# إخبار المترجم أن المجلد 'include' يقع في المجلد الأعلى
CFLAGS = -target x86_64-sie-ps5 -I../include -fPIC -ffreestanding -O1
LDFLAGS = -target x86_64-sie-ps5 -nostdlib

all: Control_power_ps5.elf

Control_power_ps5.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf
