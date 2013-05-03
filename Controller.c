/* Controller.c
This sets up the Controller inputs, as well as providing a main loop to demonstrate the module
Controller includes the PSP slide pot, which is read through ADC
It is calibrated to provide directional input in terms of positive or negative values, with a deadzone when the analog stick isn't touched
*/

#include <stdio.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "adc.h"
#include "controller.h"
#include "Output.h"
#include "lm3s1968.h"
#include "entities.h"
#include "rit128x96x4.h"
#include "systickints.h"
#include "movingbits.h"

extern const unsigned char hitbox[];

unsigned long ADCValues[2];

int shootspeed;
int enemyshoot;

extern long hbox[2];
extern long X;
extern long Y;
extern long B;
extern player Avatar;
extern const unsigned char hitbox[];
extern int score;


extern bullet_struct mybullets[NUM_MYBULLETS];
extern bullet_struct theirbullets[NUM_THEIRBULLETS];
extern enemy fairies[NUM_FAIRIES];
extern enemy deathfairies[NUM_DEATHFAIRIES];

int explosionM;

//CTLRInit exists just so I didn't have to include adc.h in the main file
//It also initializes a lot more than just the controller. Oh well.
void CTLRInit(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3));
	GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2, 1);
	ADCInit();
}



void GameOver(void){
	DisableInterrupts();
	printf("Too bad! You lose! \rYour score was:\r%d \rPress reset to try \ragain!",score);
	while(1);
}

/* Reads Controller raw input, and calibrates. Ignoring the dead
  zone of the PSP slide pad, returns either positive or negative 1.
  The button being pressed returns a 1, otherwise its 0 */
void CTLRRead(long* X, long* Y, long* button){
		ADCSample(ADCValues);
		if (ADCValues[0] > 675) *X = 1;
		else if (ADCValues[0] < 525) *X= -1;
		else *X = 0;
		if (ADCValues[1] > 510) *Y = -2;
		else if (ADCValues[1] < 410) *Y = 2;
		else *Y = 0;
		*button = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_7);
}

/* Controller test code, displays raw X and Y positions as well
 as calibrated values and whether a button is pressed or not */
void CTLRTest(void){long XPos, YPos, Button;
	while(1){
		CTLRRead(&XPos, &YPos, &Button);
		printf("X Raw:				%d\r",ADCValues[0]);
		printf("Y Raw:				%d\r",ADCValues[1]);
		printf("X Calibrated: %d \r",XPos);
		printf("Y Calibrated: %d \r",YPos);
		printf("Button: 			%d\r", Button);
		Output_Cursor_Reset();
	}
}


//Timer handler
//basically, this is where everything in the game happens
//The main loop is empty, so this is where the magic happens
void Timer0A_Handler(void){int i;
  int deathflag = 0;
	RIT128x96x4_ClearImage();
	CTLRRead(&X, &Y, &B);
	
// Move Avatar around
	Avatar.X = (Avatar.X + X);
	Avatar.Y = (Avatar.Y + Y);
	if (Avatar.Y < 0) Avatar.Y = 0;
	if (Avatar.Y > 70) Avatar.Y = 70;
	
	//set hitbox on character head
	hbox[0] = (Avatar.Y+6);
	hbox[1] = (Avatar.X+4);
	
	//If the character's speed is greater than the counter, then, they can shoot
	if (shootspeed > Avatar.speed){
		if (B) {
			Shoot((Avatar.X), (Avatar.Y+4));
		}
		shootspeed = 0;
	}
	shootspeed++;
	
	//Populate the RAM buffer and the screen with player's bullets
	for (i = 0; i < NUM_MYBULLETS; i++){
		if (mybullets[i].time != (-1)){
			long myx, myy;
			mybullets[i].time++;
			mybullets[i].Position(mybullets[i].time,&myx,&myy);
			RIT128x96x4_SetPixel(mybullets[i].Y+myy, mybullets[i].X+myx, 15);
			if (mybullets[i].Y+myy < 1){
				mybullets[i].time = -1;
			}
		}
	}
	
	// Generate 7 fairies at random X Values
	
	//Iterate through fairies, load into the RAM buffer ones that aren't dead.
	for (i = 0; i < NUM_FAIRIES; i++){int explosionS = 0;
		if (fairies[i].time == (-1)){
			makefairies(((i*9)+9),0);
		}
		if (fairies[i].time != (-1)){
			fairies[i].time++;
			fairies[i].Position(fairies[i].time, &fairies[i].X, &fairies[i].Y);
			RIT128x96x4_CheckOverwrite(fairies[i].esprite, fairies[i].Y, fairies[i].X, &explosionS);
			if (explosionS){
				fairies[i].time = -1;
			}
			else {
				if (enemyshoot > ENEMYSHOOTSPEED){
					eShoot(fairies[i].X, fairies[i].Y);
				}
				RIT128x96x4_LoadImage(fairies[i].esprite, fairies[i].Y, fairies[i].X);
			}
		}
	}

	//Populate the RAM buffer with enemy bullets
	for (i = 0; i < NUM_THEIRBULLETS; i++){
		if (theirbullets[i].time != (-1)){
			long myx, myy;
			theirbullets[i].time++;
			theirbullets[i].Position(theirbullets[i].time,&myx,&myy);
			RIT128x96x4_SetPixel(theirbullets[i].Y+myy, theirbullets[i].X+myx, 15);
			if (theirbullets[i].Y+myy > 90){
				theirbullets[i].time = -1;
			}
		}
	}
	RIT128x96x4_CheckOverwrite(hitbox, hbox[0], hbox[1], &deathflag);
		if (deathflag){
			Avatar.lives = Avatar.lives - 1;
				if (Avatar.lives == 0){
					GameOver();
				}
/*			Avatar.X = 27;
			Avatar.Y = 60;
			hbox[0] = (Avatar.Y+6);
			hbox[1] = (Avatar.X+4);*/
			}
	RIT128x96x4_LoadImage(Avatar.character, Avatar.Y, Avatar.X);
	RIT128x96x4_ShowImage();
	if (Avatar.lives == 3) GPIO_PORTD_DATA_R = 0x07;
	if (Avatar.lives == 2) GPIO_PORTD_DATA_R = 0x02;
	if (Avatar.lives == 1) GPIO_PORTD_DATA_R = 0x01;
	else GPIO_PORTD_DATA_R = 0;
	if (ENEMYSHOOTSPEED < enemyshoot){
		enemyshoot = 0;
	}
	enemyshoot++;
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;
}
