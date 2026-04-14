#include "shell.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../libc/string.h"
#include "../libc/io.h"

#define INPUT_MAX 256

static char input_buf[INPUT_MAX];
static int  input_pos = 0;

static void print_prompt(void) {
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_write("dogos> ");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
}

static void cmd_help(void) {
    vga_write("Available commands:\n");
    vga_write("  help     - show this help\n");
    vga_write("  clear    - clear screen\n");
    vga_write("  uptime   - show tick count\n");
    vga_write("  echo      - echo arguments\n");
    vga_write("  about     - about DogOS\n");
    vga_write("  reboot    - reboot system\n");
}

static void cmd_clear(void) {
    vga_clear();
}

static void cmd_uptime(void) {
    vga_write("Uptime: ");
    char buf[12];
    int_to_str(timer_get_ticks(), buf);
    vga_write(buf);
    vga_write(" ticks\n");
}

static void cmd_echo(const char *args) {
    vga_write(args);
    vga_putchar('\n');
}

static void cmd_about(void) {
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_write("DogOS v0.1 - A lightweight x86 operating system\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
}

static void cmd_reboot(void) {
    vga_write("Rebooting...\n");
    uint8_t good = 0x02;
    while (good & 0x02) good = inb(0x64);
    outb(0x64, 0xFE);
    asm volatile("hlt");
}

static void process_command(void) {
    input_buf[input_pos] = '\0';

    if (input_pos == 0) return;

    if (strcmp(input_buf, "help") == 0) {
        cmd_help();
    } else if (strcmp(input_buf, "clear") == 0) {
        cmd_clear();
    } else if (strcmp(input_buf, "uptime") == 0) {
        cmd_uptime();
    } else if (strncmp(input_buf, "echo ", 5) == 0) {
        cmd_echo(input_buf + 5);
    } else if (strcmp(input_buf, "about") == 0) {
        cmd_about();
    } else if (strcmp(input_buf, "reboot") == 0) {
        cmd_reboot();
    } else {
        vga_write("Unknown command: ");
        vga_write(input_buf);
        vga_putchar('\n');
    }
}

void shell_run(void) {
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_write("DogOS v0.1 - Welcome!\n");
    vga_write("Type 'help' for available commands.\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    print_prompt();

    while (1) {
        char c = keyboard_get_char();
        if (!c) {
            asm volatile("hlt");
            continue;
        }

        if (c == '\n') {
            vga_putchar('\n');
            process_command();
            input_pos = 0;
            print_prompt();
        } else if (c == '\b') {
            if (input_pos > 0) {
                input_pos--;
                vga_backspace();
            }
        } else {
            if (input_pos < INPUT_MAX - 1) {
                input_buf[input_pos++] = c;
                vga_putchar(c);
            }
        }
    }
}
