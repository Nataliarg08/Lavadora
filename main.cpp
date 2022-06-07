#include <MKL25Z4.h>
#include <led.h>
#include <LCD.h>
#include <KEYPAD.h>
#include <delay.h>
#include <motor.h>
#include <pump.h>
#include <buzzer.h>
#include <interrupt.h>

/* 
Main, funciones principales de la lavadora. 
*/

void sensing(void);
void washing(int n);
void drained(void);
void final_spin(void);
void finish(void);
int contador(void);

int main(void){
    //dar de alta función interruption
    LCD_init();
    LED_init();
    keypad_init();
    pump_init();
    motor_init();
    buzzer_init();
    //interrupt();
    unsigned char key;
    bool key2=false;
    int time=0;

    
    LCD_command(1);//clear the LCD
    LCD_command(0x80);//set the cursor
    LCD_print("SET THE DESIRED\nWASHING CYCLE");
    delayMs(5000);
    LCD_command(1);//clear the LCD
    LCD_command(0x80);//set the cursor
    LCD_print("1:C1 2:C2 3:S\n");

    while (!key2){
        key = keypad_getkey();
        if (key==13 || key==15 ){key2=true;}
        else if (key>0 && key<13 && key%4!=0){
            time*=10;
            time+=(key-key/4);
            LCD_data((key-key/4)+48);
        }
        else if (key==14){
            time*=10;
            LCD_data(48);
        }
        delayMs(300);
    }
    sensing();
    washing(time);  
    final_spin();
    finish();
}

void sensing(void){
    //activar sensor
    LCD_command(1);//clear the LCD
    LCD_command(0x80);//set the cursor
    LCD_print("SENSING");
}
void washing(int n){
    //activar bombas de suministro & dual-motor
    LCD_command(1);//clear the LCD
    LCD_command(0x80);//set the cursor
    LCD_print("WASHING");
    if (n==1){
        for (int i=0;i<3;i++){
            pump_turn(i,1);
            delayMs(5000);
            pump_turn(i,0);
            delayMs(3000);
            motor_turn(1);
            delayMs(4000);
            motor_turn(0);
            delayMs(3000);
            drained();
        }
    }
    else if (n==2){
        for (int i=0;i<2;i++){
            pump_turn(i+1,1);
            delayMs(5000);
            pump_turn(i+1,0);
            delayMs(3000);
            motor_turn(1);
            delayMs(4000);
            motor_turn(0);
            delayMs(3000);
            drained();
        }
    }
}

void drained(void){
    //bomba de salida
    pump_turn(3,1);
    delayMs(7000);
    pump_turn(3,0);
}

void final_spin(void){
    //prender motor
    motor_turn(1);
    delayMs(7000);
    motor_turn(0);
}

void finish(){
    //activar buzzer, mensaje de despedida
    LCD_command(1);//clear the LCD
    LCD_command(0x80);//set the cursor
    LCD_print("FINISH  :)\nHAVE A NICE DAY");
    for (int i=0;i<3;i++){//toggle led & buzzer
        LED_turnON(1);//RED LED
        buzzer_turn(1);//buzzer turn ON
        delayMs(1500);
        LED_turnOFF(1);//RED LED
        buzzer_turn(0); //buzzer turn OFF
        delayMs(1500);
    }

}

extern "C" void PORTA_IRQHandler(void) {
    unsigned char key3;
    int i;
    LCD_command(1);//clears display
    LCD_command(0x80);//FIST LINE
    LCD_print("PAUSE");
    while(1){
        key3 = keypad_getkey();
        if(key3==13 || key3==15){
            LCD_command(1);
            break;
        }
    }
    PORTA->ISFR = 0x00000006; /* clear interrupt flag */ 
}

