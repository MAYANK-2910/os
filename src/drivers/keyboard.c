#include "keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../libc/io.h"
#include "vga.h"

static char keyboard_buffer[256];
static int buffer_head = 0;
static int buffer_tail = 0;

static const char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=',
    '\b', '\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
    0, '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0, ' '
};

static const char shift_scancode_to_ascii[128] = {
    0, 27, '!','@','#','$','%','^','&','*','(',')','_','+',
    '\b', '\t', 'Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0, 'A','S','D','F','G','H','J','K','L',':','"','~',
    0, '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0, ' '
};

static int shift_pressed = 0;

static void keyboard_callback(registers_t *regs) {
    (void)regs;
    uint8_t scancode = inb(0x60);

    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }
    if (scancode & 0x80) return;

    char c;
    if (shift_pressed) {
        c = shift_scancode_to_ascii[scancode];
    } else {
        c = scancode_to_ascii[scancode];
    }

    if (c) {
        keyboard_buffer[buffer_head] = c;
        buffer_head = (buffer_head + 1) % 256;
    }
}

void keyboard_init(void) {
    irq_register_handler(1, keyboard_callback);
}

char keyboard_get_char(void) {
    if (buffer_tail == buffer_head) return 0;
    char c = keyboard_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % 256;
    return c;
}
