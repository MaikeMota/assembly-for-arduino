/*
 * util.h
 *
 * Created: 01/02/2018 22:09:57
 *  Author: maike
 */ 

#include <stdint.h>
#define F_CPU 16000000UL

#ifndef UTIL_H_
#define UTIL_H_

void send_normalized_data(uint16_t raw_value, uint16_t normalized_value, uint16_t lower_bound,uint16_t higher_bound);


#endif /* UTIL_H_ */