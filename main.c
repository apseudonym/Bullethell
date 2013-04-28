//Christopher Davis
//Pawan Mannava
//Touhou-like Bullethell
//created April 22, 2013

#include <stdio.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "lm3s1968.h"
#include "adc.h"
#include "rit128x96x4.h"
#include "Output.h"
#include "systickints.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"


unsigned long ADCValues[2];
long XPos;
long YPos;

int main (void){
	
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                 SYSCTL_XTAL_8MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, GPIO_PIN_7);
  SysCtlADCSpeedSet(SYSCTL_ADCSPEED_1MSPS);
	InitAdcPorts();
	Output_Init();
	Output_Color(15);
	SysTick_Init(20000000);
	
	while(1){int PortG;
		if (ADCValues[0] > 675) XPos = 1;
		else if (ADCValues[0] < 545) XPos = -1;
		else XPos = 0;
		if (ADCValues[1] > 495) YPos = 1;
		else if (ADCValues[1] < 420) YPos = -1;
		else YPos = 0;
		PortG = !GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_7);
		
		printf("X Raw:				%d\r",ADCValues[0]);
		printf("Y Raw:				%d\r",ADCValues[1]);
		printf("X Calibrated: %d \r",XPos);
		printf("Y Calibrated: %d \r",YPos);
		printf("Button: 			%d\r", PortG);
		Output_Cursor_Reset();
	}
}


// Interrupt service routine
// Executed every 20ns*(period)
void SysTick_Handler(void){
	sampleAdcPort(ADCValues);
	return;
}
