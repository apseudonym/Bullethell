// #define GPIO_PORTF_DATA_R       (*((volatile unsigned long *) 0x400253FC))
// #define GPIO_PORTF_DIR_R        (*((volatile unsigned long *) 0x40025400))
// #define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *) 0x40025420))
// #define GPIO_PORTF_DEN_R        (*((volatile unsigned long *) 0x4002551C))
// #define SYSCTL_RCGC2_R          (*((volatile unsigned long *) 0x400FE108))

void DAC_Init(void);
void DAC_Out(unsigned long);

extern unsigned long DACoutput;
