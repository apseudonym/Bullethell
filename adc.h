//ADC.h

//ADC Test will check the ADC and output onto the screen X and Y values
void ADCTest(void);

//ADC Init will initialize sequencer 3 and ADC channel 0 and 1
void ADCInit(void);

//ADC Sample will write to an array of containing the x and y values where the 0th location is X and the 1st is Y
void ADCSample(unsigned long* ADCValues);
