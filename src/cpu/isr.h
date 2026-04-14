#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);

void isr_init(void);
void isr_register_handler(uint8_t num, isr_t handler);

#endif
