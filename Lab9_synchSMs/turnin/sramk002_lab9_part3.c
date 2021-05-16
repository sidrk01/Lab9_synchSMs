  
/*	Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: none 
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Video - https://youtu.be/yH_U9vBYwv0
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

#define b3 (~PINA & 0x04) 

unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char speakerOn;

enum ThreeLEDsSM {SMStart, Bit0, Bit1, Bit2 } three_state;
enum BlinkingLEDSM {SMStart1, Bit_ON, Bit_OFF } one_state;
enum CombineLEDsSM {SMStart2, Comb_Bit } comb_state;
enum SpeakOn {SMStart3, Speak_On, Speak_Off } speaky_state;

void Tick_Fct1(){
    static unsigned int counter1;
    if (counter1 < 300){
        counter1 += 1;
    } else {
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
    counter1 = 0;
    }
}

void Tick_Fct2(){
    static unsigned int counter2;
    if (counter2 < 1000){
        counter2 += 1;
    } else {
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
        counter2 = 0;
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
            PORTB = (threeLEDs | blinkingLED) | speakerOn;
        break;
    }
}

void Tick_Fct4(){
  static unsigned int counter3;
    if (counter3 < 2){
        counter3 += 1;
    } else {
  switch (speaky_state){
    case SMStart3:
      speaky_state = Speak_Off;
     break;
     
    case Speak_On:
      speaky_state = Speak_Off;
     break;
      
    case Speak_Off:
      if (b3){
      speaky_state = Speak_On;
      } else {
       speaky_state = Speak_Off;
      }
      break;
  }
      
   switch (speaky_state){
     case Speak_On:
     speakerOn = 0x10;
     break;
       
     case Speak_Off:
     speakerOn = 0x00;
     break;
       
     default:
     break;
   }
   counter3 = 0;   
  }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;    PORTA = 0xFF;
    DDRB = 0x00;    PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(1);
    TimerOn();
    
    threeLEDs = 0x00;
    blinkingLED = 0x00;
    speakerOn = 0x00;
    
  three_state = SMStart;
  one_state = SMStart1;
  comb_state = SMStart2;
  speaky_state = SMStart3;
  
    while (1) {
        
    Tick_Fct1();
    Tick_Fct2();
    Tick_Fct3();
    Tick_Fct4();  
        
    while(!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
