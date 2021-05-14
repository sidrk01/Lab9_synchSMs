/*	Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: none 
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
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

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x00;    PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(1000);
    TimerOn();
    
    while (1) {
    
    while(!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
