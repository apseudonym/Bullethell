/* Controller.c
This sets up the Controller inputs, as well as providing a main loop to demonstrate the module
Controller includes the PSP slide pot, which is read through ADC
It is calibrated to provide directional input in terms of positive or negative values, with a deadzone when the analog stick isn't touched
*/

#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "adc.h"
#include "controller.h"
#include "systickints.h"
#include "Output.h"

unsigned long ADCValues[2];


//CTLRInit exists just so I didn't have to include adc.h in the main file
void CTLRInit(void){
	InitAdcPorts();
}

/* Reads Controller raw input, and calibrates. Ignoring the dead
  zone of the PSP slide pad, returns either positive or negative 1.
  The button being pressed returns a 1, otherwise its 0 */
void Ctlread(long* X, long* Y, long* button){
		if (ADCValues[0] > 675) *X = 1;
		else if (ADCValues[0] < 545) *X= -1;
		else *X = 0;
		if (ADCValues[1] > 495) *Y = 1;
		else if (ADCValues[1] < 420) *Y = -1;
		else *Y = 0;
		*button = !GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_7);
}

/* Controller test code, displays raw X and Y positions as well
 as calibrated values and whether a button is pressed or not */
void ControllerTest(void){long *XPos, *YPos, *Button;
		Ctlread(XPos, YPos, Button);
		printf("X Raw:				%d\r",ADCValues[0]);
		printf("Y Raw:				%d\r",ADCValues[1]);
		printf("X Calibrated: %d \r",XPos);
		printf("Y Calibrated: %d \r",YPos);
		printf("Button: 			%d\r", Button);
		Output_Cursor_Reset();
}

// Interrupt service routine
// Executed every 20ns*(period)
void SysTick_Handler(void){
	sampleAdcPort(ADCValues);
	return;
}
