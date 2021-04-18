// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "DAC.h"
#include "TExaS.h"

// variables
int key = -1;
int previous_key;

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);

int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
	// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
  while(1){                
	//	input from keys to select tone
		key = Piano_In(); // read the switches
		if (key != previous_key){
			delay(50); // debounce
			previous_key = key;
			switch(key){
				case 0:
					Sound_Tone(523.251);	// C note has frequency 523.251 Hz
					break;
				case 1:
					Sound_Tone(587.330);	// D note has frequency 587.330 Hz
					break;
				case 2:
					Sound_Tone(659.255);	// E note has frequency 659.255 Hz
					break;
				case 3:
					Sound_Tone(783.991);	// G note has frequency 783.991 Hz
					break;
				default: Sound_Off();	// turn off the sound
			}
		}
  }
            
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


