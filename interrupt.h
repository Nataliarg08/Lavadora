#ifndef INTERRUPT_H
#define INTERRUPT_H
 
#include <MKL25Z4.h>   

void interrupt(void){ 
   __disable_irq(); /* disable all IRQs */
    SIM->SCGC5 |= 0x200; /* enable clock to Port A */
    /* configure PTA1 for interrupt */
    PORTA->PCR[1] |= 0x00100; /* make it GPIO */
    PORTA->PCR[1] |= 0x00003; /* enable pull-up */
    PTA->PDDR &= ~0x0002; /* make pin input */
    PORTA->PCR[1] &= ~0xF0000; /* clear interrupt selection */
    PORTA->PCR[1] |= 0xA0000; /* enable falling edge INT */
 
    NVIC->ISER[0] |= 0x40000000; /* enable INT30 (bit 30 of ISER[0]) */
    __enable_irq(); /* global enable IRQs */
    
}

#endif