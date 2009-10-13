#include <avr/io.h> 
#include <avr/interrupt.h>  
#include <util/delay.h> 
#include <stdlib.h>
#include "USI_UART.h"
#include "softpwm.h"



static unsigned char          mybuffer[16]; 
int rxindex;

int main(void) {


	PWMInit();
	USI_UART_Initialise_Receiver();


	while(1) {
	
		if(USI_UART_Data_In_Receive_Buffer()) {					// if there is data in receive buffer
			_delay_ms(10);
			rxindex = 0; 										// reset my buffer rx index
			while(USI_UART_Data_In_Receive_Buffer()) {			// move from rx buffer 
				mybuffer[rxindex] = USI_UART_Receive_Byte();	// to my buffer
				rxindex++;										// incr index
			}
		} 														
		if(!USI_UART_Data_In_Receive_Buffer() && mybuffer[0]) {
			_delay_ms(10);
			rxindex=0;								// reset rx index
			while(mybuffer[rxindex]) {				// while we have rx buffer data
				setPWM(0,mybuffer[rxindex]);
				setPWM(1,mybuffer[rxindex+3]);
				setPWM(2,mybuffer[rxindex+6]);
				setPWM(3,mybuffer[rxindex+1]);
				setPWM(4,mybuffer[rxindex+4]);
				setPWM(5,mybuffer[rxindex+7]);
				setPWM(6,mybuffer[rxindex+2]);
				setPWM(7,mybuffer[rxindex+5]);
				setPWM(8,mybuffer[rxindex+8]);
				mybuffer[rxindex] = 0x00;			// clear buffer start 	
			}
		}
		
	}
	return 1;

 
}

