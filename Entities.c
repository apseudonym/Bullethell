// This file contains the entity definitions as well as movement algorithms for said entities

/* This is the struct for the player. Contains movement speed, X and Y position, and sprite */
typdef struct {
	long X,
	long Y,
	long speed,
	
} player;

/* This is the struct for a weak enemy. Contains function pointer to X and Y position, sprite, time its been living, and hitpoints */
typedef struct {
	void (*Position)(time),
	//put in sprite here
	long time,
	long hitpoints,
} wEnemey;

/*This is the struct for a stronger enemy. Contains function pointer to X and Y positions, sprite, and hitpoints */
typdef struct {
	void (*Position)(time),
	//put in sprite here
	long time,
	long hitpoints,
} sEnemy;

typedef struct {
	
	
} sBullets;

typedef struct {
	
	
} lBullets;