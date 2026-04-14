#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "isr.h"

void irq_init(void);
void irq_register_handler(uint8_t num, isr_t handler);

#endif
