// Pin mappings
#define CHMAX       9    // maximum number of PWM channels
#define PWMDEFAULT  0x08  // default PWM value at start up for all channels

#define R0_CLEAR (pinlevelB &= ~(1 << PB4)) // map R0 to PB4
#define G0_CLEAR (pinlevelB &= ~(1 << PB5)) // map G0 to PB5
#define B0_CLEAR (pinlevelB &= ~(1 << PB6)) // map B0 to PB6

#define R1_CLEAR (pinlevelA &= ~(1 << PA0)) // map R1 to PA0
#define G1_CLEAR (pinlevelA &= ~(1 << PA1)) // map G1 to PA1
#define B1_CLEAR (pinlevelA &= ~(1 << PA2)) // map B1 to PA2

#define R2_CLEAR (pinlevelA &= ~(1 << PA5)) // map R1 to PA5
#define G2_CLEAR (pinlevelA &= ~(1 << PA6)) // map G1 to PA6
#define B2_CLEAR (pinlevelA &= ~(1 << PA7)) // map B1 to PA7

// ROOM FOR A THIRD OR 4TH ON REST OF PORT A AND SOME OF PORT B ********

// Set bits corresponding to pin usage above
#define PORTB_MASK  (1 << PB4)|(1 << PB5)|(1 << PB6)
#define PORTA_MASK  (1 << PA0)|(1 << PA1)|(1 << PA2)|(1 << PA5)|(1 << PA6)|(1 << PA7)

// prototypes
void PWMInit(void);
void setPWM(unsigned char,unsigned char);

