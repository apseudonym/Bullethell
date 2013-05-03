/* ADC Module
Takes X and Y input from the PSP slide pad
Allow Main in order to test input, it will print positions to the screen
*/

#include <inc/hw_types.h>
#include "driverlib/sysctl.h"
#include <driverlib/adc.h>
#include "driverlib/gpio.h"
#include <inc/hw_memmap.h>

int ADCTest(void){
	while(1);
}

void ADCInit(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
	ADCSequenceConfigure(ADC_BASE,0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC_BASE, 0, 1, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceEnable(ADC_BASE, 0);
}

void ADCSample(unsigned long* ADCValues) {
	ADCProcessorTrigger(ADC_BASE, 0 ); 
	while(!ADCIntStatus(ADC_BASE, 0, false)); 
	ADCSequenceDataGet(ADC_BASE, 0, ADCValues);
	ADCIntClear(ADC_BASE, 0);
}
