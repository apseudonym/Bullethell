// This file contains the entity movement algorithms for said entities

#include "entities.h"

void fairy (long time, long* XPos, long* YPos){
	if (time < 62){
		*XPos = time;
		*YPos = 5;
	}
	if (time > 62){
		*XPos = 62-time;
		*YPos = 15;
	}
	
}

void death_fairy (long time, long* XPos, long* YPos){
	if (*XPos > 30 ){
		*XPos = (*XPos - time); 
	}
	if (*XPos < 30){
		*XPos = (*XPos + time);
	}
	if (*YPos > 10){
		*YPos = (*YPos - time*2);
	}
	if (*YPos < 10){
		*YPos= (*YPos + time*2);
	}
}

void cirno (long time, long* XPos, long* YPos){
	if (*XPos >= 60){
		*XPos = (*XPos - time); 
	}
	if (*XPos < 5){
		*XPos = (*XPos + time);
	}
	if (*YPos > 20){
		*YPos = (*YPos - time*2);
	}
	if (*YPos < 5){
		*YPos= (*YPos + time*2);
	}
}

void bulleth (long time, long* XPos, long* YPos, long X, long Y){int slope;
	slope = ((Y - *YPos)/(X - *XPos));
	*XPos = time;
	*YPos = *XPos * slope;
}

void bulletl (long time, long* XPos, long* YPos, long X, long Y){
	*XPos = -(time);
	*YPos = (time*2);
}

void bulletr (long time, long* XPos, long* YPos, long X, long Y){
	*XPos = time;
	*YPos = (time*2);
}

void bullets (long time, long* XPos, long* YPos, long X, long Y){
	*XPos = 0;
	*YPos = (time*2);
}

const bulletpath enemypaths[] = {/*bulleth,*/ bullets, bulletr, bulletl};

void playerbullets (long time, long* XPos, long* YPos, long eh, long meh){
	*XPos = 0;
	*YPos = -(time*2);
}
