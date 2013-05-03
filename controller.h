//-------------Controller Init---------------
// Initializes the ADC and GPIO Input Port
// Input: None
// Output: None
void CTLRInit(void);

//-------------Controller Read---------------
// Reads from the Controller and stores the
// calibrated X and Y values
// Input: X, Y, and Button addresses
// Output: technically none, but it stores
// values in the address of the input
void CTLRRead(long* X, long* Y, long* button);

//-------------Controller Test---------------
// Tests the controller code and outputs the
// raw and calibrated data to the screen
// Input: None
// Output: None
void CTLRTest(void);

void GameOver(void);
