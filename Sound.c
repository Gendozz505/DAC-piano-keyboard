// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

//	variables
const unsigned int SineWave[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,
																12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};	// 4-bit 32-element sine wave
int SineWave_size = sizeof(SineWave) / sizeof(int);
extern int key;
unsigned long i = 0;	// counter for sinewave

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
  NVIC_ST_CTRL_R = 0;           // disable SysTick during setup      
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0	
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
}

// **************Sound_period*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(double pitch){
	NVIC_ST_RELOAD_R = 1 / pitch / 0.0000000125 / (sizeof(SineWave) / sizeof(int));	// reload value according to the pitch
	NVIC_ST_CURRENT_R = 0;	// any write to current clears it
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	GPIO_PORTB_DATA_R = 0;
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	if (key != -1)
		DAC_Out(SineWave[(i++)&(0x1F)]);
}
