ENTRY(_start)

SECTIONS {
    . = 0xC0000000 + SIZEOF_HEADERS;

    .text ALIGN(4K) : {
        *(.multiboot)
        *(.text)
        *(.rodata)
    }

    .data ALIGN(4K) : {
        *(.data)
    }

    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note*)
    }
}
