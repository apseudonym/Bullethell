// This file contains the entity movement algorithms for said entities

#include "entities.h"

void fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection){
	if (*XPos >= 128){
		*xdirection = *xdirection * (-1);
	}
	*XPos = time + (2*(*xdirection));
	*YPos = time + 1;
}

void death_fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection){
	if (*XPos >= 128){
		*xdirection = *xdirection*(-1);
	}
	if (*YPos > 40){
		*ydirection = *ydirection*(-1);
	}
	*XPos = time + (3*(*xdirection));
	*YPos = time + (2*(*ydirection));
}
