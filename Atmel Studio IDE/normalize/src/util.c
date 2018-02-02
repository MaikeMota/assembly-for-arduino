/*
 * util.c
 *
 * Created: 01/02/2018 22:07:23
 *  Author: maike
 */ 

#include "../headers/util.h"
#include "../headers/USART.h"

char* itoa(int __val, char *__s, int __radix);

void send_normalized_data(uint16_t raw_value, uint16_t normalized_value, uint16_t lower_bound, uint16_t upper_bound){
	char value[16];
	USART_put_string("RAW Value");
	USART_put_string("\t");
	USART_put_string("Normalized Value");
	USART_put_string("\t");
	USART_put_string("Upper Bound");
	USART_put_string("\t");
	USART_put_string("Lower Bound");
	USART_put_string("\n\r");
	itoa(raw_value, value, 10);
	USART_put_string(value);
	USART_put_string("\t\t");
	itoa(normalized_value, value, 10);
	USART_put_string(value);
	USART_put_string("\t\t\t");
	itoa(upper_bound, value, 10);
	USART_put_string(value);
	USART_put_string("\t\t");
	itoa(lower_bound, value, 10);
	USART_put_string(value);
	USART_put_string("\n\r");
}
