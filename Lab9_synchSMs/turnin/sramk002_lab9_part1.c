/*	Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: none 
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * Demo Video - https://youtu.be/ESCbUYEDBzk
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

unsigned char threeLEDs;
unsigned char blinkingLED;

enum ThreeLEDsSM {SMStart, Bit0, Bit1, Bit2 } three_state;
enum BlinkingLEDSM {SMStart1, Bit_ON, Bit_OFF } one_state;
enum CombineLEDsSM {SMStart2, Comb_Bit } comb_state;

void Tick_Fct1(){
    switch (three_state){
        case SMStart:
            three_state = Bit0;
        break;
        
        case Bit0:
            three_state = Bit1;
        break;
        
        case Bit1:
            three_state = Bit2;
        break;  
        
        case Bit2:
            three_state = Bit0;
        break;    
    }
    
    switch (three_state){
        case SMStart:
        break;
        
        case Bit0:
            threeLEDs = 0x01;
        break;
        
        case Bit1:
            threeLEDs = 0x02;
        break;  
        
        case Bit2:
            threeLEDs = 0x04;
        break; 
    }
}

void Tick_Fct2(){
    switch(one_state){
        case SMStart1:
           one_state = Bit_ON;
        break;
            
        case Bit_ON:
            one_state = Bit_OFF;
        break;
            
        case Bit_OFF:
             one_state = Bit_ON;
        break;    
    }
    
    switch(one_state){
        case SMStart1:
        break;
            
        case Bit_ON:
            blinkingLED = 0x08;
        break;
            
        case Bit_OFF:
             blinkingLED = 0x00;
        break;    
    }
}

void Tick_Fct3(){
    switch (comb_state){
        case SMStart2:
            comb_state = Comb_Bit;
        break;
            
        case Comb_Bit:
             comb_state = Comb_Bit;
        break;
    }
    
    switch (comb_state){
        case SMStart2:
            break;
           
        case Comb_Bit:
            PORTB = threeLEDs | blinkingLED;
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x00;    PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(1000);
    TimerOn();
    
    threeLEDs = 0x00;
    blinkingLED = 0x00;
    
    while (1) {
        
    Tick_Fct1();
    Tick_Fct2();
    Tick_Fct3();
        
    while(!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
