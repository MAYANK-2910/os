#include "irq.h"
#include "idt.h"
#include "../libc/io.h"

static isr_t irq_handlers[16] = {0};

void irq_register_handler(uint8_t num, isr_t handler) {
    irq_handlers[num] = handler;
}

void irq_handler(registers_t *regs) {
    if (irq_handlers[regs->int_no - 32]) {
        irq_handlers[regs->int_no - 32](regs);
    }

    if (regs->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}

extern void irq0(void);  extern void irq1(void);  extern void irq2(void);
extern void irq3(void);  extern void irq4(void);  extern void irq5(void);
extern void irq6(void);  extern void irq7(void);
extern void irq8(void);  extern void irq9(void);  extern void irq10(void);
extern void irq11(void); extern void irq12(void); extern void irq13(void);
extern void irq14(void); extern void irq15(void);

static void set_irq_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    extern void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
    idt_set_gate(num, base, selector, flags);
}

void irq_init(void) {
    uint16_t code_seg = 0x08;
    uint8_t  flags     = 0x8E;

    set_irq_gate(32,  (uint32_t)irq0,  code_seg, flags);
    set_irq_gate(33,  (uint32_t)irq1,  code_seg, flags);
    set_irq_gate(34,  (uint32_t)irq2,  code_seg, flags);
    set_irq_gate(35,  (uint32_t)irq3,  code_seg, flags);
    set_irq_gate(36,  (uint32_t)irq4,  code_seg, flags);
    set_irq_gate(37,  (uint32_t)irq5,  code_seg, flags);
    set_irq_gate(38,  (uint32_t)irq6,  code_seg, flags);
    set_irq_gate(39,  (uint32_t)irq7,  code_seg, flags);
    set_irq_gate(40,  (uint32_t)irq8,  code_seg, flags);
    set_irq_gate(41,  (uint32_t)irq9,  code_seg, flags);
    set_irq_gate(42,  (uint32_t)irq10, code_seg, flags);
    set_irq_gate(43,  (uint32_t)irq11, code_seg, flags);
    set_irq_gate(44,  (uint32_t)irq12, code_seg, flags);
    set_irq_gate(45,  (uint32_t)irq13, code_seg, flags);
    set_irq_gate(46,  (uint32_t)irq14, code_seg, flags);
    set_irq_gate(47,  (uint32_t)irq15, code_seg, flags);
}
