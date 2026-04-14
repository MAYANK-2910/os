# DogOS - Lightweight x86 Operating System

CC      = gcc
LD      = ld
CFLAGS  = -Wall -Wextra -Werror -ffreestanding -nostdlib -nostdinc \
          -fno-builtin -fno-stack-protector -fno-pic -m32 -mno-red-zone \
          -Isrc -Isrc/libc
LDFLAGS = -T linker.ld -nostdlib -m elf_i386

SRCDIR  = src
BUILDDIR = build

C_SOURCES   = $(shell find $(SRCDIR) -name '*.c')
ASM_SOURCES = $(shell find $(SRCDIR) -name '*.S')
C_OBJECTS   = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRCDIR)/%.S,$(BUILDDIR)/%.o,$(ASM_SOURCES))
OBJECTS = $(ASM_OBJECTS) $(C_OBJECTS)

TARGET = dogos.bin
ISO    = dogos.iso

.PHONY: all clean run iso

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.S | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

iso: $(TARGET)
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot/dogos.bin
	echo 'menuentry "DogOS" { multiboot /boot/dogos.bin }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso 2>/dev/null || \
		grub-mkrescue --output=$(ISO) iso

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -serial stdio

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(ISO) iso

