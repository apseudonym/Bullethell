#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *) 0x4002551C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *) 0x400FE108))

void DAC_Init(void);
void DAC_out(unsigned long);

unsigned long DACoutput;

void DAC_Init(){volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_DIR_R |= 0x0F;          //set 0-3 outputs
  GPIO_PORTF_AFSEL_R = 0x00;
  GPIO_PORTF_DEN_R = 0xFF;
}

void DAC_Out(unsigned long DACoutput){
  GPIO_PORTF_DATA_R = DACoutput;
}
