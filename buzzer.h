#ifndef BUZZER_H
#define BUZZER_H
 
#include <MKL25Z4.h>
#include <delay.h>

//funciones
void buzzer_init(void);
void buzzer_turn(int n);

void buzzer_init(void){
    SIM->SCGC5 |= 0x2000; //enable clock to port E
    PORTE->PCR[20] = 0x100;//make PTE20 as GPIO
    PTE->PDDR |= 0x100000;//Make PTE20   as an output pin
    PTE->PCOR = 0x100000;//turn off buzzer
}

void buzzer_turn(int n){
    if (n==0){  
        PTE->PCOR = 0x100000;//turn off buzzer
    }
    else if (n==1){
		PTE->PSOR = 0x100000;//turn on buzzer
    }
}

#endif
