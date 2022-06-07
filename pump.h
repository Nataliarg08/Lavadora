/*
Para funcionamiento correcto utilizar relevador
también util para motor
*/
#ifndef PUMP_H
#define PUMP_H

#include <MKL25Z4.h>

void pump_init(void);
void pump_turn(int m, int n);

void pump_init(void){
    SIM->SCGC5 |= 0x2000; //enable clock to port E
    PORTE->PCR[2] = 0x100;//make PTE2 as GPIO
    PORTE->PCR[3] = 0x100;//make PTE3 as GPIO
    PORTE->PCR[4] = 0x100;//make PTE4 as GPIO
    PORTE->PCR[5] = 0x100;//make PTE5 as GPIO
    PTE->PDDR |= 0x04;//Make PTE2 as an output pin
    PTE->PDDR |= 0x08;//Make PTE3 as an output pin
    PTE->PDDR |= 0x10;//Make PTE4 as an output pin
    PTE->PDDR |= 0x20;//Make PTE5 as an output pin
    PTE->PSOR = 0x04;//turn off pump
    PTE->PSOR = 0x08;//turn off pump
    PTE->PSOR = 0x10;//turn off pump
    PTE->PSOR = 0x20;//turn off pump
}

void pump_turn(int m, int n){
    if (m==0){
        if (n==0){
            PTE->PSOR = 0x04;//turn OFF PUMP
        }
        else if(n==1){
            PTE->PCOR = 0x04;//turn ON PUMP
        }
    }
    else if (m==1){
        if (n==0){
            PTE->PSOR = 0x08;//turn OFF PUMP
        }
        else if(n==1){
            PTE->PCOR = 0x08;//turn ON PUMP
        }
    }
    else if (m==2){
        if (n==0){
            PTE->PSOR = 0x10;//turn OFF PUMP
        }
        else if(n==1){
            PTE->PCOR = 0x10;//turn ON PUMP
        }
    }
    else if (m==3){
        if (n==0){
            PTE->PSOR = 0x20;//turn OFF PUMP
        }
        else if(n==1){
            PTE->PCOR = 0x20;//turn ON PUMP
        }
    }
}

#endif