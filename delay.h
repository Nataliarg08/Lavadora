#ifndef DELAY_H
#define DELAY_H
 
#include <MKL25Z4.h>
 
void delayMs(int n);
 

//Delay Ms
void delayMs(int n) {
    int i;
    SysTick->LOAD = 41940 - 1;
    SysTick->CTRL = 0x5; // Enable the timer and choose sysclk as the clock source 
 
    for(i = 0; i < n; i++) {
    while((SysTick->CTRL & 0x10000) == 0)
    // wait until the COUTN flag is set 
    { }
    }
    SysTick->CTRL = 0; 
    // Stop the timer (Enable = 0) 
}
/*
//TPM
void delayMs(int n){
    int i;
    for (i = 0; i<n;i++){
        while((TPM0->SC & 0x80) == 0) { } // wait until the TOF is set
        TPM0->SC |= 0x80; // clear TOF
    }
}*/
 
#endif
