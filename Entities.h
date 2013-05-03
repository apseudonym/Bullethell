// This file contains the entity definitions

typedef void (*bulletpath)(long, long*, long*);

/* This is the struct for the player. Contains movement speed, X and Y position, and sprite */
typedef struct {
	long X;
	long Y;
	const unsigned char* character;
	long speed;
	long lives;
} player;

/* This is the struct for an enemy, their position is determined by how long they have stayed alive */
typedef struct {
	void(*Position)(long,long*,long*);
	long X;
	long Y;
	const unsigned char* esprite;
	long time;
} enemy;


/* This is the struct for bullets, their position is determined by how long they have existed*/
typedef struct {
	void (*Position)(long ,long*,long*);
	long X;
	long Y;
	long time;
} bullet_struct;

/* Prototypes for the various movement algorithms*/
void fairy (long time, long* XPos, long* YPos);
void death_fairy (long time, long* XPos, long* YPos);
void cirno (long time, long* XPos, long* YPos);
void bullets (long time, long* XPos, long* YPos);
void bulletl (long time, long* XPos, long* YPos);
void bulletr (long time, long* XPos, long* YPos);
void playerbullets (long time, long* XPos, long* YPos);


