
#include <ctype.h>
#include "softpwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>


//! global buffers
unsigned char compare[CHMAX];
volatile unsigned char compbuff[CHMAX];


/*Init function. This function initialises the hardware
 */
void PWMInit(void)
{
  unsigned char i, pwm;

//why watchdog
  wdt_reset();           // reset watchdog timer
  MCUSR &= ~(1 << WDRF);        // clear the watchdog reset flag
  WDTCR |= (1<<WDCE)|(1<<WDE); // start timed sequence
  WDTCR = 0x00;                // disable watchdog timer
  DDRA |= PORTA_MASK;
  DDRB |= PORTB_MASK;            // set port pins to output
  pwm = PWMDEFAULT;
  for(i=0 ; i<CHMAX ; i++)      // initialise all channels
  {
    compare[i] = pwm;           // set default PWM values
    compbuff[i] = pwm;          // set default PWM values
  }
  TIFR |= (1 << OCF1A);           // clear interrupt flags
  TIMSK |= (1 << TOIE1)  ;         // enable output compare interrupts
  TCCR1B = (1 << CS10);         // start timer, no prescale
  sei();         // enable interrupt
}

void setPWM(unsigned char channel,unsigned char value) {
	compbuff[channel] = value;
}



  ISR(TIMER1_OVF1_vect)
{
  static unsigned char pinlevelB=PORTB_MASK;
  static unsigned char pinlevelA=PORTA_MASK;
  static unsigned char softcount=0xFF;
  PORTA = pinlevelA;            // update outputs
  PORTB = pinlevelB;            // update outputs
  
  if(++softcount == 0){         // increment modulo 256 counter and update
                                // the compare values only when counter = 0.
    compare[0] = compbuff[0];   // verbose code for speed
    compare[1] = compbuff[1];
    compare[2] = compbuff[2];
    compare[3] = compbuff[3];
    compare[4] = compbuff[4];
    compare[5] = compbuff[5];
    compare[6] = compbuff[6];
    compare[7] = compbuff[7];
    compare[8] = compbuff[8];


   // last element should equal CHMAX - 1

    pinlevelA = PORTA_MASK;     // set all port pins high
    pinlevelB = PORTB_MASK;     // set all port pins high
    softcount = 0;	  
  }
  // clear port pin on compare match (executed on next interrupt)
  if(compare[0] == softcount) R0_CLEAR;
  if(compare[1] == softcount) G0_CLEAR;
  if(compare[2] == softcount) B0_CLEAR;
  if(compare[3] == softcount) R1_CLEAR;
  if(compare[4] == softcount) G1_CLEAR;
  if(compare[5] == softcount) B1_CLEAR;
  if(compare[6] == softcount) R2_CLEAR;
  if(compare[7] == softcount) G2_CLEAR;
  if(compare[8] == softcount) B2_CLEAR;

}


