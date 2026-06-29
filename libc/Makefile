DESTDIR ?= /opt/ps5-payload-sdk

LLVM_CONFIG_CANDIDATES := llvm-config-21 \
                          llvm-config-20 llvm-config-19 llvm-config-18 \
                          llvm-config-17 llvm-config-16 llvm-config-15 \
                          llvm-config
LLVM_CONFIG_CANDIDATES := $(foreach LCC,$(LLVM_CONFIG_CANDIDATES), \
                          $(if $(shell command -v $(LCC) 2>/dev/null), $(LCC)))

LLVM_CONFIG ?= $(firstword $(LLVM_CONFIG_CANDIDATES))
ifndef LLVM_CONFIG
    $(error Unable to find llvm-config)
endif

LLVM_BINDIR := $(shell $(LLVM_CONFIG) --bindir)
CC ?= $(LLVM_BINDIR)/clang
AR ?= $(LLVM_BINDIR)/llvm-ar

CFLAGS := -target x86_64-sie-ps5 -fPIC  -fno-plt -fno-stack-protector
CFLAGS += -nobuiltininc -isystem ../include/freebsd
CFLAGS += -fvisibility-nodllstorageclass=default
CFLAGS += -O1

ASFLAGS := $(CFLAGS)

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o) _setjmp.o

ARCHIVE := libc.a

.PHONY: all clean install

all: $(ARCHIVE)

$(ARCHIVE): $(OBJS)
	$(AR) -rsc $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(ASFLAGS) -o $@ $<

clean:
	rm -f *.a *.o

install: $(ARCHIVE)
	install -d $(DESTDIR)/target/lib
	install $^ $(DESTDIR)/target/lib

