#define NUM_FAIRIES 7
#define NUM_DEATHFAIRIES 1
#define NUM_MYBULLETS 100
#define NUM_THEIRBULLETS 100
//#define ENEMYSHOOTSPEED 13

void InitBullets(void);
void Shoot(int X,int Y);
void eShoot(int X, int Y);
void makefairies(long X, long Y);
void makedeathfairies(long X, long Y);
unsigned long Random(void);


void Seed(unsigned long n);
unsigned long Random(void);
