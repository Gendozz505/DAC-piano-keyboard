// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"

// variables
extern int sound_state;
	
// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
  unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x00000010; // activate port E
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTE_AMSEL_R &= ~0x0F;      // no analog 
  GPIO_PORTE_PCTL_R &= ~0x0000FFFF; // regular function
	GPIO_PORTE_DIR_R &= ~0x0F;    // make PE0-PE3 input
  GPIO_PORTE_AFSEL_R &= ~0x0F;  // disable alt funct on PE0-PE3
  GPIO_PORTE_DEN_R |= 0x0F;     // enable digital I/O on PE0-PE3
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 1 pressed (C note), 0x02 is key 2 pressed (D note),
// 0x04 is key 3 pressed (E note), 0x08 is key 4 pressed (G note)
// 0x00 is all keys are released
unsigned long Piano_In(void){
	switch(GPIO_PORTE_DATA_R){
		case 0x01:
			return 0;	// C note has frequency 523.251 Hz Hz
		case 0x02:
			return 1;	// D note has frequency 587.330 Hz
		case 0x04:
			return 2;	// E note has frequency 659.255 Hz
		case 0x08:
			return 3;	// G note has frequency 784.991 Hz
		default: return -1;	// turn off the sound
		}
}
