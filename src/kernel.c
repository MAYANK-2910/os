#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "shell/shell.h"

void kernel_main(void) {
    vga_init();

    vga_set_color(VGA_WHITE, VGA_BLUE);
    vga_write("  ___  ____  ___  ____   ____\n");
    vga_write(" / _ \\|  _ \\/ _ \\|  _ \\ / ___|\n");
    vga_write("| | | | | | | | | | |_) | |\n");
    vga_write("| |_| | |_| | |_| |  _ <| |___\n");
    vga_write(" \\___/|____/ \\___/|_| \\_\\\\____|\n");
    vga_write("\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_write("Initializing GDT...\n");
    gdt_init();
    vga_write("Initializing IDT...\n");
    idt_init();
    vga_write("Initializing Timer (100 Hz)...\n");
    timer_init(100);
    vga_write("Initializing Keyboard...\n");
    keyboard_init();
    vga_write("Enabling interrupts...\n");
    asm volatile("sti");
    vga_write("All systems go!\n\n");

    shell_run();
}
