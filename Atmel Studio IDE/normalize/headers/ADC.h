/*
 * ADC.h
 *
 * Created: 01/02/2018 22:04:20
 *  Author: maike
 */ 

#include <avr/io.h>
#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_

void ADC_init();
uint16_t ADC_read(uint8_t ADC_channel);

#endif /* ADC_H_ */