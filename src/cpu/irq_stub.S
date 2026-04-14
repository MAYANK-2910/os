.section .text

.macro IRQ_HANDLER num idt_num
.global irq\num
irq\num:
    cli
    push $0
    push $\idt_num
    jmp irq_common
.endm

IRQ_HANDLER 0  32
IRQ_HANDLER 1  33
IRQ_HANDLER 2  34
IRQ_HANDLER 3  35
IRQ_HANDLER 4  36
IRQ_HANDLER 5  37
IRQ_HANDLER 6  38
IRQ_HANDLER 7  39
IRQ_HANDLER 8  40
IRQ_HANDLER 9  41
IRQ_HANDLER 10 42
IRQ_HANDLER 11 43
IRQ_HANDLER 12 44
IRQ_HANDLER 13 45
IRQ_HANDLER 14 46
IRQ_HANDLER 15 47

.extern irq_handler

irq_common:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push %esp
    call irq_handler
    add $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret
