#ifndef LED_H
#define LED_H
 
#include <MKL25Z4.h>
 
void LED_init(void);
void LED_turnON(int n);
void LED_turnOFF(int n);

void LED_turnON(int n){
    PTB->PSOR = 0x80000;//turn OFF green LED
    PTB->PSOR = 0x20000000;//turn OFF red LED
    PTD->PSOR = 0x02;//turn OFF blue LED
    if (n==1){
        PTB->PCOR = 0x20000000;//turn ON red LED
    }
    else if (n==2){
        PTD->PCOR = 0x02;//turn ON blue LED
    }
    else if (n==3){
        PTB->PCOR = 0x80000;//turn ON green LED
    }
}
void LED_turnOFF(int n){
    if (n==1){
        PTB->PSOR = 0x20000000;//turn OFF red LED
    }
    else if (n==2){
        PTD->PSOR = 0x02;//turn OFF blue LED
    }
    else if (n==3){
        PTB->PSOR = 0x80000;//turn OFF green LED
    }
}
void LED_init(void){
    SIM->SCGC5 |= 0x2000; //enable clock to port E
    PORTE->PCR[29] = 0X100;//make PTE29 as GPIO
    PTE->PDDR |= 0x20000000;//make PTE29 as an output pin
    PTE->PSOR = 0x20000000;//turn off led


    SIM->SCGC5 |= 0x400; /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
    PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
    PTB->PSOR |= 0x40000; /* turn off  LED */
    PORTB->PCR[10] = 0x100; /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02; /* make PTD1 as output pin */
    PTD->PSOR |= 0x02; /* turn off blue LED */
}
 
#endif
