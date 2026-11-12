#include "ch32v20x.h"


volatile uint32_t sys_ticks_ms = 0;

void SysTick_Init(void) {
    // Disable SysTick counter while configuring
    SysTick->CTLR = 0;
    
    // Clear the current counter values
    SysTick->CNT = 0;
    
    // Calculate comparison value: 96,000,000 Hz or 144,000,000 / 1000 = 96,000 OR 144,000ticks per millisecond
    // Since it counts from 0, subtract 1
    SysTick->CMP = (SystemCoreClock / 1000) - 1;
    
    // Configure Control Register (CTLR):
    // Bit 0 (STE):  Enable counter
    // Bit 1 (STIE): Enable interrupt when CNT matches CMP
    // Bit 2 (STCLK): Clock source selection (1 = HCLK, 0 = HCLK/8)
    // Bit 3 (STRE): Auto-reload enable (restarts from 0 on match)
    SysTick->CTLR = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    // Enable the SysTick vector in the core interrupt controller
    NVIC_EnableIRQ(SysTick_IRQn);
    
    // Set SysTick priority low (e.g., 0xF0) so it doesn't interrupt or block USB handling
    NVIC_SetPriority(SysTick_IRQn, 0xF0);
}

__attribute__((interrupt("WCH-Interrupt-fast"))) __attribute__((used)) 
void SysTick_Handler(void) {
    sys_ticks_ms++;
    SysTick->SR = 0; // Clear condition flag
}
