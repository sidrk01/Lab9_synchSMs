#ifndef _TIMER_H_
#define _TIMER_H_

#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; //TimerISR () sets this to 1. C Programmer should clear to 0.

//Internal variables for mapping AVR's ISR to out cleaner TimerISR model 
unsigned long _avr_timer_M = 1; //Start count from here, down to 0. Default 1 ms
unsigned long _avr_timer_cntcurr = 0; //Current internal count of 1ms ticks

void TimerOn() {
   // AVR timer/counter controller register TCCR1
       TCCR1B = 0x0B; //bit3 = 0: CTC mode (clear timer on compare )
       	 	  //bit2bit1bit0=011: pre-scaler /64 
       	 	  	 	  //00001011: 0x0B
       	 	  	 	  	 	  //so, 8MHx clock or 8,000,000 /64 = 125,000 ticks/s
       	 	  	 	  	 	  	 	  //Thus, TCNT1 register will count at 125,000 ticks/s
   

//AVR output compare register OCR1A
   OCR1A = 125;   //Timer interrupt will be generated when TCNT1==OCR1A
//   		  //We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
//   		  		  //So when TCNT1 register equals 125,
//   		  		  		  //1 ms has passed. Thus, we compare to 125.
//   		  		  		     //AVR timer interrupt mask register
   TIMSK1 = 0x02; //bit1: OCIElA -- enables compare match interrupt    	 	  	 	  	 	  	 	     
//Intialize avr counter 
   TCNT1 = 0;
//
      _avr_timer_cntcurr = _avr_timer_M;
//         //TimerISR will be called every _avr_timer_cntcurr milliseconds

 //Enable global interrupts
   SREG |= 0x80; //0x80: 100000 
   }
 
// The "enable goal interrupts" is SREG |= 0x80, not SREG |- 0x80

 void TimerOff() {
 	TCCR1B = 0x00; //bit3bit1bit0=000: timer off
 	 }

 	 void TimerISR() {
 	 	TimerFlag = 1;
 	 	}

ISR(TIMER1_COMPA_vect) {
	//CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
		_avr_timer_cntcurr--; //Count down to 0 rather than up to TOP
			if (_avr_timer_cntcurr == 0){
					TimerISR(); //Call the ISR that the user uses
					_avr_timer_cntcurr = _avr_timer_M;
				}
}

//Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
		_avr_timer_cntcurr = _avr_timer_M;	
		}

#endif //_TIMER_H_
