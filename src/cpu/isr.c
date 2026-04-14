#include "isr.h"
#include "idt.h"

static isr_t interrupt_handlers[256] = {0};

void isr_register_handler(uint8_t num, isr_t handler) {
    interrupt_handlers[num] = handler;
}

void isr_handler(registers_t *regs) {
    if (interrupt_handlers[regs->int_no]) {
        interrupt_handlers[regs->int_no](regs);
    }
}

extern void isr0(void);  extern void isr1(void);  extern void isr2(void);
extern void isr3(void);  extern void isr4(void);  extern void isr5(void);
extern void isr6(void);  extern void isr7(void);  extern void isr8(void);
extern void isr9(void);  extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void);
extern void isr15(void); extern void isr16(void); extern void isr17(void);
extern void isr18(void); extern void isr19(void); extern void isr20(void);
extern void isr21(void); extern void isr22(void); extern void isr23(void);
extern void isr24(void); extern void isr25(void); extern void isr26(void);
extern void isr27(void); extern void isr28(void); extern void isr29(void);
extern void isr30(void); extern void isr31(void);

void isr_init(void) {
    uint16_t code_seg = 0x08;
    uint8_t  flags     = 0x8E;

    idt_set_gate(0,  (uint32_t)isr0,  code_seg, flags);
    idt_set_gate(1,  (uint32_t)isr1,  code_seg, flags);
    idt_set_gate(2,  (uint32_t)isr2,  code_seg, flags);
    idt_set_gate(3,  (uint32_t)isr3,  code_seg, flags);
    idt_set_gate(4,  (uint32_t)isr4,  code_seg, flags);
    idt_set_gate(5,  (uint32_t)isr5,  code_seg, flags);
    idt_set_gate(6,  (uint32_t)isr6,  code_seg, flags);
    idt_set_gate(7,  (uint32_t)isr7,  code_seg, flags);
    idt_set_gate(8,  (uint32_t)isr8,  code_seg, flags);
    idt_set_gate(9,  (uint32_t)isr9,  code_seg, flags);
    idt_set_gate(10, (uint32_t)isr10, code_seg, flags);
    idt_set_gate(11, (uint32_t)isr11, code_seg, flags);
    idt_set_gate(12, (uint32_t)isr12, code_seg, flags);
    idt_set_gate(13, (uint32_t)isr13, code_seg, flags);
    idt_set_gate(14, (uint32_t)isr14, code_seg, flags);
    idt_set_gate(15, (uint32_t)isr15, code_seg, flags);
    idt_set_gate(16, (uint32_t)isr16, code_seg, flags);
    idt_set_gate(17, (uint32_t)isr17, code_seg, flags);
    idt_set_gate(18, (uint32_t)isr18, code_seg, flags);
    idt_set_gate(19, (uint32_t)isr19, code_seg, flags);
    idt_set_gate(20, (uint32_t)isr20, code_seg, flags);
    idt_set_gate(21, (uint32_t)isr21, code_seg, flags);
    idt_set_gate(22, (uint32_t)isr22, code_seg, flags);
    idt_set_gate(23, (uint32_t)isr23, code_seg, flags);
    idt_set_gate(24, (uint32_t)isr24, code_seg, flags);
    idt_set_gate(25, (uint32_t)isr25, code_seg, flags);
    idt_set_gate(26, (uint32_t)isr26, code_seg, flags);
    idt_set_gate(27, (uint32_t)isr27, code_seg, flags);
    idt_set_gate(28, (uint32_t)isr28, code_seg, flags);
    idt_set_gate(29, (uint32_t)isr29, code_seg, flags);
    idt_set_gate(30, (uint32_t)isr30, code_seg, flags);
    idt_set_gate(31, (uint32_t)isr31, code_seg, flags);
}
