# DogOS - Lightweight x86 Operating System

A minimal, Linux-like x86 operating system built from scratch.

## Features

- **Multiboot-compliant** bootloader entry
- **GDT** (Global Descriptor Table) for x86 protected mode
- **IDT** (Interrupt Descriptor Table) with full ISR/IRQ support
- **VGA text mode** console with color support
- **Keyboard** driver (US QWERTY layout with shift)
- **PIT** timer at 100 Hz
- **Interactive shell** with built-in commands

## Shell Commands

| Command  | Description           |
|----------|-----------------------|
| `help`   | Show available commands |
| `clear`  | Clear the screen      |
| `uptime` | Show system tick count |
| `echo`   | Echo arguments        |
| `about`  | About DogOS           |
| `reboot` | Reboot the system     |

## Prerequisites

- `i686-elf-gcc` cross-compiler
- `nasm` assembler
- `qemu-system-i386` for testing
- `grub-mkrescue` and `xorriso` for ISO creation

## Build

```bash
make          # Build the kernel binary
make run      # Run in QEMU
make iso      # Create bootable ISO
make clean    # Clean build artifacts
```

## Project Structure

```
src/
├── boot/boot.asm        # Multiboot entry + stack setup
├── cpu/
│   ├── gdt.c/h          # Global Descriptor Table
│   ├── idt.c/h          # Interrupt Descriptor Table
│   ├── isr.c/h          # Interrupt Service Routines
│   ├── irq.c/h          # Hardware IRQ handlers
│   └── *.asm            # Assembly stubs for GDT/IDT/ISR/IRQ
├── drivers/
│   ├── vga.c/h          # VGA text mode console
│   ├── keyboard.c/h     # PS/2 keyboard driver
│   └── timer.c/h        # PIT timer driver
├── libc/
│   ├── string.c/h       # Minimal string utilities
│   ├── stdint.h          # Fixed-width integer types
│   └── io.h              # Port I/O helpers
├── shell/shell.c/h      # Interactive command shell
└── kernel.c             # Kernel entry point
```
