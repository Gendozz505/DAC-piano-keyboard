// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"


// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
  unsigned long volatile Init_delay;
	SYSCTL_RCGC2_R |= 0x00000002; // activate port B
  Init_delay = SYSCTL_RCGC2_R;
  GPIO_PORTB_AMSEL_R &= ~0x0F;      // no analog 
  GPIO_PORTB_PCTL_R &= ~0x0000FFFF; // regular function
	GPIO_PORTB_DIR_R |= 0x0F;    // make PB0-PB3 output
  GPIO_PORTB_DR8R_R |= 0x0F;    // can drive up to 8mA out
  GPIO_PORTB_AFSEL_R &= ~0x0F;  // disable alt funct on PB0-PB3
  GPIO_PORTB_DEN_R |= 0x0F;     // enable digital I/O on PB0-PB3
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long amp){
	GPIO_PORTB_DATA_R = amp; //	output DAC value
}

