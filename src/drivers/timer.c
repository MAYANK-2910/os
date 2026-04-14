#include "timer.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../libc/io.h"

static uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    (void)regs;
    tick++;
}

void timer_init(uint32_t freq) {
    irq_register_handler(0, timer_callback);

    uint32_t divisor = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

uint32_t timer_get_ticks(void) {
    return tick;
}
