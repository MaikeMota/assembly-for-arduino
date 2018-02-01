/*
 * normalize.c
 *
 * Created: 01/02/2018 20:57:45
 * Author : maike
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "headers/normalize.h"

#define F_CPU 16000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)



void USART_init(void){
	
	UBRR0H = (uint8_t)(BAUD_PRESCALE>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALE);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}

void USART_send( unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

unsigned char USART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void USART_put_string(char* StringPtr){
	
	while(*StringPtr != 0x00){    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
		USART_send(*StringPtr);    //Using the simple send function we send one char at a time
		StringPtr++;
	}        //We increment the pointer so we can read the next char
	
}

void ADC_init()
{
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC 
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t ADC_read(uint8_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}

const uint16_t lower_bound = 800;
const uint16_t upper_bound = 350;

int main(void)
{	

	USART_init();
	ADC_init();
	
    while (1) 
	{
		char str[16];
		int raw_value = ADC_read(0);
		int normalized_value = normalize(raw_value, lower_bound, upper_bound);
		USART_put_string("RAW Value");
		USART_put_string("\t");
		USART_put_string("Normalized Value");
		USART_put_string("\t");
		USART_put_string("Upper Bound");
		USART_put_string("\t");
		USART_put_string("Lower Bound");
		USART_put_string("\n\r");
		USART_put_string(itoa(raw_value, str, 10));
		USART_put_string("\t\t");
		USART_put_string(itoa(normalized_value, str, 10));
		USART_put_string("\t\t\t");
		USART_put_string(itoa(upper_bound, str, 10));
		USART_put_string("\t\t");
		USART_put_string(itoa(lower_bound, str, 10));
		USART_put_string("\n\r");
		_delay_ms(25000);
    }
}

