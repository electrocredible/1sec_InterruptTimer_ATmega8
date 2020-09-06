/*
 * 1second_Timer1_interrupt.c
 *
 * Created: 05-02-2019 1.08.42 AM
 * Author : Abhilekh-8bit
 */ 



//THIS PROGRAM PRINTS THE VALUE OF SECONDS AN MINUTES IN SERIAL PORT. CHANGE TCNT VALUES FOR DIFFERENT CRYSTALS	

#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile uint8_t seconds=0;
volatile uint8_t minutes=0;
void usart_init(void)
{
	UCSRB=(1<<TXEN);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRL=0x4D;//value for 12MHz and 9600baud
}
void usartr_send(unsigned char ch)
{
	while(!((UCSRA)&(1<<UDRE)));
	UDR=ch;
}

ISR(TIMER1_OVF_vect)
{
	seconds++;
	if(seconds>59)
	{
		minutes++;
		seconds=0;
	}
	
	usartr_send(seconds);
	usartr_send(minutes);
	
	TCNT1H=(-11719)>>8;
	TCNT1L=(-11719)&0xFF;
	
}

int main(void)
{
   
	TCNT1H=(-11719)>>8;
	TCNT1L=(-11719)&0xFF;// over flow after 11719 clocks__works for12MHZ,[1/12000000x1024x11719=1 second]
	TCCR1A=0x00;//normal mode
	TCCR1B=0x05;//internal clock ,prescaler 1:1024
	TIMSK=(1<<TOIE1);// enable timer1 interrupt
	sei();
	usart_init();
    while (1) 
    {
		
    }
}

