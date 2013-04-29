// This file contains the entity definitions

/* This is the struct for the player. Contains movement speed, X and Y position, and sprite */
typedef struct {
	long X;
	long Y;
	long speed;
	long lives;
} player;

/* This is the struct for an enemy, their position is determined by how long they have stayed alive */
typedef struct {
	void(*Position)(long,long*,long*,char*,char*);
	char xdirection;
	char ydirection;
	long time;
	long hitpoints;
} enemey;

/* This is the struct for bullets, their position is determined by how long they have existed*/
typedef struct {
	void (*Position)(long,long*,long*);
	long time;
} bullet;

/* Prototypes for the various movement algorithms*/
void fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void death_fairy (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void cirno (long time, long* XPos, long* YPos, char* xdirection, char* ydirection);
void bullets (long time, long* XPos, long* YPos);
void bulletl (long time, long* XPos, long* YPos);
void bulletr (long time, long* XPos, long* YPos);
