# تحديد مسار الـ SDK الرئيسي
SDK_ROOT = ..
# تحديد المجلدات الفرعية للمكتبات التي تم بناؤها
SDK_INCLUDE = $(SDK_ROOT)/include
SDK_LIBS = $(SDK_ROOT)/libc
SDK_STUBS = $(SDK_ROOT)/sce_stubs

# إعدادات المترجم المعتمدة على SDK الحديث الخاص بك
CC = clang
# استخدام Target يتوافق مع SIE PS5
CFLAGS = -target x86_64-sie-ps5 -I$(SDK_INCLUDE) -fPIC -ffreestanding -O1
LDFLAGS = -target x86_64-sie-ps5 -L$(SDK_LIBS) -L$(SDK_STUBS) -nostdlib

all: Control_power_ps5.elf

Control_power_ps5.elf: main.o
	# الربط مع المكتبات المطلوبة (libc و sce_stubs)
	$(CC) $(LDFLAGS) -o $@ $^ -lc -lsce_stubs

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf
