// This file contains the entity definitions

/* This is the struct for the player. Contains movement speed, X and Y position, and sprite */
typedef struct {
	long X;
	long Y;
	long speed;
	long lives;
} player;

/* This is the struct for an enemy */
typedef struct {
	void(*Position)(long,long*,long*,char*,char*);
	char xdirection;
	char ydirection;
	long time;
	long hitpoints;
} enemey;

void fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void death_fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void bullets (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void cirno (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
