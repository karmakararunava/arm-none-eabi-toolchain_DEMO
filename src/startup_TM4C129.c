/*
 * startup_TM4C129.c
 *
 *  Created on: 01-Aug-2024
 *      Author: Arunava Karmakar
 *        mail: arunava.karmakar@protonmail.ch
 */

#include <stdint.h>
#include <stdbool.h>
#include "TM4C129ENCPDT.h"  // Header file for the TM4C129ENCPDT microcontroller

// Forward declaration of the default handlers.
void Reset_Handler(void);
void DefaultHandler(void);
int main(void);

// Linker script provides the stack top and data section.
extern uint32_t _stack_top;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

// Vector table.
__attribute__((section(".isr_vector"))) void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&_stack_top),  // Initial stack pointer
    Reset_Handler,                            // Reset handler
    DefaultHandler,                          // NMI handler
    DefaultHandler,                          // Hard fault handler
    DefaultHandler,                          // MPU fault handler
    DefaultHandler,                          // Bus fault handler
    DefaultHandler,                          // Usage fault handler
    0, 0, 0, 0,                              // Reserved
    DefaultHandler,                          // SVCall handler
    DefaultHandler,                          // Debug monitor handler
    0,                                        // Reserved
    DefaultHandler,                          // PendSV handler
    DefaultHandler,                          // SysTick handler

    // External interrupts
    DefaultHandler,                          // GPIO Port A
    DefaultHandler,                          // GPIO Port B
    DefaultHandler,                          // GPIO Port C
    DefaultHandler,                          // GPIO Port D
    DefaultHandler,                          // GPIO Port E
    DefaultHandler,                          // GPIO Port F
    DefaultHandler,                          // GPIO Port G
    DefaultHandler,                          // GPIO Port H
    DefaultHandler,                          // GPIO Port I
    DefaultHandler,                          // GPIO Port J
    DefaultHandler,                          // GPIO Port K
    DefaultHandler,                          // UART0
    DefaultHandler,                          // UART1
    DefaultHandler,                          // UART2
    DefaultHandler,                          // UART3
    DefaultHandler,                          // UART4
    DefaultHandler,                          // UART5
    DefaultHandler,                          // UART6
    DefaultHandler,                          // UART7
    DefaultHandler,                          // SSI0
    DefaultHandler,                          // SSI1
    DefaultHandler,                          // SSI2
    DefaultHandler,                          // SSI3
    DefaultHandler,                          // I2C0
    DefaultHandler,                          // I2C1
    DefaultHandler,                          // I2C2
    DefaultHandler,                          // I2C3
    DefaultHandler,                          // PWM0 Fault
    DefaultHandler,                          // PWM0 Generator 0
    DefaultHandler,                          // PWM0 Generator 1
    DefaultHandler,                          // PWM0 Generator 2
    DefaultHandler,                          // QEI0
    DefaultHandler,                          // QEI1
    DefaultHandler,                          // ADC0 Sequence 0
    DefaultHandler,                          // ADC0 Sequence 1
    DefaultHandler,                          // ADC0 Sequence 2
    DefaultHandler,                          // ADC0 Sequence 3
    DefaultHandler,                          // Watchdog Timer
    DefaultHandler,                          // Timer 0A
    DefaultHandler,                          // Timer 0B
    DefaultHandler,                          // Timer 1A
    DefaultHandler,                          // Timer 1B
    DefaultHandler,                          // Timer 2A
    DefaultHandler,                          // Timer 2B
    DefaultHandler,                          // Analog Comparator 0
    DefaultHandler,                          // Analog Comparator 1
    DefaultHandler,                          // Analog Comparator 2
    DefaultHandler,                          // Flash EEPROM Control
    DefaultHandler,                          // GPIO Port M
    DefaultHandler,                          // GPIO Port N
    DefaultHandler,                          // Quadrature Encoder 0
    DefaultHandler,                          // Quadrature Encoder 1
    DefaultHandler,                          // Motor Control PWM0
    DefaultHandler,                          // Motor Control PWM1
    DefaultHandler,                          // Motor Control PWM2
    DefaultHandler,                          // Motor Control PWM3
    DefaultHandler,                          // PWM1 Fault
    DefaultHandler,                          // PWM1 Generator 0
    DefaultHandler,                          // PWM1 Generator 1
    DefaultHandler,                          // PWM1 Generator 2
    DefaultHandler,                          // PWM1 Generator 3
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Timer 3A
    DefaultHandler,                          // Timer 3B
    DefaultHandler,                          // Timer 4A
    DefaultHandler,                          // Timer 4B
    DefaultHandler,                          // Timer 5A
    DefaultHandler,                          // Timer 5B
    DefaultHandler,                          // Timer 6A
    DefaultHandler,                          // Timer 6B
    DefaultHandler,                          // Timer 7A
    DefaultHandler,                          // Timer 7B
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
    DefaultHandler,                          // Reserved
};

// The reset handler.
void Reset_Handler(void)
{
    uint32_t *pSrc, *pDest;

    // Copy the data section from Flash to SRAM.
    pSrc = &_etext;
    for (pDest = &_sdata; pDest < &_edata; )
    {
        *pDest++ = *pSrc++;
    }

    // Zero fill the bss section.
    for (pDest = &_sbss; pDest < &_ebss; )
    {
        *pDest++ = 0;
    }

    // Call the application's entry point.
    main();
}

// Default handler for interrupts.
void DefaultHandler(void)
{
    while (1)
    {
        // Loop forever if an unexpected interrupt occurs.
    }
}

// Application's entry point.
extern int main(void);

