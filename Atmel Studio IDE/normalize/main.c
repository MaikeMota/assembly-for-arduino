/*
 * normalize.c
 *
 * Created: 01/02/2018 20:57:45
 * Author : maike
 */ 



#include "headers/normalize.h"
#include "headers/USART.h"
#include "headers/ADC.h"
#include "headers/util.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


const uint16_t lower_bound = 800;
const uint16_t upper_bound = 350;

int main(void)
{	

	USART_init();
	ADC_init();
	
    while (1) 
	{
		int raw_value = ADC_read(0);
		int normalized_value = normalize(raw_value, lower_bound, upper_bound);
		send_normalized_data(raw_value, normalized_value, lower_bound, upper_bound);
		_delay_ms(2500);
    }
}

