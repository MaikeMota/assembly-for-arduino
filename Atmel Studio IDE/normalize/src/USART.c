/*
 * USART.c
 *
 * Created: 01/02/2018 22:01:12
 *  Author: maike
 */ 

#include "../headers/USART.h"


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

void USART_put_string(char* string){
	
	while(*string != 0x00){    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
		USART_send(*string);    //Using the simple send function we send one char at a time
		string++;
	}        //We increment the pointer so we can read the next char
	
}
