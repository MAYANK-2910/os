#include "vga.h"
#include "../libc/io.h"

static volatile uint16_t *const vga_buffer = (volatile uint16_t *const)VGA_MEMORY;
static int cursor_x = 0;
static int cursor_y = 0;
static uint8_t current_color;

static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

static void update_hw_cursor(void) {
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, (uint8_t)(pos >> 8));
    outb(0x3D4, 15);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
}

static void scroll(void) {
    if (cursor_y >= VGA_HEIGHT) {
        for (int y = 0; y < VGA_HEIGHT - 1; y++) {
            for (int x = 0; x < VGA_WIDTH; x++) {
                int dst = y * VGA_WIDTH + x;
                int src = (y + 1) * VGA_WIDTH + x;
                vga_buffer[dst] = vga_buffer[src];
            }
        }
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', current_color);
        }
        cursor_y = VGA_HEIGHT - 1;
    }
}

void vga_init(void) {
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_clear();
}

void vga_set_color(vga_color fg, vga_color bg) {
    current_color = (uint8_t)fg | ((uint8_t)bg << 4);
}

void vga_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\t') {
        cursor_x = (cursor_x + 8) & ~7;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    } else {
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = vga_entry(c, current_color);
        cursor_x++;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    scroll();
    update_hw_cursor();
}

void vga_write(const char *str) {
    while (*str) {
        vga_putchar(*str++);
    }
}

void vga_clear(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_entry(' ', current_color);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
    update_hw_cursor();
}

void vga_backspace(void) {
    if (cursor_x > 0) {
        cursor_x--;
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = VGA_WIDTH - 1;
    }
    vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = vga_entry(' ', current_color);
    update_hw_cursor();
}

void vga_set_cursor(int x, int y) {
    cursor_x = x;
    cursor_y = y;
    update_hw_cursor();
}

void vga_get_cursor(int *x, int *y) {
    *x = cursor_x;
    *y = cursor_y;
}
