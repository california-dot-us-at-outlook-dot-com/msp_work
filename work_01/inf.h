#ifndef INF_H_
#define INF_H_

#include<msp430.h>

void infrared_decode();
void set_value(unsigned char);
void init_port1();
void init_device();

#endif /* INF_H_ */
