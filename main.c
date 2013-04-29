//Christopher Davis
//Pawan Mannava
//Touhou-like Bullethell
//created April 22, 2013
/*I DO NOT OWN ANY OF THESE SPRITES
 ALL SPRITES BELONG TO ZUN*/

#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "lm3s1968.h"
#include "controller.h"
#include "rit128x96x4.h"
#include "Output.h"
#include "systickints.h"
#include "entities.h"

#define yolo "swag"

long XPos;
long YPos;

int main(void){
	
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                 SYSCTL_XTAL_8MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, GPIO_PIN_7);
  SysCtlADCSpeedSet(SYSCTL_ADCSPEED_1MSPS);
	CTLRInit();
	Output_Init();
	Output_Color(15);
	SysTick_Init(20000000);
	
	while(1){
	ControllerTest();
	}
}

