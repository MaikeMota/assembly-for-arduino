/*
 * USART.h
 *
 * Created: 01/02/2018 22:00:06
 *  Author: maike
 */ 

#include <avr/io.h>
#include <stdint.h>

#include "util.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#ifndef USART_H_
#define USART_H_


void USART_init(void);
void USART_send( unsigned char data);
unsigned char USART_receive(void);
void USART_put_string(char* string);

#endif /* USART_H_ */