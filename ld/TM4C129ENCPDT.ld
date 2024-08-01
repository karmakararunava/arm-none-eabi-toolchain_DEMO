/*
 * TM4C129ENCPDT.ld
 *
 *  Created on: 01-Aug-2024
 *      Author: Arunava Krmakar
 *        mail: arunava.karmakar@protonmail.ch
 */
/* Linker script for TM4C129ENCPDT */

MEMORY
{
    /* Define memory regions */
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1024K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
    PERIPH (rw) : ORIGIN = 0x40000000, LENGTH = 512K
    SYSCTRL (rw) : ORIGIN = 0xE000E000, LENGTH = 0x00100000
}

/* Define the sections and their placement */
SECTIONS
{
    .text :
    {
        *(.isr_vector)   /* Interrupt vector table */
        *(.text*)        /* Code */
        *(.rodata*)      /* Read-only data */
        *(.gnu.linkonce.t.*) /* Linkonce sections (text) */
        _etext = .;      /* End of text section */
    } > FLASH

    .data : 
    {
        _sdata = .;      /* Start of data section */
        *(.data*)        /* Initialized data */
        *(.gnu.linkonce.d.*) /* Linkonce sections (data) */
        _edata = .;      /* End of data section */
    } > SRAM AT> FLASH

    .bss :
    {
        _sbss = .;       /* Start of bss section */
        *(.bss*)         /* Uninitialized data */
        *(.gnu.linkonce.b.*) /* Linkonce sections (bss) */
        _ebss = .;       /* End of bss section */
    } > SRAM

    .heap :
    {
        _sheap = .;      /* Start of heap */
        _eheap = .;      /* End of heap */
    } > SRAM

    .stack :
    {
        _sstack = .;    /* Start of stack */
        _estack = .;    /* End of stack */
    } > SRAM

    /* Define the end of the linker script */
    _end = .;
}

/* Define some symbols for the linker script */
__isr_vector = .;
_stack_top = _sstack;
__stack_end = _estack;
__heap_end = _eheap;
__bss_end = _ebss;

