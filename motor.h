#ifndef MOTOR_H
#define MOTOR_H

#include <MKL25Z4.h>

void motor_init(void);
void motor_turn(int n);

void motor_init(void){
    SIM->SCGC5 |= 0x2000; //enable clock to port E
    PORTE->PCR[21] = 0X100;//make PTE21 as GPIO
    PTE->PDDR |= 0x200000;//make PTE21 as an output pin
    PTE->PSOR = 0x200000;//turn off motor
}

void motor_turn(int n){
    if (n==0){
        PTE->PSOR = 0x200000;//turn OFF PUMP
    }
    else if(n==1){
        PTE->PCOR = 0x200000;//turn ON PUMP
    }
}
#endif