//Controls the generation and movement of all things that move about

#include <stdio.h>
#include "entities.h"
#include "movingbits.h"

bullet_struct mybullets[NUM_MYBULLETS];
bullet_struct theirbullets[NUM_THEIRBULLETS];
enemy fairies[NUM_FAIRIES];
enemy deathfairies[NUM_DEATHFAIRIES];

unsigned long m = 1;
extern bulletpath enemypaths[];
extern const unsigned char bluefairy[];
extern const unsigned char deathfairy[];


void InitBullets(void){int i;
	for (i = 0; i < NUM_MYBULLETS; i++){
		mybullets[i].time = -1;
		theirbullets[i].time = -1;
		fairies[i].time = -1;
		deathfairies[i].time = -1;
	}
}

void Seed(unsigned long n){
	m = n;
}

unsigned long Random(void){
	m = 1664525*m+1013904223;
	return m;
}

void makefairies(long X, long Y){int i;
	for (i = 0; i < NUM_FAIRIES; i++){
		if (fairies[i].time == -1){
			fairies[i].X = X;
			fairies[i].Y = Y;
			fairies[i].time = 0;
			fairies[i].Position = fairy;
			fairies[i].esprite = bluefairy;
			i = NUM_FAIRIES;
		}
	}
}

void makedeathfairies(long X, long Y){int i;
	for (i = 0; i < NUM_FAIRIES; i++){
		if (deathfairies[i].time == -1){
			deathfairies[i].X = X;
			deathfairies[i].Y = Y;
			i = NUM_FAIRIES;
			deathfairies[i].time = 0;
			deathfairies[i].Position = death_fairy;
		}
	}
}

void Shoot(int X, int Y){int i;
	for (i = 0; i < NUM_MYBULLETS; i++){
		if (mybullets[i].time == -1){
			mybullets[i].X = (X*2)+6;
			mybullets[i].Y = Y-3;
			mybullets[i].time = 0;
			mybullets[i].Position = playerbullets;
			i = NUM_MYBULLETS;
		}
	}
}
	
void eShoot(int X, int Y){int i;
	for (i = 0; i < NUM_THEIRBULLETS; i++){
		if (theirbullets[i].time == -1){
			theirbullets[i].X = (X*2)+4;
			theirbullets[i].Y = Y+3;
			theirbullets[i].time = 0;
			theirbullets[i].Position = enemypaths[Random()%3];
			i = NUM_THEIRBULLETS;
		}
		if (mybullets[i].Y < 1){
			mybullets[i].time = -1;
		}
	}
}
